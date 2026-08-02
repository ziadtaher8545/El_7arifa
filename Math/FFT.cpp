using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> &a, bool invert)
{
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++)
    {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1)
    {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len)
        {
            cd w(1);
            for (int j = 0; j < len / 2; j++)
            {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert)
    {
        for (cd &x : a)
            x /= n;
    }
}

vector<ll> multiply(vector<ll> const &a, vector<ll> const &b)
{
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<ll> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}
vector<int> pw(vector<int> p, int k)
{
    vector<ll> ans = {1};
    while (k)
    {
        if (k & 1)
            ans = multiply(ans, p);
        p = multiply(p, p);
        k /= 2;
    }
    return ans;
};
string mul_big_nums(string s, string t)
{

    int n = s.size(), m = t.size();
    vector<int> p1(n), p2(m);
    for (int i = 0; i < n; i++)
        p1[n - i - 1] = s[i] - '0';
    for (int i = 0; i < m; i++)
        p2[m - i - 1] = t[i] - '0';

    vector<int> ans = multiply(p1, p2);
    n = ans.size();

    for (int i = 0; i < n - 1; i++)
        ans[i + 1] += ans[i] / 10, ans[i] %= 10;

    string res = to_string(ans[n - 1]);
    for (int i = n - 2; i >= 0; i--)
        res += char(ans[i] + '0');

    for (int i = 0; i < n; i++)
        if (res[i] - '0')
            return res.substr(i);

    return "0";
}
int string_match(string s, string t)
{
    int n = s.size(), m = size(t);
    vector<int> p1(n), p2(m);
    int sh = m - 1;
    vector<int> ans(n);
    for (int ch = 0; ch < 26; ch++)
    {
        for (int i = 0; i < n; i++)
            p1[i] = (s[i] - 'a') == ch;
        for (int i = 0; i < m; i++)
            p2[sh - i] = (t[i] - 'a') == ch;
        vector<int> mul = multiply(p1, p2);
        for (int i = 0; i < n; i++)
            ans[i] += mul[i];
    }

    for (int i = 0; i <= n - m; i++)
        cout << ans[i + sh] << ' ';
    return 0;
}
