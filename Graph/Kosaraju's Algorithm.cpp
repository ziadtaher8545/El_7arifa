#include "bits/stdc++.h"
#define el '\n'
#define ll long long
#define int long long
using namespace std;
const int N = 100;
vector<int> ad[N], adtr[N];
vector<vector<int> > ans;
vector<int> vis1(N), vis2(N);
stack<int> s;

void dfs1(int u) {
    vis1[u] = 1;
    for (auto x: ad[u]) {
        if (!vis1[x]) {
            dfs1(x);
        }
    }
    s.push(u);
}

vector<int> r;

void dfs2(int u) {
    vis2[u] = 1;
    r.push_back(u);

    for (auto x: adtr[u]) {
        if (!vis2[x]) {
            dfs2(x);
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        ad[x].push_back(y);
        adtr[y].push_back(x);
    }
    for (int i = 1; i <= n; i++)
        if (!vis1[i]) {
            dfs1(i);
        }
    while (s.size()) {
        if (vis2[s.top()])
            s.pop();
        else {
            dfs2(s.top()), s.pop();
            ans.push_back(r);
            r.clear();
        }
    }

    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << i + 1 << el;
        for (int j: ans[i]) {
            cout << j << ' ';
        }
        cout << el;
    }
}

/*


8 14
1 2
2 3
3 1
4 2
4 3
4 5
5 4
8 8
8 5
5 6
6 3
6 7
7 6
8 7

 **/

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;


    //freopen("help.in", "r", stdin);
    //    freopen("output.txt", "w", stdout);
    //cin >> T;
    for (int i = 1; i <= T; i++)
        solve();
}
