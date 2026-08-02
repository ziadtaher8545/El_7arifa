class SegmentTree {
private:
    int size = 1;

    struct Node {
        ll sum, lazy;
        bool isLazy;

        Node() : sum(0), lazy(0), isLazy(false) {}
        Node(ll val) : sum(val), lazy(0), isLazy(false) {}

        void apply(int lx, int rx, ll val) {
            sum += val * (rx - lx + 1);
            lazy += val;
            isLazy = true;      
        }

        void merge(const Node& lf, const Node& ri) {
            sum = lf.sum + ri.sum;
        }
    };

    vector<Node> seg;

    void propagate(int nd, int lx, int rx) {
        if (!seg[nd].isLazy) return;

        if (lx != rx) {
            int mid = (lx + rx) >> 1, lf = 2 * nd + 1, ri = 2 * nd + 2;
            seg[lf].apply(lx, mid, seg[nd].lazy);
            seg[ri].apply(mid + 1, rx, seg[nd].lazy);
        }
        seg[nd].lazy = 0;
        seg[nd].isLazy = false;
    }

    void build(int nd, int lx, int rx, vector<int>& a) {
        if (lx == rx) {
            if (lx < a.size()) {
                seg[nd] = Node(a[lx]);
            }
            return;
        }

        int mid = (lx + rx) >> 1, lf = 2 * nd + 1, ri = 2 * nd + 2;
        build(lf, lx, mid, a);
        build(ri, mid + 1, rx, a);
        seg[nd].merge(seg[lf], seg[ri]);
    }

    void update(int nd, int lx, int rx, int l, int r, ll val) {
        if (lx > r || rx < l) return;
        if (lx >= l && rx <= r) {
            seg[nd].apply(lx, rx, val);
            return;
        }
        
        propagate(nd, lx, rx);
        int mid = (lx + rx) >> 1, lf = 2 * nd + 1, ri = 2 * nd + 2;
        update(lf, lx, mid, l, r, val);
        update(ri, mid + 1, rx, l, r, val);
        seg[nd].merge(seg[lf], seg[ri]);
    }

    Node query(int nd, int lx, int rx, int l, int r) {
        if (lx > r || rx < l) return Node();
        if (lx >= l && rx <= r) return seg[nd];

        propagate(nd, lx, rx);
        int mid = (lx + rx) >> 1, lf = 2 * nd + 1, ri = 2 * nd + 2;

        Node ret;
        ret.merge(query(lf, lx, mid, l, r), query(ri, mid + 1, rx, l, r));
        return ret;
    }

public:
    SegmentTree(vector<int>& a) {
        while (size < a.size())
            size <<= 1;
        seg.assign(2 * size, Node());
        build(0, 0, size - 1, a);
    }

    void update(int l, int r, ll val) {
        update(0, 0, size - 1, l, r, val);
    }

    ll query(int l, int r) {
        return query(0, 0, size - 1, l, r).sum;
    }
};
