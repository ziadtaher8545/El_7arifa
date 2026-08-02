class Bit2D
{
    int n, m;
    vector<vector<int>> v;

public:
    Bit2D(int n, int m)
    {
        this->n = n + 5;
        this->m = m + 5;
        v = vector<vector<int>>(n + 5, vector<int>(m + 5));
    }
    void add(int r, int c, int val)
    {
        for (int i = r; i < n; i += i & -i)

            for (int j = c; j < n; j += j & -j)
                v[i][j] += val;
    }
    long long query(int r, int c)
    {
        long long ret = 0;
        for (int i = r; i > 0; i -= i & -i)
            for (int j = c; j > 0; j -= j & -j)
                ret += v[i][j];
        return ret;
    }
    long long query(int r, int c, int r2, int c2)
    {
        return query(r2, c2) - query(r2, c - 1) - query(r - 1, c2) + query(r - 1, c - 1);
    }
};
