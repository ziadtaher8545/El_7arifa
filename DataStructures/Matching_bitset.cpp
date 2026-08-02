class matching_bitset
{
    string s;
    static constexpr int N = 1e5 + 1;
    bitset<N> mask[26], pat_mask;

public:
    matching_bitset(const string &_s)
    {
        s = _s;
        for (int i = 0; i < s.size(); ++i)
        {
            int c = s[i] - 'a';
            mask[c].set(i);
        }
    }

    void update(int idx, char ch)
    {
        mask[s[idx] - 'a'][idx] = 0;
        s[idx] = ch;
        mask[s[idx] - 'a'][idx] = 1;
    }

    int pattern_count(const string &pat, int l, int r)
    {
        if (r - l + 1 < pat.size())
        {
            return 0;
        }
        pat_mask.set(); // all ones
        for (int i = 0; i < pat.size(); ++i)
        {
            pat_mask &= (mask[pat[i] - 'a'] >> i);
        }
        // number of set bits from l to r (similar to computing prefix sums)
        return (pat_mask >> l).count() -
               (pat_mask >> (r - (int)pat.size() + 2)).count();
    }

    vector<int> pattern_pos(const string &pat, int l, int r)
    {
        pattern_count(pat, l, r);
        vector<int> pos;
        int m = pat.size();
        int i = pat_mask._Find_first();
        while (i != pat_mask.size())
        {
            pos.emplace_back(i);
            i = pat_mask._Find_next(i);
        }
        return pos;
    }
};
