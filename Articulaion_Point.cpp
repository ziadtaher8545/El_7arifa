vector<int> deg(N);
struct Articulaion_Point
{
    /*
       articulaion point is a vertex if i remove it the graph will be unconnected
    */
    vector<bool> vis;
    vector<int> low;
    Articulaion_Point(int n)
    {
        vis = vector<bool>(n + 1);
        low = vector<int>(n + 1, 1e9);
        for (int i = 1; i <= n; i++)
        {
            if (!vis[i])
            {
                dfs(i, -1);
            }
        }
    }
    void dfs(int u, int p)
    {
        vis[u] = 1;
        int child = 0;
        for (auto v : ad[u])
        {
            if (v == p)
                continue;
            if (vis[v])
            {
                low[u] = min(low[u], deg[v]);
                continue;
            }
            child++;
            deg[v] = deg[u] + 1;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= deg[u] && p != -1)
            {
                // vertex u is an articulation point --------
            }
        }
        if (p == -1 && child > 1)
        {
            // root of this component is an articulation point --------
        }
    }
};
