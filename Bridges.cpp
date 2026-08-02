
const int N = 2e5 + 5;
vector<int> ad[N];
int deg[N], low[N], par[N], timer;

class Bridges {
    vector<bool> vis;
    void dfs(int u, int p) {
        vis[u] = 1;
        deg[u] = low[u] = ++timer;
        for (auto &to : ad[u]) {
            if (to == p) continue;
            if (vis[to]) {
                low[u] = min(low[u], deg[to]);
            } else {
                dfs(to, u);
                low[u] = min(low[u], low[to]);
                if (low[to] > deg[u]) {
                    // edge between u and v is bridge --------
                }
            }
        }
    }
public:
    Bridges(int n) {
        vis.assign(n + 1, false);
        timer = 0;
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) dfs(i, -1);
        }
    }
};
