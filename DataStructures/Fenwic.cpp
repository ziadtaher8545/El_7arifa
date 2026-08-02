class Bit
{
    int n;
    vector<int> v;

public:
    Bit(int n)
    {
        this->n = n + 5;
        v.resize(n + 5);
    }
    void add(int i, int val)
    {
        while (i < n)
        {
            v[i] += val;
            i += i & -i;
        }
    }
    long long query(int i)
    {
        long long ret = 0;
        while (i > 0)
        {
            ret += v[i];
            i -= i & -i;
        }
        return ret;
    }
    long long query(int l, int r)
    {
        return query(r) - query(l - 1);
    }
};
