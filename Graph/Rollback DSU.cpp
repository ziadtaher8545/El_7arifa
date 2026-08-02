#include "bits/stdc++.h"
#define el '\n'
#define ll long long
#define int long long
#pragma GCC optimize ("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#pragma GCC optimize ("unroll-loops")
using namespace std;
struct DSU {
    vector<int> par, gp;
    stack<array<int, 5>> prev;
    int ans = 0;

    DSU(int n) {
        par.resize(n + 5);
        gp = vector<int>(n + 5, 1);
        std::iota(par.begin(), par.end(), 0);
        this->ans = n;
    }

    int getRoot(int u) {
        if (par[u] == u)return u;
        return getRoot(par[u]);
    }

    void merge(int u, int v) {
        v = getRoot(v), u = getRoot(u);
        if (u == v) {
              prev.push({-1, -1, -1, -1, ans});
            return;
        }
        if (gp[u] > gp[v])swap(u, v);

        prev.push({u, par[u], v, gp[v], ans});
        ans--;
        gp[v] += gp[u];
        par[u] = v;
    }

    void rollback() {
        auto s = prev.top();
        prev.pop();
        if (s[0] == -1) {
            return;
        }
        ans = s[4];
        par[s[0]] = s[1];
        gp[s[2]] = s[3];
    }
};
void solve() {
int n,q;
    cin>>n>>q;DSU d(n);
    vector<int>t;
    for (int i=0;i<q;i++) {
        string s;cin>>s;
        if (s[0]=='p') {
            t.push_back(d.prev.size());
        }
        else if (s[0]=='r') {

            if (t.size()) {
                while (d.prev.size() > t.back())
                    d.rollback();
            }
            if (t.size())
                t.pop_back();
            cout<<d.ans<<el;

        }
        else {
            int x,y;cin>>x>>y;
            d.merge(x,y);
            cout<<d.ans<<el;
        }
    }

}

/*


 */
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // freopen("milk.in", "r", stdin);
    //freopen("output.txt", "w", stdout);
   // cin >> T;
    for (int i = 1; i <= T; i++)
        solve();
}
