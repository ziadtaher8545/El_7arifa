#include "bits/stdc++.h"
#define el '\n'
#define ll long long
#define int long long
using namespace std;

// واحده dp بقا يا ام ناصر عايزين نحل
const int N = 2e5 + 5, n22 = 501, mod = 1e9 + 7, M = 1e9 + 7, base = 31;

ll pw1[N], pw2[N];
const ll bs1 = 131, bs2 = 137, mod2 = 1e9 + 9;

void init() {
    pw1[0] = pw2[0] = 1;
    for (int i = 1; i < N; i++) {
        pw1[i] = pw1[i - 1] * bs1 % mod;
        pw2[i] = pw2[i - 1] * bs2 % mod2;
    }
}

struct Hash {
private:
    vector<pair<int, int> > pre;

public:
    Hash(string &s) {
        pre.assign(s.size(), {0, 0});
        int h1 = 0, h2 = 0;
        for (int i = 0; i < s.size(); i++) {
            int x = s[i] ;
            h1 = (h1 * bs1 % mod + x) % mod;
            h2 = (h2 * bs2 % mod2 + x) % mod2;
            pre[i] = {h1, h2};
        }
    }

    pair<int, int> get(int l, int r) {
        pair<int, int> ret = pre[r];
        int sz = r - l + 1;
        if (l) {
            ret.first = (ret.first - pre[--l].first * pw1[sz] % mod + mod) % mod;
            ret.second = (ret.second - pre[l].second * pw2[sz] % mod2 + mod2) % mod2;
        }
        return ret;
    }
};

pair<int,int> sz[10][N];
int pre[11][N];

pair<int,int> clc(int l,int r) {
    pair<int,int> ans = {0, 0};
    auto &[h1,h2] = ans;
    for (int d = 0; d <= 9; d++) {
        int num = pre[d][r] - pre[d][l - 1];
        if (!num)
            continue;
        h1 = (h1 * pw1[num]) % mod;
        h2 = (h2 * pw2[num]) % mod2;

        h1 = (h1 + sz[d][num].first) % mod;
        h2 = (h2 + sz[d][num].second) % mod2;
    }
    return ans;
}

pair<int,int>conc(pair<int,int>s1,pair<int,int>s2,int sz1,int sz2) {
   auto &[h1,h2]=s1;

    h1 = (h1 * pw1[sz2]) % mod;
    h2 = (h2 * pw2[sz2]) % mod2;

    h1 = (h1 + s2.first) % mod;
    h2 = (h2 + s2.second) % mod2;
    return s1;
}
void solve() {
    init();
    for (int d = 0; d <= 9; d++) {
        for (int i = 1; i < N; i++) {
           //  999999
            sz[d][i].first = (sz[d][i - 1].first * bs1 % mod + (d + '0' )) % mod;
            sz[d][i].second = (sz[d][i - 1].second * bs2 % mod2 + (d + '0' )) % mod2;
        }
    }

    //   cout<<sz[di][size]

    int n, q;
    cin >> n >> q;
    string a;
    cin >> a;
    a = '*' + a;
    Hash h(a);
    for (int i = 1; i <= n; i++) {
        pre[a[i]-'0'][i]++;
    }
    for (int d = 0; d <= 9; d++) {
        for (int i = 1; i <= n; i++) {
            pre[d][i] += pre[d][i - 1];
        }
    }
    set<pair<int,int> > s;
    while (q--) {
        int l, r;
        cin >> l >> r;
        pair<int ,int >p=clc(l,r);
        auto x=make_pair(0,0);
        if (l>1)
            x=conc(h.get(1,l-1),p,l-1,r-l+1);
        else x=p;
        if (r!=n)
            x=conc(x,h.get(r+1,n),r-l+1,n-(r+1)+1);
//cout<<x.first<<' '<<x.second<<el;
        s.insert(x);
    }
    cout << s.size() << el;
}

/*
 *
5
1 2 3 4 5
3
2 4
2 5
3 5

 */
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;

    // freopen("fib.in", "r", stdin);
    ///   freopen("gracehopper.in", "w", stdout);
   // cin >> T;

    for (int i = 1; i <= T; i++)
        solve();
}
