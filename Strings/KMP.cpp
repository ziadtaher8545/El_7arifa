vector<int> prefix_function(const auto &s)
{
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1, j = 0; i < n; ++i)
    {
        while (j && s[i] != s[j])
            j = pi[j - 1];

        if (s[i] == s[j])
            ++j;
        pi[i] = j;
    }
    return pi;
}

auto compute_automaton(string s)
{
    s += '#';
    int n = s.size();
    auto pi = prefix_function(s);
    vector aut(n, vector<int>(26));

    aut[0][s[0] - 'a'] = 1;
    for (int i = 1; i < n; i++)
    {
        for (int c = 0; c < 26; c++)
        {
            if (c == s[i] - 'a')
                aut[i][c] = i + 1;
            else
                aut[i][c] = aut[pi[i - 1]][c];
        }
    }

    return aut;
}
