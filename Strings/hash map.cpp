#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define el '\n'
#define ll long long

//#define int long long
#pragma GCC optimize ("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#pragma GCC optimize ("unroll-loops")
#define mi gp_hash_table<int, int, custom_hash>

using namespace __gnu_pbds;
using namespace std;
// إن لم تستطع اللعب فاكمل ستفعلها يوما ما

struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

void solve() {int n;
    cin>>n;
   // vector<int>a(n);for (int i=0;i<n&&cin>>a[i];i++);
     mi cost,m; int mn=1e18;
    for (int i=0;i<n;i++) {

        int x;cin>>x;
        int c=0;mi v;
        while (!v[x]) {
            m[x]++;cost[x]+=c;v[x]++;
            if (m[x]==n)
                mn=min(mn,cost[x]);
            c++;
            if (x%2==0)
                x/=2;
            else x++;
        }
       // cout<<c<<el;
    }

    // for (auto [x,cnt]:m)if (cnt==n) {
    //     mn=min(mn,cost[x]);
    // }
    cout<<mn<<el;
}


/*

999999999
*/
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // freopen("milk.in", "r", stdin);
    //freopen("output.txt", "w", stdout);
    cin >> T;

    for (int i = 1; i <= T; i++)
        solve();
}
