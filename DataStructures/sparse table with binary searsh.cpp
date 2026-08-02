#include "bits/stdc++.h"
#define el '\n'
#define ll long long
#define int long long
using namespace std;
//  لو مش الديك موجود الفرحه هتبيض ازاي ؟
class Sparse_table
{
    vector<vector<int>> sp;
    int sz, n;
    void build()
    {
        for (int i = 1; i <= sz; i++)
        {
            for (int j = 0; j + (1 << (i)) - 1 < n; j++)
            {
                sp[i][j] = gcd(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

public:
    Sparse_table(vector<int> &v)
    {
        n = v.size();
        sz = __lg(n);
        sp = vector<vector<int>>(sz + 1, vector<int>(n));
        for (int i = 0; i < n; i++)
            sp[0][i] = v[i];
        build();
    }
    int query(int l, int r)
    {
        int n = __lg(r - l + 1);
        return gcd(sp[n][l], sp[n][r - (1 << n) + 1]);
    }
    int query_log(int l, int r)
    {
        int n = r - l + 1;
        int ans;
        for (int mask = sz; ~mask; --mask)
        {
            if ((1 << mask) & n)
            {
            }
        }
        return ans;
    }
};
const int M=1e9+7;
void solve() {
    int n;cin>>n;
    vector<int> a(n);
    for (int i=0;i<n;i++)
        cin>>a[i];
    Sparse_table sp(a);
    int ans=0;
    for (int i = 0; i < n; i++)
    {
        ll k = i;
        ll cur, l, r, mid;
        while (k < n)
        {
            cur = sp.query(i, k);
            l = k, r = n - 1;
            while (l <= r)
            {
                mid = (l + r) / 2;
                if (sp.query(i, mid) == cur)
                {
                    l = mid + 1;
                }
                else
                    r = mid - 1;
            }
           ans=(ans%M+(cur*(r-k+1))%M)%M;
            k = r + 1;
        }
    }
    cout<<ans<<endl;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    //freopen("help.in", "r", stdin);
    //freopen("output.txt", "w", stdout);
    //cin >> T;
    for (int i = 1; i <= T; i++)
        solve();
}
