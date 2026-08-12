// وَأَن لَّيْسَ لِلْإِنسَانِ إِلَّا مَا سَعَىٰ (39) وَأَنَّ سَعْيَهُ سَوْفَ يُرَىٰ (40) ثُمَّ يُجْزَاهُ الْجَزَاءَ الْأَوْفَىٰ (41) وَأَنَّ إِلَىٰ رَبِّكَ الْمُنتَهَىٰ
#include "bits/stdc++.h"
#define el '\n'
#define ll long long
#define int ll
#pragma GCC optimize ("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#pragma GCC optimize ("unroll-loops")
using namespace std;
// وكل يوم يسال نفسه نفس السؤال هيا ليه صعبه كده؟
// وما يلاقي اجابه غير اني ربنا مش بيضيع تعب حد

/*


the number of elements y such that x|y=x
the number of elements y such that x&y=x
the number of elements y such thatx&y=0

*/

const int N = 1e5 + 6,B=20,val=1<<20;
int freq[val];int dp_or[val],dp_and[val];
bool on(int mask,int i) {
    return ((mask>>i)&1);
}
void solve() {
 int n;cin>>n;vector<int>a(n);
    for (int i=0;i<n;i++) {
        cin>>a[i];freq[a[i]]++;
    }
    for (int i=0;i<(1<<B);i++)
        dp_or[i]=dp_and[i]=freq[i];
    for (int i=0;i<B;i++)
        for (int mask=0;mask<(1<<B);mask++) {
            if (on(mask,i)) {
                dp_or[mask]+=dp_or[mask^(1<<i)];
            }
        }
    //and
    for (int i=0;i<B;i++)
        for (int mask=0;mask<(1<<B);mask++) {
            if (!on(mask,i)) {
                dp_and[mask]+=dp_and[mask^(1<<i)];
            }
        }
    for (int i=0;i<n;i++)
        cout<<dp_or[a[i]]<<' '<<dp_and[a[i]]<<' '<<n-dp_or[(a[i]^(val-1))]<<el;

}


/*

3 10
3 5 2

*/
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // freopen("D.in", "r", stdin);
    //freopen("output.txt", "w", stdout);
     // cin >> T;

    for (int i = 1; i <= T; i++)
        solve();
}
