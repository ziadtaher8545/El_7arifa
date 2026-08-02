#include "bits/stdc++.h"
#define el '\n'
#define ll long long
//#define int long long
#define Matrix vector<vector<int >>
#define Row vector<int >
using namespace std;

struct HopcroftKarp {
    // O(sqrt(V)*E)
    int n, m;
    vector<vector<int> > adj;
    vector<int> match, level;
    vector<bool> vis;

    HopcroftKarp(int n, int m) : n(n), m(m) {
        adj.resize(n);
        match.assign(n + m, -1);
        level.resize(n);
        vis.resize(n);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v + n);
    }

    bool bfs() {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (match[i] == -1) {
                level[i] = 0;
                q.push(i);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v: adj[u]) {
                if (match[v] == -1) {
                    return true;
                }
                if (level[match[v]] == -1) {
                    level[match[v]] = level[u] + 1;
                    q.push(match[v]);
                }
            }
        }
        return false;
    }

    bool dfs(int u) {
        vis[u] = true;
        for (int v: adj[u]) {
            if (match[v] == -1 || (!vis[match[v]] && level[match[v]] == level[u] + 1 && dfs(match[v]))) {
                match[u] = v;
                match[v] = u;
                return true;
            }
        }
        return false;
    }

    int maxMatching() {
        int ans = 0;
        while (bfs()) {
            fill(vis.begin(), vis.end(), false);
            for (int i = 0; i < n; i++) {
                if (match[i] == -1 && dfs(i)) {
                    ans++;
                }
            }
        }
        return ans;
    }
};


void solve() {
    int n, m, k;;
    cin >> n >> m >> k;
    HopcroftKarp T(n, m);
    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        T.addEdge(a, b);
    }
    cout << T.maxMatching() << el;
    for (int i = 0; i < n; i++)
        if (T.match[i] != -1) {
            cout << i + 1 << ' ' << T.match[i] - n + 1 << el;
        }
}

/*


2
4 7
2 9


 */
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;

    // freopen("fib.in", "r", stdin);
    ///   freopen("gracehopper.in", "w", stdout);
    // cin >> T;

    for (int i = 1; i <= T; i++)
        solve();
}
