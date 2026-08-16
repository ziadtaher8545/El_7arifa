#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll
const int N = 2E6 + 5, mod = 1E9 + 7;
ll mul(ll a, ll b) {
    return (a % mod * b % mod) % mod;
}

ll power(ll b, ll p) {
    ll ret = 1;
    while (p) {
        if (p & 1)
            ret = mul(ret, b);
        b *= b, b %= mod, p >>= 1;
    }
    return ret;
}
int ncr(int n, int r) {
    if (r > n) return 0;
    int num = 1, den = 1;
    for (int i = 0; i < r; i++)
        num = (num % mod * (n - i)) % mod, den = (den * (i + 1)) % mod;
    return num * power(den % mod, mod - 2) % mod;
}
int lucas(int n, int k) {
    if (k <= 0) return 1;
    return ncr(n % mod, k % mod) * lucas(n / mod, k / mod) % mod;
}

void solve(...) {
    ll n, m, k;
    cin >> n >> m >> k;
    if (n < k || m < k - 1 || n && !k)
        return void(cout << 0);
    if (n == k && !k)
        return void(cout << 1);

    cout << mul(lucas(n - 1, k - 1), lucas(m + 1, k));
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
