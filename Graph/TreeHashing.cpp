// @prefix Tree hashing 
// @description 

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll N = 5e5 + 5;
const ll mod[] = {(ll)1E9 + 7, (ll)1E9 + 9};
const ll B[] = {131, 137};
array<ll, 2> pw[N];

void init()
{
    pw[0][0] = pw[0][1] = 1;
    for (int i = 1; i < N; i++)
    {
        for (int j = 0; j <= 1; j++)
            pw[i][j] = pw[i - 1][j] * B[j] % mod[j];
    }
}

ll power(ll b, ll p, ll MOD)
{
    ll ret = 1;
    while (p)
    {
        if (p & 1)
            ret = (ret * b) % MOD;
        b *= b, b %= MOD, p >>= 1;
    }
    return ret;
}

ll inv(ll b, ll MOD)
{
    return power(b, MOD - 2, MOD);
}
class Tree
{
public:
    vector<int> dep;
    const int LOG = 20;
    vector<vector<int>> up;
    vector<vector<int>> adj;
    vector<array<int, 2>> h, hrv;
    string a;
    Tree(int n) : adj(n), dep(n), h(n), hrv(n), up(n, vector<int>(LOG)) {}

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // DFS to preprocess ancestors
    void dfs(int u, int p = 0)
    {
        up[u][0] = p;
        int x = a[u - 1];

        for (int i = 0; i <= 1; i++)
        {
            h[u][i] = (h[p][i] * B[i] % mod[i] + x) % mod[i];              // string from p to u
            hrv[u][i] = (hrv[p][i] + pw[dep[u]][i] * x % mod[i]) % mod[i]; // string from u to p
        }

        for (int k = 1; k < LOG; k++)
            up[u][k] = up[up[u][k - 1]][k - 1];

        for (auto &v : adj[u])
        {
            if (v == p)
                continue;
            dep[v] = dep[u] + 1;
            dfs(v, u);
        }
    }

    // kth ancestor
    int kthAnc(int u, int k)
    {
        if (dep[u] < k)
            return -1;

        for (int i = LOG - 1; i >= 0; --i)
            if ((k >> i) & 1)
                u = up[u][i];

        return u;
    }

    // LCA
    int LCA(int u, int v)
    {
        if (dep[u] < dep[v])
            swap(u, v);

        int k = dep[u] - dep[v];
        u = kthAnc(u, k);
        if (u == v)
            return u;

        for (int i = LOG - 1; i >= 0; --i)
            if (up[u][i] != up[v][i])
                u = up[u][i], v = up[v][i];

        return up[u][0];
    }

    array<ll, 2> get(int u, int v)
    {
        int lca = LCA(u, v);

        ll L[]{hrv[u][0], hrv[u][1]};
        ll R[]{h[v][0], h[v][1]};
        int l1 = dep[v] - dep[lca], l2 = dep[lca] + 1;
        int x = a[lca - 1];

        for (int i = 0; i <= 1; i++)
        {
            R[i] = (R[i] - h[lca][i] * pw[l1][i] % mod[i] + mod[i]) % mod[i];
            R[i] = (R[i] + x * pw[l1][i] % mod[i]) % mod[i];

            L[i] = (L[i] - hrv[lca][i] + mod[i]) % mod[i] * inv(pw[l2][i], mod[i]) % mod[i];
        }

        array<ll, 2> res{0, 0};
        for (int i = 0; i <= 1; i++)
        {
            res[i] = (L[i] * pw[l1 + 1][i] % mod[i] + R[i]) % mod[i];
        }

        return res;
    }
};

void solve(...)
{
    int n, m;
    cin >> n >> m;

    Tree tree(n + 1);
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v, tree.addEdge(u, v);

    string s;
    cin >> s;
    tree.a = s;
    tree.dfs(1);

    auto Hashing = [&](string x)
    {
        array<ll, 2> h = {0, 0};
        for (int i = 0; i < x.size(); i++)
        {
            int v = x[i];
            for (int j = 0; j <= 1; j++)
                h[j] = (h[j] * B[j] % mod[j] + v) % mod[j];
        }

        return h;
    };

    set<array<ll, 2>> st;
    for (int i = 0; i < m; i++)
    {
        string x;
        cin >> x;
        st.insert(Hashing(x));
    }

    int q;
    cin >> q;
    while (q--)
    {
        int u, v;
        cin >> u >> v;

        if (st.count(tree.get(u, v)))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}

signed main()
{
    cin.tie(0)->sync_with_stdio(0);

    init();
    int _t = 1;
    cin >> _t;
    for (int i = 1; i <= _t; i++)
    {
        // cout << "Case #" << i << ": ";
        solve(i), cout << '\n';
    }
}
