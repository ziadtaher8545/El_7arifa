// ويتمني لو تاتي مرة
#include "bits/stdc++.h"

#define el '\n'
#define ll long long
#define int  ll

#pragma GCC optimize ("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#pragma GCC optimize ("unroll-loops")
using namespace std;


void solve() {
    // ll l = 1, r = *max_element(v.begin(), v.end()), ans = 0, m1, m2, an1, an2;
    // while (l <= r)
    // {
    //     m1 = l + (r - l) / 3;
    //     m2 = r - (r - l) / 3;
    //     an1 = can(m1), an2 = can(m2);
    //     // cout << m1 << ' ' << m2 << ' ' << an1 << ' ' << an2 << el;
    //     if (an1 > an2)
    //         r = m2 - 1;
    //     else
    //         l = m1 + 1;
    //     ans = max({ans, an1, an2});
    // }
    int n,k;
    cin>>n>>k;
    vector<array<int,2>>a(n);
    for (int i=0;i<n;i++)cin>>a[i][0]>>a[i][1];
    long double l=0,r=k;long double ans=1e18;
   for (int i=0;i<100;i++) {
    //   cout<<l<<' '<<r<<el;
          long double  t1=l+(r-l)/3.000;
       long double  t2=r-(r-l)/3.00;
       long double mx1 =0, mn1 = 1e18;
       long double mx2 = 0, mn2 = 1e18;
        for (auto [s,d] :a) {
            mx1=max(mx1,s*t1+d);
            mn1=min(mn1,s*t1+d);
        }
        for (auto [s,d] :a) {
            mx2=max(mx2,s*t2+d);
            mn2=min(mn2,s*t2+d);
        }
          long double  ans1=mx1-mn1,ans2=mx2-mn2;
       ans=min(ans1,ans2);
       if (ans1<ans2) {
           r=t2;
       }
       else l=t1;

    }
cout << fixed << setprecision(6) << ans << '\n';
}

/*




*/
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;

    // freopen("same.in", "r", stdin);
    //freopen("output.txt", "w", stdout);
   // cin >> T;
    // cin.ignore();
    //init();
    //for (int i=1;i<N;i++)for (int j=i;j<N;j+=i)ad[j].push_back(i);

    for (int i = 1; i <= T; i++)
        solve();
}
