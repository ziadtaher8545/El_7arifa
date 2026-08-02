class SegmentTree
{
private:
    int size = 1;

    struct Node
    {
        ll mn = 1e9, mx = -1e9;
        void apply(ll val) {
            mn = mx = val;
        }
        void merge(const Node& l, const Node& r) {
            mn = min(l.mn, r.mn);
            mx = max(l.mx, r.mx);
        }
    };

    vector<Node> seg;
    void build(int nd, int lx, int rx, vector<int>& a) {
        if (lx == rx) {
            if (lx < a.size()) {
                seg[nd].apply(a[lx]);
            }
            return;
        }

        int mid = (lx + rx) >> 1, lf = 2 * nd + 1, ri = 2 * nd + 2;
        build(lf, lx, mid, a);
        build(ri, mid + 1, rx, a);

        seg[nd].merge(seg[lf], seg[ri]);
    }

    void update(int nd, int lx, int rx, int i, ll val) {
        if (lx == rx)
            return void(seg[nd].apply(val));

        int mid = (lx + rx) >> 1, lf = 2 * nd + 1, ri = 2 * nd + 2;
        if (i <= mid)
            update(lf, lx, mid, i, val);
        else
            update(ri, mid + 1, rx, i, val);

        seg[nd].merge(seg[lf], seg[ri]);
    }

    int find_first(int nd, int lx, int rx, int l, int r, ll val) {
        if (lx > r || l > rx || seg[nd].mn > val)
            return -1;
        if (lx == rx)
            return lx;

        int mid = (lx + rx) >> 1, lf = 2 * nd + 1, ri = 2 * nd + 2;
        int res = find_first(lf, lx, mid, l, r, val);
        if (res != -1)
            return res;
        return find_first(ri, mid + 1, rx, l, r, val);
    }
    int find_last(int nd, int lx, int rx, int l, int r, ll val) {
        if (lx > r || l > rx || seg[nd].mx < val)
            return -1;
        if (lx == rx)
            return lx;

        int mid = (lx + rx) >> 1, lf = 2 * nd + 1, ri = 2 * nd + 2;
        int res = find_last(ri, mid + 1, rx, l, r, val);
        if (res != -1)
            return res;
        return find_last(lf, lx, mid, l, r, val);
    }

    Node query(int nd, int lx, int rx, int l, int r) {
        if (lx > r || l > rx)
            return Node();
        if (lx >= l && rx <= r)
            return seg[nd];

        int mid = (lx + rx) >> 1, lf = 2 * nd + 1, ri = 2 * nd + 2;
        Node ret;
        ret.merge(query(lf, lx, mid, l, r), query(ri, mid + 1, rx, l, r));
        return ret;
    }

public:
    SegmentTree(vector<int>& a) {
        while (size < a.size())
            size *= 2;
        seg.assign(2 * size, Node());
        build(0, 0, size - 1, a);
    }

    void update(int i, ll val) {
        update(0, 0, size - 1, i, val);
    }

    int find_first(int l, int r, ll val) {
        return find_first(0, 0, size - 1, l, r, val);
    }
    int find_last(int l, int r, ll val) {
        return find_last(0, 0, size - 1, l, r, val);
    }
    Node query(int l, int r) {
        return query(0, 0, size - 1, l, r);
    }
};
