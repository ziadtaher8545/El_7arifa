map<pair<int, int>, int>mp;
struct HLD {
    int sz[N], big[N], par[N], head[N], id[N], dep[N], val[N];
    ///   لو جاب رن تايم فهو ميموري مش رن تايم 
    void dfs(int v, const vector<vector<pair<int,int>>>& ad) {
        sz[v] = 1;
        for (auto x : ad[v]) {
            if (x.first == par[v]) continue;
            par[x.first] = v;
            dep[x.first] = dep[v] + 1;
            val[x.first] = x.second;
            mp[{v, x.first}] = x.first;
            mp[{ x.first,v}] = x.first;
            dfs(x.first, ad);
            sz[v] += sz[x.first];
            if (big[v] == 0 || sz[x.first] > sz[big[v]])
                big[v] = x.first;
        }
    }

    void flatten(int v, const vector<vector<pair<int,int>>>& ad, int& next) {
        id[v] = next++;
        if (big[v]) {
            head[big[v]] = head[v];
            flatten(big[v], ad, next);
        }
        for (auto x : ad[v]) {
            if (x.first == par[v] || x.first == big[v]) continue;
            head[x.first] = x.first;
            flatten(x.first, ad, next);
        }
    }

    vector<pair<int, int>> path(int u, int v) {
        vector<pair<int, int>> res;
        while (head[u] != head[v]) {
            if (dep[head[u]] < dep[head[v]]) swap(u, v);
            res.emplace_back(id[head[u]], id[u]);
            u = par[head[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        res.emplace_back(id[u]+1, id[v]);
        return res;
    }

    HLD(int n, const vector<vector<pair<int, int>>>& ad) {
        for (int i = 0; i <= n; i++) {
            sz[i] = 0;
            big[i] = 0;
            par[i] = 0;
            head[i] = 0;
            id[i] = 0;
            dep[i] = 0;
            val[i] = 0;
        }
        par[1] = -1; 
        dfs(1, ad);
        int next = 0;
        head[1] = 1;
        flatten(1, ad, next);
    }
};
vector < vector<pair<int, int>>>ad(N);

void solve() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++)
        ad[i].clear();
    vector<pair<int, int>>k;
    for (int i = 0; i < n - 1; i++)
    {
        int x, y, w; cin >> x >> y >> w;
        k.push_back({ x,y });
        ad[x].push_back({ y,w });;
        ad[y].push_back({ x,w });;
    }
    HLD hld(n, ad);
    vector<int>v(n+2);
    for (int i = 2; i <= n; i++)
        v[hld.id[i]] = hld.val[i];
    Segment_Tree<int>sg(v);
    string q;
    while (cin >> q && q != "DONE") {
        if (q == "CHANGE") {
            int i,x;
            cin >> i >> x;
            i--;
            sg.update(hld.id[mp[k[i]]], x);

        }
        else {
            int u, g;
            cin >> u >> g;
            auto d = hld.path(u, g);
            int mx = -1e18;
            for (auto x : d)
                mx = max(mx, sg.query(x.first, x.second));
            cout << mx << el;
        }
    }
}
