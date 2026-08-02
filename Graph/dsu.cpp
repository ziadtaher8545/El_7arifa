struct DSU {
private:
public:
    vector<int> par, size;
    DSU(int n) {
        par.resize(n + 5);
        size.resize(n + 5, 1);
        std::iota(par.begin(), par.end(), 0);
    }

    int getRoot(int u) {
        if (u == par[u])return u;
        return par[u] = getRoot(par[u]);
    }

    bool sameSet(int u, int v) {
        return getRoot(u) == getRoot(v);
    }

    void merge(int u, int v) {
        u = getRoot(u);
        v = getRoot(v);
        if (u == v)
            return;
        if (size[u] > size[v]) swap(u, v);
        par[u] = v;
        size[v] += size[u];
    }
};
