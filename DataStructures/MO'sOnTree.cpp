#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class MoOnTree
{
public:
    int n, q, SQ, timer = -1;
    const int LOG = 20;

    vector<int> dep, in, out, w;
    vector<vector<int>> up;
    vector<vector<array<int, 2>>> adj;

    struct query {
        int l, r, idx, lc;
    };

    vector<int> v, fr, vis;
    vector<query> Q;
    long long res = 0;

    MoOnTree(int n) {
        this->n = n;
        dep.resize(n);
        in.resize(n);
        out.resize(n);
        w.resize(n);
        up.resize(n, vector<int>(LOG));
        adj.resize(n);
    }

    void addEdge(int u, int v, int wt) {
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }

    void build(int u, int p = 0) {
        in[u] = ++timer;
        up[u][0] = p;

        for (int k = 1; k < LOG; k++)
            up[u][k] = up[up[u][k - 1]][k - 1];

        for (auto& [v, wt] : adj[u]) {
            if (v == p) continue;
            dep[v] = dep[u] + 1;
            w[v] = wt;
            build(v, u);
        }

        out[u] = ++timer;
    }

    int kthAnc(int u, int k) {
        if (dep[u] < k) return -1;

        for (int i = LOG - 1; i >= 0; i--)
            if ((k >> i) & 1)
                u = up[u][i];

        return u;
    }

    int LCA(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);

        int k = dep[u] - dep[v];
        u = kthAnc(u, k);

        if (u == v) return u;

        for (int i = LOG - 1; i >= 0; i--)
            if (up[u][i] != up[v][i])
                u = up[u][i], v = up[v][i];

        return up[u][0];
    }

    void init(vector<int>& a) {
        v = a;
        SQ = sqrt(a.size()) + 1;
        fr.resize(a.size());
        vis.resize(a.size());
        q = 0;
    }

    void add(int u) {
        if (w[u] > n) return;
        fr[w[u]]++;
        while (fr[res]) res++;
    }

    void del(int u) {
        if (w[u] > n) return;
        fr[w[u]]--;
        if (!fr[w[u]])
            res = min(res, (long long)w[u]);
    }

    void cal(int ind) {
        int u = v[ind];
        if (!vis[u]) add(u);
        else del(u);
        vis[u] ^= 1;
    }

    void add_query(int l, int r, int lc) {
        Q.push_back({l, r, q++, lc});
    }

    vector<long long> process() {
        vector<long long> ans(q);

        sort(Q.begin(), Q.end(), [&] (query& a, query& b) {
            if (a.l / SQ != b.l / SQ)
                return a.l / SQ < b.l / SQ;
            return a.r < b.r;

            if ((a.l / SQ) & 1)
                return a.r > b.r;
            return a.r < b.r;
        });

        int l = 0, r = -1;

        for (auto [lq, rq, idx, lc] : Q) {

            while (l > lq) cal(--l);
            while (r < rq) cal(++r);
            while (l < lq) cal(l++);
            while (r > rq) cal(r--);

            ans[idx] = res;
        }

        return ans;
    }
};
void solve(...) {
    int n, m;
    cin >> n >> m;

    MoOnTree tr(n);
    for (int i = 1; i < n; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        tr.addEdge(u, v, wt);
    }
    tr.build(0);

    vector<int>a(2 * n);
    for (int u = 0; u < n; u++)
        a[tr.in[u]] = a[tr.out[u]] = u;

    tr.init(a);
    while (m--) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        if (tr.in[u] > tr.in[v]) swap(u, v);
        int lc = tr.LCA(u, v);

        int l = tr.out[u], r = tr.in[v];
        if (lc == u)
            l = tr.in[u] + 1;

        tr.add_query(l, r, lc);
    }
    auto ans = tr.process();
    for (auto& x : ans)
        cout << x << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);

    int _t = 1;
    // cin >> _t;
    for (int i = 1; i <= _t; i++) {
        // cout << "Case #" << i << ": ";
        solve(i), cout << '\n';
    }
}
