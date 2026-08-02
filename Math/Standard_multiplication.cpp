#include "bits/stdc++.h"
#define ll long long
#define int ll
#define el '\n'
using namespace std;
const int N = 3e5 + 77;
/* time is n*n   len n is the size of string   */
string Standard_multiplication_of_tow_string(string a, string b) {
    int n = a.size(), m = b.size();

    vector<int>res(n + m, 0);
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            int x = (a[i] - '0') * (b[j] - '0');
            int sum = x + res[i + j + 1];
            res[i + j + 1] = sum % 10;
            res[i + j] += (sum / 10);
        }
    }
    string ans = "";
    for (auto x : res)
        if (!(ans.size() == 0 && x == 0))
            ans += to_string(x);
    return ans == "" ? "0" : ans;
}
/* time is n*(log2(n))   len n is the size of string   */
#include <bits/stdc++.h>
using namespace std;
using cd = complex<double>;
const double PI = acos(-1);

// FFT forward/inverse
void fft(vector<cd>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j];
                cd v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert)
        for (cd& x : a) x /= n;
}

// multiply big numbers
string multiply(string s1, string s2) {
    vector<int> a, b;
    for (int i = s1.size() - 1; i >= 0; i--) a.push_back(s1[i] - '0');
    for (int i = s2.size() - 1; i >= 0; i--) b.push_back(s2[i] - '0');

    int n = 1;
    while (n < (int)a.size() + (int)b.size()) n <<= 1;
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    fa.resize(n); fb.resize(n);

    fft(fa, false); fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);

    vector<int> res(n);
    for (int i = 0; i < n; i++) res[i] = int(round(fa[i].real()));

    for (int i = 0; i + 1 < n; i++) {
        res[i + 1] += res[i] / 10;
        res[i] %= 10;
    }

    while (res.size() > 1 && res.back() == 0) res.pop_back();
    string ans;
    for (int i = res.size() - 1; i >= 0; i--) ans.push_back(res[i] + '0');
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    cin >> a >> b;
    cout << multiply(a, b) << "\n";
}
