#include "bits/stdc++.h"
#define el '\n'
#define ll long long
//#define int long long
#define Matrix vector<vector<int >>
#define Row vector<int >
using namespace std;
const int M = 1e9 + 7, N = 1e6 + 5;

struct DSU {
private:
    vector<int> par, size;

public:
    DSU(int n) {
        par.resize(n + 5);
        size.resize(n + 5, 1);
        std::iota(par.begin(), par.end(), 0);
    }

    int getRoot(int u) {
        if (u == par[u])return u;
        return par[u] = getRoot(par[u]);
    }

    bool sameSet(int u, int v) {
        return getRoot(u) == getRoot(v);
    }

    void merge(int u, int v) {
        u = getRoot(u);
        v = getRoot(v);
        if (u == v)
            return;
        if (size[u] > size[v]) swap(u, v);
        par[u] = v;
        size[v] += size[u];
    }
};

void solve() {
    int n, m, Q;
    cin >> n >> m >> Q;
    vector<array<int, 2> > v;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        v.push_back({x, y});
    }
    vector<pair<int, int> > q(Q);
    vector<int> L(Q), R(Q), ans(Q);
    for (int i = 0; i < Q; i++) {
        int x, y;
        L[i] = 0, R[i] = m - 1;
        ans[i] = -1;
        cin >> x >> y;
        q[i] = {x, y};
    }
    for (int u = 0; u < 40; u++) {
        vector<vector<int>> mid(m);
        for (int i = 0; i < Q; i++) {
            if (L[i] <= R[i]) {
                int MID = (L[i] + R[i]) / 2;
                mid[MID].push_back(i);
            }
        }
        DSU d(n);
        for (int i = 0; i < m; i++) {
            auto [x,y] = v[i];
            d.merge(x, y);
            for (auto idx: mid[i]) {
                auto [X,Y] = q[idx];
                if (d.sameSet(X, Y)) {
                    ans[idx] = i + 1;
                    R[idx] = i - 1;
                } else {
                    L[idx] = i + 1;
                }
            }
        }
    }
    for (int i = 0; i < Q; i++)
        cout << (q[i].first==q[i].second?0:ans[i] )<< el;
}


/*


 */
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;

    // freopen("milk.in", "r", stdin);
    //freopen("output.txt", "w", stdout);
    //  cin >> T;

    for (int i = 1; i <= T; i++)
        solve();
}
