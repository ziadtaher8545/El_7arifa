/* "The code quickly determines the node you will reach after taking $k$ steps
from a specific starting point in a directed graph (Functional Graph) using the Binary Lifting technique."
*/
struct FG {
    int n, LOG = 30;
    int comp_cnt = 0;

    vector<int> to, vis, comp, dist, in_cycle, pos, cycle_len;
    vector<vector<int>> up;

    FG(int n) : n(n) {
        to.resize(n + 1);
        vis.assign(n + 1, 0);
        comp.assign(n + 1, 0);
        dist.assign(n + 1, 0);
        in_cycle.assign(n + 1, 0);
        pos.assign(n + 1, 0);
        cycle_len.assign(n + 1, 0);
        up.assign(n + 1, vector<int>(LOG));
    }

    void add_edge(int u, int v) {
        to[u] = v;
    }

    void dfs(int u) {
        vis[u] = 1;
        int v = to[u];

        if (!vis[v]) {
            dfs(v);
            if (!in_cycle[u]) {
                dist[u] = dist[v] + 1;
                comp[u] = comp[v];
            }
        }
        else if (vis[v] == 1) {

            comp_cnt++;
            int cur = v, p = 0;
            while (true) {
                in_cycle[cur] = 1;
                comp[cur] = comp_cnt;
                pos[cur] = p++;
                dist[cur] = 0;
                cur = to[cur];
                if (cur == v) break;
            }
            cycle_len[comp_cnt] = p;
        }
        else {

            dist[u] = dist[v] + 1;
            comp[u] = comp[v];
        }

        vis[u] = 2;
    }

    void build() {

        for (int i = 1; i <= n; i++) {
            if (!vis[i]) dfs(i);
        }

        // 2. Binary Lifting بعد الـ DFS
        for (int i = 1; i <= n; i++)
            up[i][0] = to[i];

        for (int j = 1; j < LOG; j++) {
            for (int i = 1; i <= n; i++) {
                up[i][j] = up[up[i][j - 1]][j - 1];
            }
        }
    }

    int jump(int u, int k) {
        for (int i = 0; i < LOG; i++)
            if ((k >> i) & 1)
                u = up[u][i];
        return u;
    }

    int query(int a, int b) {
        if (comp[a] != comp[b]) return -1;

        if (!in_cycle[a]) {
            if (!in_cycle[b]) {

                if (dist[a] < dist[b]) return -1;
                int diff = dist[a] - dist[b];
                if (jump(a, diff) == b) return diff;
                return -1;
            } else {

                int d_to_cycle = dist[a];
                int entry_node = jump(a, d_to_cycle);
                int len = cycle_len[comp[a]];
                int d_in_cycle = (pos[b] - pos[entry_node] + len) % len;
                return d_to_cycle + d_in_cycle;
            }
        } else {

            if (!in_cycle[b]) return -1;
            int len = cycle_len[comp[a]];
            return (pos[b] - pos[a] + len) % len;
        }
    }
};

void solve() {
    int n; cin >> n;
    FG g(n);
    int q; cin >> q;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        g.add_edge(i, x);
    }
    g.build();
    while (q--) {
        int u, k;
        cin >> u >> k;
        cout << g.jump(u, k) << '\n';
    }
}
