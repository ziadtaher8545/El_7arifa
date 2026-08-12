
struct Node {
    Node* l, * r;
    ll sum, lazy;

    Node(ll val = 0) : l(nullptr), r(nullptr), sum(val), lazy(0) {}
    Node(Node* l, Node* r) : l(l), r(r), sum(0), lazy(0) {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }

    void apply(int s, int e, ll val) {
        sum += val * (e - s + 1);
        lazy += val;
    }

    void push(int s, int e) {
        if (lazy == 0) return;
        int mid = s + (e - s) / 2;

        l = (l == nullptr) ? new Node() : new Node(*l);
        l->apply(s, mid, lazy);

        r = (r == nullptr) ? new Node() : new Node(*r);
        r->apply(mid + 1, e, lazy);

        lazy = 0;
    }
};

class LazyPST {
private:
    int n;

    // Helper Functions
    ll getSum(Node* node) { return node ? node->sum : 0; }
    Node* getL(Node* node) { return node ? node->l : nullptr; }
    Node* getR(Node* node) { return node ? node->r : nullptr; }

    Node* update(Node* node, int s, int e, int l, int r, ll val) {
        if (r < s || e < l) return node;

        Node* cur = node ? new Node(*node) : new Node();

        if (l <= s && e <= r) {
            cur->apply(s, e, val);
            return cur;
        }

        cur->push(s, e);
        int mid = s + (e - s) / 2;

        cur->l = update(getL(cur), s, mid, l, r, val);
        cur->r = update(getR(cur), mid + 1, e, l, r, val);

        cur->sum = getSum(cur->l) + getSum(cur->r);
        return cur;
    }

    ll query(Node* node, int s, int e, int l, int r, ll lazy_add) {
        if (r < s || e < l) return 0;

        if (!node) {
            int intersect_len = min(e, r) - max(s, l) + 1;
            return max(0, intersect_len) * lazy_add;
        }

        if (l <= s && e <= r) {
            return node->sum + lazy_add * (e - s + 1);
        }

        int mid = s + (e - s) / 2;
        ll next_lazy = lazy_add + node->lazy;

        return query(node->l, s, mid, l, r, next_lazy) +
            query(node->r, mid + 1, e, l, r, next_lazy);
    }

public:
    LazyPST(int n) : n(n) {}

    Node* build(int s, int e, const vector<int>& a) {
        if (s == e) return new Node(a[s]);
        int mid = s + (e - s) / 2;
        return new Node(build(s, mid, a), build(mid + 1, e, a));
    }

    Node* update(Node* node, int l, int r, ll val) {
        return update(node, 0, n - 1, l, r, val);
    }

    ll query(Node* node, int l, int r) {
        return query(node, 0, n - 1, l, r, 0);
    }
};
