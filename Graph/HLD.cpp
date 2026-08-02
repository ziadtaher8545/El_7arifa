struct HLD {
    int sz[N], big[N], par[N], head[N], id[N], dep[N];

    void dfs(int v, const vector<vector<int>>& ad) {
        sz[v] = 1;
        for (auto x : ad[v]) {
            if (x == par[v]) continue;
            par[x] = v;
            dep[x] = dep[v] + 1;
            dfs(x, ad);
            sz[v] += sz[x];
            if (big[v] == 0 || sz[x] > sz[big[v]])
                big[v] = x;
        }
    }

    void flatten(int v, const vector<vector<int>>& ad, int& next) {
        id[v] = next++;
        if (big[v]) {
            head[big[v]] = head[v];
            flatten(big[v], ad, next);
        }
        for (int x : ad[v]) {
            if (x == par[v] || x == big[v]) continue;
            head[x] = x;
            flatten(x, ad, next);
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
        res.emplace_back(id[u], id[v]);
        return res;
    }

    HLD(int n, const vector<vector<int>>& ad) {
        for (int i = 0; i <= n; i++) {
            sz[i] = 0;
            big[i] = 0;
            par[i] = 0;
            head[i] = 0;
            id[i] = 0;
            dep[i] = 0;
        }
        dfs(1, ad);
        int next = 0;
        head[1] = 1;
        flatten(1, ad, next);
    }
};
