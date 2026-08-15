#include "bits/stdc++.h"
#define el '\n'
#define ll long long
//#define int long long
#define Matrix vector<vector<int >>
#define Row vector<int >
using namespace std;
const int N = 1e6;
int fre[N];
const int skip=1e5+50;
template<typename T = int>
class MO_on_tree {
public:
    vector<vector<int> > adj, up;
    vector<int> dep;
    int SQ, q;
    T ans;

    struct Query {
        int l, r, idx, lc;
    };

    vector<Query> Q;
    vector<T> a;
    vector<int> vis, in, out, id;
    int timer;

    void dfs(int u, int p) {
        in[u] = ++timer;
        id[timer] = u;
        for (auto &v: adj[u]) {
            if (p == v)continue;
            dep[v] = dep[u] + 1;
            up[v][0] = u;
            for (int j = 1; j < 20; j++) {
                up[v][j] = up[up[v][j - 1]][j - 1];
            }
            dfs(v, u);
        }
        out[u] = ++timer;
        id[timer] = u;
    }


    void remove(int u) {
        if(a[u]>=skip)
        return ;
        fre[a[u]]--;
        if (fre[a[u]] == 0&&ans>a[u])
            ans=a[u];
    }

    void add(int u) {
        if (a[u]>=skip)
            return ;
        fre[a[u]]++;
        while (fre[ans])
            ans++;
    }

    void check(int u) {
        // If (u) occurs twice, then don't consider its value
        if (vis[u] /*&& (--fre[a[u]] == 0)*/) {
            // ans--;
            remove(u);
        } else if (!vis[u] /*&& !fre[a[u]]++*/) {
            add(u);
        }
        vis[u] ^= 1;
    }

    T calc(...) {
        return ans;
    }

    MO_on_tree(vector<T> &a, vector<vector<int> > &adj) {
        q = 0;
        ans = 0;
        timer = 0;
        this->a = a;
        this->adj = adj;
        int n = a.size();
        in = out = dep = vis = vector<int>(n + 5);
        SQ = sqrt(n << 1);
        id.resize(2 * n + 5);
        up = vector<vector<int> >(n + 5, vector<int>(20));
        dfs(1, 0);
    }

    int LCA(int u, int v) {
        if (dep[u] < dep[v])swap(u, v);
        int k = dep[u] - dep[v];
        for (int i = 0; i < 20; i++) {
            if (k & (1 << i)) {
                u = up[u][i];
            }
        }
        if (u == v) {
            return u;
        }
        for (int i = 19; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }

    void add_query(int l, int r, int lc) {
        Q.push_back({l, r, q++, lc});
    }

    vector<int> process() {
        vector<T> ans_query(q);
        std::sort(Q.begin(), Q.end(), [&](Query &x, Query &y) {
            if (x.l / SQ != y.l / SQ) {
                return x.l / SQ < y.l / SQ;
            }
            return x.r < y.r;
        });
        int curL = 1, curR = 0;
        for (int i = 0; i < Q.size(); i++) {
            int L = Q[i].l, R = Q[i].r, lc = Q[i].lc, idx = Q[i].idx;
            while (curL < L) check(id[curL++]);
            while (curL > L) check(id[--curL]);
            while (curR < R) check(id[++curR]);
            while (curR > R) check(id[curR--]);
            int u = id[curL], v = id[curR];
          //  if (lc != u and lc != v) check(lc);
            ans_query[idx] = calc();
          //  if (lc != u and lc != v) check(lc);
        }
        for (int i = curL; i <= curR; i++)check(id[i]);
        return ans_query;
    }
};
void dfs(int u,int p,vector<int>&a,vector<vector<pair<int,int>>>&ad) {
    for (auto [ x,c]:ad[u])if (x!=p) {
        a[x]=c;
        dfs(x,u,a,ad);
    }
}
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    int q;int id=1;
    cin >> q;
    vector<vector<pair<int,int>> > ad(n + 1);
    vector<vector<int> > ad2(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int x, y,c;
        cin >> x >> y>>c;
        ad2[x].push_back(y);
        ad2[y].push_back(x);

        ad[x].push_back({y,c});
        ad[y].push_back({x,c});
    }
    a[1]=1e9;
    dfs(1,0,a,ad);
    // for (int i=1;i<=n;i++)
    //     cout<<i<<' '<<a[i]<<el;
    MO_on_tree<int> mo(a, ad2);
 for (int i=0;i<q;i++){
        int u, v;
        cin >> u >> v;
        int lc = mo.LCA(u, v);
        if (mo.in[u] > mo.in[v])swap(u, v);
        int l, r;
        if (lc == u) {
            l = mo.in[u]+1;
            r = mo.in[v];
        } else {
            l = mo.out[u];
            r = mo.in[v];
        }
        mo.add_query(l, r, lc);
    }
    auto x = mo.process();
   for (int i=0;i<q;i++)

        cout << x[i] << el;
}


/*
7 6
2 1 1
3 1 2
1 4 0
4 5 1
5 6 3
5 7 4
1 3
4 1
2 4
2 5
3 5
3 7
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
