#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
const ll INF = 1000000000000000005LL;
using Row = vector<ll>;
using Matrix = vector<Row>;
 
Matrix multiply(const Matrix& A, const Matrix& B) {
    int n = A.size();
    int m = B[0].size();
    int p = B.size();
 
    Matrix C(n, Row(m, INF));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < p; k++)
                C[i][j] = min(C[i][j], A[i][k] + B[k][j]);
 
    return C;
}
Matrix exp(Matrix& A, ll p) {
    int n = A.size();
    Matrix res(n, Row(n, INF));
    for (int i = 0; i < n; i++)
        res[i][i] = 0;
 
    while (p) {
        if (p & 1)
            res = multiply(res, A);
        A = multiply(A, A);
        p >>= 1;
    }
    return res;
}
void solve(...) {
    int n, m, k;
    cin >> n >> m >> k;
 
    Matrix adj(n, Row(n, INF));
 
    while (m--) {
        ll u, v, c;
        cin >> u >> v >> c;
        --u, --v;
        adj[u][v] = min(c, adj[u][v]);
    }
 
    auto res = exp(adj, k)[0][n-1];
    if (res >= INF)
        cout << -1;
    else
        cout << res;
 
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
