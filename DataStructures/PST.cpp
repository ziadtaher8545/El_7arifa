struct Node
{
    Node* l, * r;
    ll sum = 0, lazy = 0;

    Node(int val) : l(NULL), r(NULL), sum(val) {}
    Node() : l(NULL), r(NULL) {}
    Node(Node* l, Node* r) : l(l), r(r) {
        if (l != NULL)
            sum += l->sum;
        if (r != NULL)
            sum += r->sum;
    }

    void apply(int s, int e, ll val) {
        sum += val * (e - s + 1);
        lazy += val;
    }

    void push(int s, int e) {
        if (lazy == 0)
            return;
        int mid = s + e >> 1;

        l = l == NULL ? new Node() : new Node(*l);
        l->apply(s, mid, lazy);

        r = r == NULL ? new Node() : new Node(*r);
        r->apply(mid + 1, e, lazy);

        lazy = 0;
    }
};
class PST
{
private:
    int n;
    Node merge(Node lf, Node ri) {
        Node ret;
        ret.sum = lf.sum + ri.sum;
        return ret;
    }

    // range update
    Node* update(Node* node, int s, int e, int l, int r, ll val) {
        if (r < s || e < l || !node)
            return node;
        if (l <= s && e <= r) {
            Node* cur = new Node(*node);
            cur->apply(s, e, val);
            return cur;
        }

        node->push(s, e);
        int mid = s + e >> 1;
        return new Node(update(node->l, s, mid, l, r, val), update(node->r, mid + 1, e, l, r, val));
    }

    // point update
    Node* update(Node* node, int s, int e, int i, ll val) {
        if (s == e)
            return new Node(val);
        int mid = s + e >> 1;
        if (i <= mid)
            return new Node(update(node->l, s, mid, i, val), node->r);
        else
            return new Node(node->l, update(node->r, mid + 1, e, i, val));
    }
    Node query(Node* node, int s, int e, int l, int r) {
        if (!node || r < s || e < l)
            return Node();
        if (l <= s && e <= r)
            return *node;

        node->push(s, e);
        int m = (s + e) / 2;
        return merge(query(node->l, s, m, l, r), query(node->r, m + 1, e, l, r));
    }

    int getKth(Node* cur, Node* prv, int k, int s, int e) {
        if (e == s)
            return s;

        int mid = s + e >> 1;
        ll res = cur->l->sum - prv->l->sum;
        if (res >= k)
            return getKth(cur->l, prv->l, k, s, mid);
        else
            return getKth(cur->r, prv->r, k - res, mid + 1, e);
    }

public:
    PST(int n) : n(n) {}
    Node* build(int s, int e, const vector<int>& a) {
        if (s == e)
            return new Node(a[s]);
        int m = (s + e) / 2;
        return new Node(build(s, m, a), build(m + 1, e, a));
    }

    // range update
    Node* update(Node* node, int l, int r, int val) {
        return update(node, 0, n - 1, l, r, val);
    }
    // point update
    Node* update(Node* node, int i, ll val) {
        return update(node, 0, n - 1, i, val);
    }

    ll query(Node* node, int l, int r) {
        return query(node, 0, n - 1, l, r).sum;
    }
    ll getKth(Node* cur, Node* prv, int k) {
        return getKth(cur, prv, k, 0, n - 1);
    }
};
