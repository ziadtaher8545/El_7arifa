#include "bits/stdc++.h"
#define el '\n'
#define ll int
#define int long long

using namespace std;
map<int,int>mp[25][25];int n,m,k;int a[45][45];
int H=0,tot=0;;int ans=0;
void dfs(int i,int j,int d,int val) {
    if (d==H) {
     //   cout<<val<<el;
      //  cout<<i<<' '<<j<<' '<<val<<el;
        mp[i][j][val]++;
        return ;
    }
    if (i+1<n)
        dfs(i+1,j,d+1,val^a[i][j]);

    if (j+1<m)
        dfs(i,j+1,d+1,val^a[i][j]);
}
void dfs2(int i,int j,int d,int val) {
    if (tot-H==d) {
        int u=val^k^a[i][j];
        ans+=mp[i][j][u];
        return;
    }
    if (i-1>=0)
        dfs2(i-1,j,d+1,val^a[i][j]);

    if (j-1>=0)
        dfs2(i,j-1,d+1,val^a[i][j]);
}
void solve() {
    cin>>n>>m>>k;
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++)
            cin>>a[i][j];
    H=(n+m-2)/2;tot=n+m-2;
    dfs(0,0,0,0);
    dfs2(n-1,m-1,0,0);
    cout<<ans<<el;

}


/*


 */
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;

    // freopen("milk.in", "r", stdin);
    //freopen("output.txt", "w", stdout);
    //   cin >> T;

    for (int i = 1; i <= T; i++)
        solve();
}
