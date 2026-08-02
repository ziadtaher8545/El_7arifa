#include "bits/stdc++.h"

#define el '\n'
#define ll long long
#define int  long long
#pragma GCC optimize ("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#pragma GCC optimize ("unroll-loops")
using namespace std;const int N = 2e5 + 5, n22 = 501, mod = 1e9 + 7, M = 1e9 + 7, base = 31;

ll pw1[N], pw2[N];
const ll bs1 = 131, bs2 = 137, mod2 = 1e9 + 9;

ll ipw1[N], ipw2[N];
const int Log = 23;
int   anc[N][Log], lvl[N];
int P[N];
vector<int>ad[N];char a[N];
pair<int,int>down[N],up[N];

void build_ancestor(int node, int par) {

    ////
    lvl[node] = lvl[par] + 1;
    anc[node][0] = par;
    for (int i = 1; i < Log; i++) {
        int p = anc[node][i - 1];
        anc[node][i] = anc[p][i - 1];
    }
    ////
    for (auto x : ad[node]) {
        if (x != par) {
            build_ancestor(x, node);
        }
    }


}
int kthancestor(int node, int k) {
    for (int i = Log - 1; i >= 0; i--) {
        if ((k >> i) & 1)
            node = anc[node][i];
    }
    return node;
}
int LCA(int u, int v) {
    if (lvl[u] < lvl[v]) {
        swap(u, v);
    }
    u = kthancestor(u, lvl[u] - lvl[v]);
    // same level
    if (u == v)return v;
    for (int i = Log - 1; i >= 0; i--) {
        if (anc[u][i] != anc[v][i]) {
            u = anc[u][i];
            v = anc[v][i];
        }
    }
    return anc[v][0];
}
int dis(int u, int v) {
    int lca = LCA(u, v);
    return lvl[u] + lvl[v] - 2 * lvl[lca];
}
ll power_fn(ll b, ll exp, ll m) {
    ll res = 1; b %= m;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * b) % m;
        b = (b * b) % m;
        exp /= 2;
    }
    return res;
}
ll modInverse(ll n, ll m) {
    return power_fn(n, m - 2, m);
}
// خلاص هانت

void init() {
    pw1[0] = pw2[0] = 1;
    ipw1[0] = ipw2[0] = 1;
    ll inv1 = modInverse(bs1, mod);
    ll inv2 = modInverse(bs2, mod2);
    for (int i = 1; i < N; i++) {
        pw1[i] = pw1[i - 1] * bs1 % mod;
        pw2[i] = pw2[i - 1] * bs2 % mod2;
        ipw1[i] = ipw1[i - 1] * inv1 % mod;
        ipw2[i] = ipw2[i - 1] * inv2 % mod2;
    }
}

struct Hash {
private:
    vector<pair<int, int> > pre;

public:
    Hash(string &s) {
        pre.assign(s.size(), {0, 0});
        int h1 = 0, h2 = 0;
        for (int i = 0; i < s.size(); i++) {
            int x = s[i] ;
            h1 = (h1 * bs1 % mod + x) % mod;
            h2 = (h2 * bs2 % mod2 + x) % mod2;
            pre[i] = {h1, h2};
        }
    }

    pair<int, int> get(int l, int r) {
        pair<int, int> ret = pre[r];
        int sz = r - l + 1;
        if (l) {
            ret.first = (ret.first - pre[--l].first * pw1[sz] % mod + mod) % mod;
            ret.second = (ret.second - pre[l].second * pw2[sz] % mod2 + mod2) % mod2;
        }
        return ret;
    }
};
pair<int,int>conc(pair<int,int>s1,pair<int,int>s2,int sz2) {
    auto &[h1,h2]=s1;
    h1 = (h1 * pw1[sz2]) % mod;
    h2 = (h2 * pw2[sz2]) % mod2;
    h1 = (h1 + s2.first) % mod;
    h2 = (h2 + s2.second) % mod2;
    return s1;
}

void dfs(int u,int p,int dp) {
     P[u]=p;
     down[u]=conc(down[p],{a[u],a[u]},1);
     up[u]=conc({a[u],a[u]},up[p],dp);
     for (int x:ad[u])if (x!=p) {
         dfs(x,u,dp+1);
     }
}
pair<int,int> path(int x,int y,int lc) {
    pair<int,int> ans1 = down[x];
    int dis = lvl[x] - lvl[lc] + 1;

    if (P[lc]) {
        auto [h1, h2] = ans1;
        auto [h3, h4] = down[P[lc]];
        h3 = (h3 * pw1[dis]) % mod;
        h4 = (h4 * pw2[dis]) % mod2;
        h1 = (h1 - h3 + mod) % mod;
        h2 = (h2 - h4 + mod2) % mod2;
        ans1 = {h1, h2};
    }

    pair<int,int> ans2 = {0, 0};
    ans2.first = (up[y].first - up[lc].first + mod) % mod * ipw1[lvl[lc]] % mod;
    ans2.second = (up[y].second - up[lc].second + mod2) % mod2 * ipw2[lvl[lc]] % mod2;

    return conc(ans2, ans1, dis);
}
// pair<int,int>path(int x,int y,int lc) {
//     // lc->x
//     pair<int,int>ans1=down[x];int dis=lvl[x]-lvl[lc]+1;
//     if (P[lc]) {
//         auto [h1,h2]=ans1;
//         auto [h3,h4]=down[P[lc]];
//         h3=(h3*pw1[dis])%mod;
//         h4=(h4*pw2[dis])%mod2;
//         h1=(h1-h3+mod)%mod;
//         h2=(h2-h4+mod2)%mod2;
//         ans1={h1,h2};
//     }
//     // y-lc
//     pair<int,int> ans2 = {0, 0};
//     if (lvl[y] > lvl[lc]) {
//          ans2.first = (up[y].first - up[lc].first + mod) % mod * ipw1[lvl[lc]] % mod;
//         ans2.second = (up[y].second - up[lc].second + mod2) % mod2 * ipw2[lvl[lc]] % mod2;
//     }
//     return conc(ans2,ans1,dis);
// }
void solve(int t) {
int n;cin>>n;
    for (int i=1;i<=n;i++)cin>>a[i];
    for (int i=0;i<n-1;i++) {
        int x,y;cin>>x>>y;
        ad[x].push_back(y);
        ad[y].push_back(x);
    }
    dfs(1,0,0);
    build_ancestor(1,0);
    int q;cin>>q;
    while (q--) {
        int x,y;cin>>x>>y;
        int lc=LCA(x,y);
        pair<int,int>yTOx=path(x,y,lc);
        pair<int,int>xTOy=path(y,x,lc);
        if (yTOx == xTOy) cout << 1 << el;
        else cout << 0 << el;
    }
}

/*


*/
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // freopen("banana.in", "r", stdin);
    //freopen("output.txt", "w", stdout);
    //cin >> T;
    // cin.ignore();
   init();
    for (int i = 1; i <= T; i++)
        solve(i);
}
