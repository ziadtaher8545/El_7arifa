
class SegmentTree {
public:
    struct Node {
        ll sum, pref, suff, ans;
    };

    int n;
    vector<Node> tree;

    SegmentTree(vector<ll> &a) {
        n = a.size();
        tree.resize(4 * n);
        build(1, 0, n - 1, a);
    }

    Node makeNode(ll v) {
        return {v, v, v, v};
    }

    Node mergeNode(const Node &a, const Node &b) {
        Node c;
        c.sum = a.sum + b.sum;
        c.pref = max(a.pref, a.sum + b.pref);
        c.suff = max(b.suff, b.sum + a.suff);
        c.ans = max({a.ans, b.ans, a.suff + b.pref});
        return c;
    }

    void build(int id, int l, int r, vector<ll> &a) {
        if (l == r) {
            tree[id] = makeNode(a[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(id * 2, l, mid, a);
        build(id * 2 + 1, mid + 1, r, a);
        tree[id] = mergeNode(tree[id * 2], tree[id * 2 + 1]);
    }

    Node query(int id, int l, int r, int ql, int qr) {
        if (qr < l || r < ql)
            return {0, (ll) -4e18, (ll) -4e18, (ll) -4e18};

        if (ql <= l && r <= qr)
            return tree[id];

        int mid = (l + r) / 2;
        Node L = query(id * 2, l, mid, ql, qr);
        Node R = query(id * 2 + 1, mid + 1, r, ql, qr);
        return mergeNode(L, R);
    }

    ll getMaxSub(int l, int r) {
        return query(1, 0, n - 1, l, r).ans;
    }

    void update(int id, int l, int r, int pos, ll val) {
        if (l == r) {
            tree[id] = makeNode(val);
            return;
        }

        int mid = (l + r) / 2;
        if (pos <= mid)
            update(id * 2, l, mid, pos, val);
        else
            update(id * 2 + 1, mid + 1, r, pos, val);

        tree[id] = mergeNode(tree[id * 2], tree[id * 2 + 1]);
    }

    void updateVal(int pos, ll val) {
        update(1, 0, n - 1, pos, val);
    }
};
