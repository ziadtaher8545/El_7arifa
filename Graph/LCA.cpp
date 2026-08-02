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

    bool isOnPath(int u, int v, int x) {
        return dist(u, x) + dist(x, v) == dist(u, v);
    }

};
