function<int(int)> clc = [&](int nm) -> int
{
    int ret = nm;
    for (int msk = 1; msk < (1 << k); msk++)
    {
        int lc = 1;
        for (int i = 0; i < k; i++)
        {
            if (msk & (1 << i))
                lc = __lcm(lc, v[i]);

            if (lc > nm)
                break;
        }
        if (__builtin_popcount(msk) & 1)
            ret -= nm / lc;
        else
            ret += nm / lc;
    }
    return ret;
};
