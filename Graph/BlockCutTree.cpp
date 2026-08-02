#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1E6 + 5;

int timer, scc, sz;
vector<int>g[N], bcc[N], sk;
int tin[N], low[N], art[N], id[N];

void dfs(int u, int p) {
    tin[u] = low[u] = ++timer;
    int child = 0;

    sk.push_back(u);
    for (auto v : g[u]) {
        if (!tin[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);

            if (low[v] >= tin[u]) {
                sz++;
                int x;
                do {
                    x = sk.back();
                    sk.pop_back();
                    bcc[x].push_back(sz);
                } while (x ^ v);
                bcc[u].push_back(sz);
            }
        }
        else if (v != p) {
            low[u] = min(low[u], tin[v]);
        }
    }
}

class Tree
{
public:
    int n;
    vector<int> dep;
    const int LOG = 20;
    vector<vector<int>> up;
    vector<vector<int>> adj;
    Tree(int n) : adj(n), dep(n), up(n, vector<int>(LOG)) {
        this->n = n;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void build(int u, int p = 0) {
        up[u][0] = p;
        for (int k = 1; k < LOG; k++)
            up[u][k] = up[up[u][k - 1]][k - 1];

        for (auto& v : adj[u]) {
            if (v == p)
                continue;
            dep[v] = dep[u] + 1;
            build(v, u);
        }
    }

    int kthAnc(int u, int k) {
        if (dep[u] < k)
            return -1;

        for (int i = LOG - 1; i >= 0; --i)
            if ((k >> i) & 1)
                u = up[u][i];

        return u;
    }

    int LCA(int u, int v) {
        if (dep[u] < dep[v])
            swap(u, v);

        int k = dep[u] - dep[v];
        u = kthAnc(u, k);
        if (u == v)
            return u;

        for (int i = LOG - 1; i >= 0; --i)
            if (up[u][i] != up[v][i])
                u = up[u][i], v = up[v][i];

        return up[u][0];
    }

    int dist(int u, int v) {
        int lca = LCA(u, v);
        return dep[u] + dep[v] - 2 * dep[lca];
    }
    bool query(int u, int v, int c) {
        return dist(u, c) + dist(c, v) != dist(u, v);
    }
};

void solve(...) {
    int n, m, q;
    cin >> n >> m >> q;

    while (m--) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, -1);
    Tree t(n * 2 + 5);
    for (int u = 1; u <= n; u++) {
        if (bcc[u].size() > 1) {
            id[u] = ++sz;
            art[id[u]] = 1;

            for (auto v : bcc[u]) {
                t.addEdge(id[u], v);
            }
        }
        else if (bcc[u].size() == 1) id[u] = bcc[u][0];
    }

    t.build(1);
    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;

        if (a == c || b == c)
            cout << "NO\n";
        else if (!art[id[c]])
            cout << "YES\n";
        else
            cout << (t.query(id[a], id[b], id[c]) ? "YES\n" : "NO\n");
    }
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
