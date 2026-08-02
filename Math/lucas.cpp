#include "bits/stdc++.h"
#include <unordered_map>
#define ll long long
#define el '\n'
#define int ll
using namespace std;
const ll N = 2e6 + 55, mod = 2 * 1e6 + 3, M = 2 * 1e6 + 3;
ll power(ll n, ll p, ll mod) {
    if (p == 0)
        return 1;

    ll a = power(n, p / 2, mod);
    a = (a * a) % mod;

    if (p % 2 == 1)
        return (a * (n % mod)) % mod;
    else
        return a;
}
vector<int>fact(N + 4), factinv(N + 4);

void pre() {
    fact[0] = 1;
    for (int i = 1; i < M; i++) fact[i] = fact[i - 1] * i % M;
    factinv[M - 1] = power(fact[M - 1], M - 2, M);
    for (int i = M - 2; i >= 0; i--) factinv[i] = factinv[i + 1] * (i + 1) % M;
}

int ncr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * factinv[r] % M * factinv[n - r] % M;
}

int lucas(int n, int r) {
    int res = 1;
    while (n || r) {
        int ni = n % M, ri = r % M;
        res = res * ncr(ni, ri) % M;
        n /= M, r /= M;
    }
    return res;
}

int s_b(int st, int b) {
    return ncr(st + b, st);
}
int sum(int y1, int y2) {
    int s = (y2 * (y2 + 1) / 2);
    y1--;
    int s2 = (y1 * (y1 + 1) / 2);
    return ((s % M) - (s2 % M) + M) % M;
}
void solve() {
    int x1, x2, y1, y2; pre();
    cin >> x1 >> y1 >> x2 >> y2; int ans = 0;
    for (int i = x1; i <= x2; i++) {
        int s1 = lucas(i + y2 + 1, i + 1) % M;
        int s2 = lucas(i + y1, i + 1) % M;
        ans = (ans % M + ((s1 % M) - (s2 % M) + M) % M) % M;
    }
    cout << ans << el;
}
signed main() {
    ios_base::sync_with_stdio(0);
    std::cout.tie(0), cin.tie(0);/* freopen("tree.in", "r", stdin);*/
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
}
