#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
 ! Aho–Corasick Automaton

 ? Patterns must be distinct
 ? next     : Normal trie transitions (automaton edges)
 ? link     : Suffix link (longest proper suffix that is also a prefix)
 ? out_link : First suffix link that contains at least one pattern ending
 ? out      : Indices of patterns that end exactly at this node
 ?
 ? Usage:
 ?  - add(pattern)      : insert patterns into the trie
 ?  - work()            : build suffix links & automaton transitions
 ?  - advance(u, c)     : move from state u using character c
 ?  - pre_compute()     : gather all pattern matches per state
*/
const int K = 26;
class AC
{
private:
    int P = 0;

    struct node
    {
        int next[K], link, out_link;
        vector<int> out;
        node() : link(0), out_link(0)
        {
            fill(next, next + K, 0);
        }
    };
    inline int get(char c)
    {
        return c - 'a';
    }

public:
    vector<node> t{node()};
    void add(const string &s)
    {
        int u = 0;
        for (auto &c : s)
        {
            if (!t[u].next[get(c)])
            {
                t[u].next[get(c)] = t.size();
                t.emplace_back();
            }
            u = t[u].next[get(c)];
        }
        t[u].out.push_back(P++);
    }

    void work()
    {
        queue<int> q;
        q.push(0);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int c = 0; c < K; c++)
            {
                int v = t[u].next[c];

                if (v)
                {
                    q.push(v);
                    t[v].link = (u ? t[t[u].link].next[c] : 0);
                    t[v].out_link = (t[t[v].link].out.empty() ? t[t[v].link].out_link : t[v].link);
                }
                else
                    t[u].next[c] = t[t[u].link].next[c];
            }
        }
    }

    int advance(int u, char c)
    {
        return t[u].next[get(c)];
    }

    vector<vector<int>> all;
    void pre_compute()
    {
        all.resize(t.size());
        for (int u = 0; u < t.size(); u++)
        {
            for (int v = u; v; v = t[v].out_link)
                for (auto &x : t[v].out)
                    all[u].push_back(x);
        }
    }
};
void solve(...)
{
    string s;
    cin >> s;

    int q;
    cin >> q;
    vector<string> pat(q);
    for (auto &s : pat)
        cin >> s;

    auto v = pat;
    sort(pat.begin(), pat.end());
    pat.erase(unique(pat.begin(), pat.end()), pat.end());

    AC ac;
    map<string, int> id;
    int idx = 0;
    for (auto &s : pat)
        ac.add(s), id[s] = idx++;

    ac.work();

    int u = 0;
    vector<int> vis(q);
    for (auto c : s)
    {
        u = ac.advance(u, c);
        for (int v = u; v; v = ac.t[v].out_link)
            for (auto &x : ac.t[v].out)
                vis[x]++;
    }

    for (auto &s : v)
    {
        cout << (vis[id[s]] ? "YES" : "NO") << '\n';
    }
}

signed main()
{
    cin.tie(0)->sync_with_stdio(0);

    int _t = 1;
    // cin >> _t;
    for (int i = 1; i <= _t; i++)
    {
        // cout << "Case #" << i << ": ";
        solve(i), cout << '\n';
    }
}
