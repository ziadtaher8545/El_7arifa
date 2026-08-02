class Sparse_table
{
private:
    vector<vector<int>> spt;
    int merge(int a, int b)
    {
        return min(a, b);
    }

public:
    Sparse_table(vector<int> &v)
    {
        int n = v.size(), Log = __lg(n);
        spt.resize(n, vector<int>(Log + 1));
        for (int i = 0; i < n; i++)
            spt[i][0] = v[i];
        for (int msk = 1; msk <= Log; msk++)
        {
            for (int i = 0; i + (1 << msk) - 1 < n; i++)
            {
                spt[i][msk] = merge(spt[i][msk - 1], spt[i + (1 << (msk - 1))][msk - 1]);
            }
        }
    }
    int get(int l, int r)
    {
        int sz = r - l + 1;
        int msk = __lg(sz);
        return merge(spt[l][msk], spt[r - (1 << msk) + 1][msk]);
    }
    int get_log(int l, int r)
    {
        int ret = 1e18;
        int sz = r - l + 1;
        int msk = __lg(r - l) + 1;
        for (int i = msk; i >= 0; i--)
        {
            if ((1 << i) & sz)
            {
                ret = merge(ret, spt[l][i]);
                l += (1 << i);
            }
        }
        return ret;
    }
};
