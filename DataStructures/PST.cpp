struct Node
{
    Node *l, *r;
    ll sum;

    Node(ll val = 0) : l(nullptr), r(nullptr), sum(val) {}
    Node(Node *l, Node *r) : l(l), r(r), sum(0)
    {
        if (l)
            sum += l->sum;
        if (r)
            sum += r->sum;
    }
};

class PST
{
private:
    int n;

    ll getSum(Node *node) { return node ? node->sum : 0; }
    Node *getL(Node *node) { return node ? node->l : nullptr; }
    Node *getR(Node *node) { return node ? node->r : nullptr; }

    Node *update(Node *node, int s, int e, int idx, ll val)
    {
        if (s == e)
            return new Node(val);

        int mid = s + (e - s) / 2;
        Node *cur = new Node();
        if (node)
        {
            cur->l = node->l;
            cur->r = node->r;
        }

        if (idx <= mid)
            cur->l = update(getL(cur), s, mid, idx, val);
        else
            cur->r = update(getR(cur), mid + 1, e, idx, val);

        cur->sum = getSum(cur->l) + getSum(cur->r);
        return cur;
    }

    ll query(Node *node, int s, int e, int l, int r)
    {
        if (!node || r < s || e < l)
            return 0;
        if (l <= s && e <= r)
            return node->sum;

        int mid = s + (e - s) / 2;
        return query(node->l, s, mid, l, r) + query(node->r, mid + 1, e, l, r);
    }

    int getKth(Node *cur, Node *prv, int s, int e, int k)
    {
        if (s == e)
            return s;

        int mid = s + (e - s) / 2;

        ll left_sum = getSum(getL(cur)) - getSum(getL(prv));

        if (left_sum >= k)
            return getKth(getL(cur), getL(prv), s, mid, k);
        else
            return getKth(getR(cur), getR(prv), mid + 1, e, k - left_sum);
    }

public:
    PST(int n) : n(n) {}

    Node *build(int s, int e, const vector<int> &a)
    {
        if (s == e)
            return new Node(a[s]);
        int mid = s + (e - s) / 2;
        return new Node(build(s, mid, a), build(mid + 1, e, a));
    }

    Node *update(Node *node, int idx, ll val)
    {
        return update(node, 0, n - 1, idx, val);
    }

    ll query(Node *node, int l, int r)
    {
        return query(node, 0, n - 1, l, r);
    }

    int getKth(Node *cur, Node *prv, int k)
    {
        return getKth(cur, prv, 0, n - 1, k);
    }
};
