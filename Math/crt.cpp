#include "bits/stdc++.h"
#define el '\n'
#define ll long long
#define int long long
#pragma GCC optimize ("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#pragma GCC optimize ("unroll-loops")
using namespace std;
int CRT(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = CRT(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

pair<int, int> skib(int a1, int m1, int a2, int m2) {
    int p, q;
    int g = CRT(m1, m2, p, q);
    if ((a2 - a1) % g != 0) return {-1, -1};

    int mod = (m1 / g) * m2;
    // x = a1 + p * (a2 - a1) / g * m1
    int res = (p * ((a2 - a1) / g)) % (m2 / g);
    int x = (a1 + res * m1) % mod;
    if (x < 0) x += mod;
    return {x, mod};
}

/*

crt
x=a1 mod m1
x=a2 mod m2
x=a3 mod m3
...

x=(a1*M1*M1Inv+a2*M2*M2Inv+a3*M3*M3Inv) mod M
M= m1*m2*m3

for all i
    Mi=(M/mi)
    MiInv= mod_inv(M_i, congruence.m)


*/
void solve() {
    /*
3
1 2
2 3
3 4
     */
    int n;
    cin >> n;
    vector<int> a(n), m(n);
    for (int i = 0; i < n; i++)cin >> a[i] >> m[i];
    int x1 = a[0], x2 = m[0];
    for (int i = 0; i < n; i++) {
        auto [o,p] = skib(x1, x2, a[i], m[i]);
        x1 = o, x2 = p;
    }// M=x2;
    cout << x1 << el;
}

/*



 */
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // freopen("milk.in", "r", stdin);
    //freopen("output.txt", "w", stdout);
    // cin >> T;

    for (int i = 1; i <= T; i++)
        solve();
}
