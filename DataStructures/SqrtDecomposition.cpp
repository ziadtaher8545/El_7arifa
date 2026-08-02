
class Sqrt
{
private:
    int SQ;
    vector<long long> ans, v;
    vector<vector<long long>> block;

public:
    Sqrt(const vector<int>& a) {
        SQ = sqrt(a.size()) + 1;
        ans.resize(SQ);
        block.resize(SQ);

        for (int i = 0; i < a.size(); ++i) {
            block[i / SQ].push_back(a[i]);
            v.push_back(a[i]);
        }

        for (int i = 0; i < SQ; ++i) {
            sort(block[i].begin(), block[i].end());
            if (block[i].size())
                ans[i] = block[i][0];
        }
    }

    void update(int i, long long val) {
        auto& blk = block[i / SQ];
        auto it = lower_bound(blk.begin(), blk.end(), v[i]) - blk.begin();
        v[i] = blk[it] = val;

        while (0 < it && blk[it - 1] > blk[it]) {
            swap(blk[it - 1], blk[it]);
            --it;
        }
        while (it + 1 < blk.size() && blk[it] > blk[it + 1]) {
            swap(blk[it], blk[it + 1]);
            ++it;
        }

        ans[i / SQ] = blk[0];
    }

    long long getFreq(int idx, int val) {
        auto& blk = block[idx];
        int U = upper_bound(blk.begin(), blk.end(), val) - blk.begin();
        int L = lower_bound(blk.begin(), blk.end(), val) - blk.begin();
        return U - L;
    }

    long long query(int l, int r, int val) {
        long long ret = 0;
        while (l <= r) {
            if (l % SQ == 0 && l + SQ - 1 <= r) {
                ret += getFreq(l / SQ, val);
                l += SQ;
            }
            else {
                ret += v[l] == val;
                l += 1;
            }
        }
        return ret;
    }
};
