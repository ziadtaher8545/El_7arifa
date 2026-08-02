#include "bits/stdc++.h"
#define el '\n'
#define ll long long
#define int long long
using namespace std;
// Do not fight someone who still carries a living dream inside
// متي اصبح الكابوس لديك حلم تتمتع به ؟
static const long long INF = 4e18;

class FloydWarshall {
public:
    int n;
    vector<vector<long long> > d;
    vector<vector<int> > p;

    FloydWarshall(int n) : n(n) {
        d.assign(n, vector<long long>(n, INF));
        p.assign(n, vector<int>(n, -1));
        for (int i = 0; i < n; i++)
            d[i][i] = 0;
    }

    void addEdge(int u, int v, long long w) {
        d[u][v] = min(d[u][v], w);
    }

    void run() {
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                if (d[i][k] == INF) continue;
                for (int j = 0; j < n; j++) {
                    if (d[k][j] == INF) continue;
                    if (d[i][k] + d[k][j] < d[i][j]) {
                        d[i][j] = d[i][k] + d[k][j];
                        p[i][j] = k;
                    }
                }
            }
        }
        detectNegativeCycles();
    }

    void detectNegativeCycles() {
        for (int t = 0; t < n; t++) {
            if (d[t][t] < 0) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (d[i][t] < INF && d[t][j] < INF) {
                            d[i][j] = -INF;
                        }
                    }
                }
            }
        }
    }

    vector<int> getPath(int u, int v) {
        vector<int> path;
        if (d[u][v] == INF || d[u][v] == -INF) return path;
        build(u, v, path);
        return path;
    }

    long long getDistance(int u, int v) {
        return d[u][v];
    }

private:
    void build(int u, int v, vector<int> &path) {
        if (p[u][v] == -1) {
            path.push_back(u);
            if (u != v) path.push_back(v);
            return;
        }
        int k = p[u][v];
        build(u, k, path);
        path.pop_back();
        build(k, v, path);
    }
};

void solve() {
    int n, m;
    int q;

    cin >> n >> m;
    cin >> q;
    FloydWarshall f(n);
    f.run();
    for (int i = 0; i < m; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        x--;
        y--;
        f.addEdge(x, y, c);
        f.addEdge(y, x, c);
    }
    f.run();

    while (q--) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        if (f.getDistance(x, y) == INF)
            cout << -1;
        else
            cout << f.getDistance(x, y);
        cout << el;
    }
}

/*



 */
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    //freopen("help.in", "r", stdin);
    //freopen("output.txt", "w", stdout);
    //  cin >> T;
    for (int i = 1; i <= T; i++)
        solve();
}
