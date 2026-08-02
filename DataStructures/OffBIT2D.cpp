template<class T>
class OffBIT2D {
    int n;
    bool initialized = false;

    vector<vector<int> > ys;
    vector<vector<T> > bit;

    int query_rank(int x, int y) {
        return upper_bound(ys[x].begin(), ys[x].end(), y) - ys[x].begin();
    }

    int update_rank(int x, int y) {
        auto it = lower_bound(ys[x].begin(), ys[x].end(), y);
        assert(it != ys[x].end() && *it == y);
        return int(it - ys[x].begin()) + 1;
    }

public:
    OffBIT2D(int _n) : n(_n) {
        ys.resize(n + 1);
        bit.resize(n + 1);
    }

    void init(vector<pair<int, int> > updates) {
        assert(!initialized);
        initialized = true;

        for (auto [x, y]: updates) {
            assert(1 <= x && x <= n);

            for (int xx = x; xx <= n; xx += xx & -xx) {
                ys[xx].push_back(y);
            }
        }

        for (int x = 1; x <= n; x++) {
            sort(ys[x].begin(), ys[x].end());
            ys[x].erase(unique(ys[x].begin(), ys[x].end()), ys[x].end());

            bit[x].assign(ys[x].size() + 1, T{});
        }
    }

    // add value to point (x, y)
    void add(int x, int y, T val) {
        assert(initialized);
        assert(1 <= x && x <= n);

        for (int xx = x; xx <= n; xx += xx & -xx) {
            int yy = update_rank(xx, y);

            for (; yy < (int) bit[xx].size(); yy += yy & -yy) {
                bit[xx][yy] += val;
            }
        }
    }

    // sum of points with px <= x and py <= y
    T pref(int x, int y) {
        assert(initialized);

        if (x <= 0) return 0;
        if (x > n) x = n;

        T res = 0;

        for (int xx = x; xx > 0; xx -= xx & -xx) {
            int yy = query_rank(xx, y);

            for (; yy > 0; yy -= yy & -yy) {
                res += bit[xx][yy];
            }
        }

        return res;
    }

    // sum inside rectangle:
    // x1 <= x <= x2 and y1 <= y <= y2
    T rect(int x1, int y1, int x2, int y2) {
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);

        return pref(x2, y2)
               - pref(x1 - 1, y2)
               - pref(x2, y1 - 1)
               + pref(x1 - 1, y1 - 1);
    }
};
