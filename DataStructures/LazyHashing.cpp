int add(ll a, ll b, ll mod) {
    return (a % mod + b % mod) % mod;
}
int mul(ll a, ll b, ll mod) {
    return ((a % mod) * (b % mod)) % mod;
}

const int N = 2e5 + 5;
const ll mod [] = {(ll)1e9 + 7, (ll)2e9 + 11}, B [] = {131, 137};
int pw[2][N];
array<int, 2> val[27][N];

void init() {
    for (int i = 0; i < 2; i++) {
        auto& p = pw[i];
        p[0] = 1;
        for (int j = 1; j < N; j++)
            p[j] = mul(p[j - 1], B[i], mod[i]);
    }
    for (int d = 1; d < 27; d++) {
        auto& v = val[d];
        v[0] = {0, 0};
        for (int i = 1; i < N; i++) {
            for (int j = 0; j < 2; j++) {
                v[i][j] = add(mul(v[i - 1][j], B[j], mod[j]), d, mod[j]);
            }
        }
    }
}

class segmentTree
{
private:
    int size;
    struct Node
    {
        array<int, 2> h;
        int lazy, cnt = 0;
        Node() {
            h = {0, 0};
            lazy = -1;
            cnt = 0;
        }
        Node(int dg) {
            h = val[dg][1];
            lazy = -1;
            cnt = 1;
        }
        void apply(int dg, int lx, int rx) {
            lazy = dg;
            int len = rx - lx + 1;
            for (int i = 0; i < 2; i++)
                h[i] = val[dg][len][i];
        }
        void merge(const Node& lf, const Node& ri) {
            for (int i = 0; i < 2; i++)
                h[i] = add(mul(lf.h[i], pw[i][ri.cnt], mod[i]), ri.h[i], mod[i]);
            cnt = lf.cnt + ri.cnt;
        }
    };
    vector<Node> tree;

    void propagate(int nd, int lx, int rx) {
        if (tree[nd].lazy == -1)
            return;
        if (lx != rx) {
            int mid = (lx + rx) >> 1, lf = 2 * nd + 1, ri = 2 * nd + 2;
            tree[lf].apply(tree[nd].lazy, lx, mid);
            tree[ri].apply(tree[nd].lazy, mid + 1, rx);
        }
        tree[nd].lazy = -1;
    }
    void build(int nd, int lx, int rx, const string& s) {
        if (lx == rx) {
            if (lx < s.size()) {
                tree[nd] = Node(s[lx] - 'a' + 1);
            }
            return;
        }
        int mid = (lx + rx) >> 1, lf = 2 * nd + 1, ri = 2 * nd + 2;
        build(lf, lx, mid, s);
        build(ri, mid + 1, rx, s);
        tree[nd].merge(tree[lf], tree[ri]);
    }

    void update(int nd, int lx, int rx, int l, int r, int dg) {
        if (lx > r || rx < l)
            return;
        if (lx >= l && rx <= r) {
            tree[nd].apply(dg, lx, rx);
            return;
        }
        propagate(nd, lx, rx);
        int mid = (lx + rx) >> 1, lf = 2 * nd + 1, ri = 2 * nd + 2;
        update(lf, lx, mid, l, r, dg);
        update(ri, mid + 1, rx, l, r, dg);
        tree[nd].merge(tree[lf], tree[ri]);
    }

    Node query(int nd, int lx, int rx, int l, int r) {
        if (lx > r || rx < l)
            return Node();
        if (lx >= l && rx <= r)
            return tree[nd];
        propagate(nd, lx, rx);
        int mid = (lx + rx) >> 1, lf = 2 * nd + 1, ri = 2 * nd + 2;
        Node ret;
        ret.merge(query(lf, lx, mid, l, r), query(ri, mid + 1, rx, l, r));
        return ret;
    }

public:
    segmentTree(const string& s) {
        size = 1;
        while (size < s.size())
            size <<= 1;
        tree.assign(2 * size, Node());
        build(0, 0, size - 1, s);
    }

    void update(int l, int r, int dg) {
        update(0, 0, size - 1, l, r, dg);
    }

    array<int, 2> query(int l, int r) {
        auto res = query(0, 0, size - 1, l, r);
        return res.h;
    }
};

