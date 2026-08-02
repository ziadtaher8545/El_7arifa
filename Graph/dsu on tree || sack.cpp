const int N = 1e5+10;
vector<int> ad[N];
int sz[N], big[N], dep[N];
string c[N];
map<string,int> freq[N];
int  ans[N];
vector<array<int, 2> > q[N];
int sum[N], mx[N];

void pre(int u,int p,int dp) {
    sz[u] = 1;
    dep[u] = dp;
    for (auto x: ad[u])
        if (p != x) {
            pre(x, u, dp + 1);
            sz[u] += sz[x];
            if (big[u] == 0 || sz[x] > sz[big[u]]) big[u] = x;
        }
}

void update(int u,int d) {
    if (d == 1 && freq[dep[u]][c[u]] == 0)mx[dep[u]]++;
    if (d == -1 && freq[dep[u]][c[u]] == 1)mx[dep[u]]--;
    freq[dep[u]][c[u]] += d;
}

void collect(int u,int p,int d) {
    update(u, d);
    for (auto x: ad[u])
        if (x != p) {
            collect(x, u, d);
        }
}

void dfs(int u,int p, bool keep) {

    for (auto x: ad[u])
        if (x != p && x != big[u]) {
            dfs(x, u, 0);
        }
    if (big[u])
        dfs(big[u], u, 1);
    update(u, 1);
    for (auto x: ad[u])
        if (x != p && x != big[u]) {
            collect(x, u, 1);
        }
    // queries
    // dep[node]+k;
    for (auto [k,i]: q[u]) {
       ans[i]=mx[dep[u]+k];
    }
    if (!keep)
        collect(u, p, -1);
}
