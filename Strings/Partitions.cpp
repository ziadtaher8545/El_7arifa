const int N = 2E5 + 5, mod = 1E9 + 7;
int add(int a, int b) {
    return (0LL + a + b + mod) % mod;
}
int mul(int a, int b) {
    return (1ll * a * b) % mod;
}

// ans[i] = number of partitions of i
// O(n sqrt(n))
vector<int> build(int n) {
    vector<int> ans(n + 1);
    vector<pair<int, int>> gp;
    gp.emplace_back(0, 0);
    for (int i = 1; gp.back().second <= n; i++) {
        gp.emplace_back(i % 2 ? 1 : -1, i * (3 * i - 1) / 2);
        gp.emplace_back(i % 2 ? 1 : -1, i * (3 * i + 1) / 2);
    }
    ans[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (auto it : gp) {
            if (i >= it.second)
                ans[i] = add(ans[i], mul(ans[i - it.second], it.first));
            else break;
        }
    }
    return ans;
}
