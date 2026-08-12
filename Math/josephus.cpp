
/*
 * What does this code do?
 * Solves a fast, special case of the Josephus Problem (where k = 2).
 * 
 * Game Rules:
 * 'n' people stand in a circle. Every 2nd person is eliminated
 * sequentially until only one survivor remains.
 */

#include "bits/stdc++.h"
#define el '\n'
#define ll long long
#define int long long
#define Matrix vector<vector<int >>
#define Row vector<int >
using namespace std;
const int N = 5e6 + 4, mod = 998244353;
long long josephus(long long n, long long k) {
    if (n == 1) return 1;
    if (k <= (n + 1) / 2) {
        if (2 * k <= n) return 2 * k;
        return 1;
    }

    long long res = josephus(n / 2, k - (n + 1) / 2);
    if (n % 2 == 0) return 2 * res - 1;
    return 2 * res + 1;
}
void solve() {
  int n,k;
    cin>>n>>k;
    cout<<josephus(n,k)<<el;
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
    cin >> T;

    for (int i = 1; i <= T; i++)
        solve();
}
