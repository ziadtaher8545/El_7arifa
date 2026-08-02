/*
 الَّذِينَ كَذَّبُوا شُعَيْبًا كَأَن لَّمْ يَغْنَوْا فِيهَا ۚ الَّذِينَ كَذَّبُوا شُعَيْبًا كَانُوا هُمُ الْخَاسِرِينَ (92
 فَتَوَلَّىٰ عَنْهُمْ وَقَالَ يَا قَوْمِ لَقَدْ أَبْلَغْتُكُمْ رِسَالَاتِ رَبِّي وَنَصَحْتُ لَكُمْ ۖ فَكَيْفَ آسَىٰ عَلَىٰ قَوْمٍ كَافِرِينَ (93
 وَمَا أَرْسَلْنَا فِي قَرْيَةٍ مِّن نَّبِيٍّ إِلَّا أَخَذْنَا أَهْلَهَا بِالْبَأْسَاءِ وَالضَّرَّاءِ لَعَلَّهُمْ يَضَّرَّعُونَ (94
 (ثُمَّ بَدَّلْنَا مَكَانَ السَّيِّئَةِ الْحَسَنَةَ حَتَّىٰ عَفَوا وَّقَالُوا قَدْ مَسَّ آبَاءَنَا الضَّرَّاءُ وَالسَّرَّاءُ فَأَخَذْنَاهُم بَغْتَةً وَهُمْ لَا يَشْعُرُونَ (95
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <numeric>
#include <fstream>
#include <stack>
#include <queue>
#include <deque>
#include <utility>
#include <map>
#include <set>
#include <cstdint>
#include <unordered_map>
#include <climits>
#include <cstring>
#include <bitset>
#define ll long long 
#define i128 __int128_t
#define pb push_back
#define YES cout << "YES\n";
#define NO cout << "NO\n";
#define el '\n';
#define temos int64_t
#define f0(i,n) for(int i=0;i<n;i++)
#define f1(i,n) for(int i=1;i<=n;i++)
#define ON(n, k) ((n) | (1 << k))
#define off(n, k) ((n) & (~(1 << k)))
#define ison(n, k) ((n >> k) & 1)
#define int long long 
#define all(x) x.begin(),x.end()
#define sz(a)  a.size()
#define pr priority_queue<int, vector<int>, greater<int>>
#define temos_dp  int n;cin>>n;vector<int>a(n);f0(i,n)cin>>a[i];
#define inn  int n;cin>>n;
#define imm  int m;cin>>m;
#define vec(n)  vector<int>a(n);f0(i,n)cin>>a[i];  
#define vec2(m)  vector<int>b(m);f0(i,m)cin>>b[i];  
#include <climits>

using namespace std;
int dx[] = { 1,0 };
int dy[] = { 0,1 };
#define i64 long long  


const int N = 200 + 5, n2 = 200 + 1;
string a, b;
int dp[2][2][22][n2][N]; int m;
int clc(int i, int sum, int sumdi, bool eqA, bool eqB) {
    if (i == a.size()) {
        if (sum % m == 0 && sumdi % m == 0)return 1;
        return 0;
    }
    int& ret = dp[eqA][eqB][i][sumdi][sum];
    if (~ret)return ret;
    int be = (eqA ? a[i] - '0' : 0);
    int ed = (eqB ? b[i] - '0' : 9);
    ret = 0;
    for (int x = be; x <= ed; x++) {
        ret += clc(i + 1, ((sum * 10) % m + x % m) % m, (sumdi + x) % m, (eqA & (be == x)), (eqB & (ed == x)));
    }
    return ret;
}
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int temoz = 1;
    cin >> temoz;
    int x = 1;
    while (temoz--)
    {
        cin >> a >> b >> m;
        cout << "Case " << x++ << ": ";
        if (m > 200) {
            cout << 0 << el;
        }
        else {
            memset(dp, -1, sizeof dp);
            while (a.size() < b.size())a = '0' + a;
            cout << clc(0, 0, 0, 1, 1) << el;;
        }

    }
    return 0;
}
/* if (fopen("input.txt", "r"))
  {
      freopen("input.txt", "r", stdin);
      freopen("output.txt", "w", stdout);
  }*/
