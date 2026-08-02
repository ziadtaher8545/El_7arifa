struct Maximumflow_Ford_Fulkerson_and_Edmonds_Karp {
    // time is node * (edge^2)
    int n;
    vector<vector<int> > ad, capacity;
    const int INF = 1e18;

    Maximumflow_Ford_Fulkerson_and_Edmonds_Karp(int node) {
        n = node;
        ad.resize(n + 1);
        capacity.assign(n + 1, vector<int>(node + 1));
    }

    void addEdge(int x,int y,int c) {
        ad[x].push_back(y);
        ad[y].push_back(x);
        capacity[x][y] += c;
       //  capacity[y][x] += c; if the graph is undirected
    }

    int bfs(int s,int t, vector<int> &par) {
        fill(par.begin(), par.end(), -1);
        par[s] = -2;
        queue<pair<int,int> > q;
        q.push({s, INF});
        while (!q.empty()) {
            auto [cur,flow] = q.front();
            q.pop();
            for (int x: ad[cur])
                if (par[x] == -1 && capacity[cur][x]) {
                    par[x] = cur;
                    int newFlow = min(flow, capacity[cur][x]);
                    if (x == t) return newFlow;
                    q.push({x, newFlow});
                }
        }
        return 0;
    }


    int maxFlow(int s,int t) {
        vector<int> par(n + 5);;
        int new_flow = 0;
        int flow = 0;
        while (new_flow = bfs(s, t, par)) {
            flow += new_flow;
            int cur = t;
            while (cur != s) {
                capacity[par[cur]][cur] -= new_flow;
                capacity[cur][par[cur]] += new_flow;
                cur = par[cur];
            }
        }
        return flow;
    }

    vector<array<int, 2> > path_Of_Flow(int s,int t, vector<array<int, 2> > edges) {
        queue<int> q;
        q.push(s);
        vector<int> vis(n + 1, false);
        vis[s] = true;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int x: ad[cur]) {
                if (!vis[x] && capacity[cur][x] > 0)
                    q.push(x), vis[x] = true;
            }
        }
        vector<array<int, 2> > ret;
        for (auto [x,y]: edges)
            if (vis[x] != vis[y]) {
                ret.push_back({x, y});
            }
        return ret;
    }
};
