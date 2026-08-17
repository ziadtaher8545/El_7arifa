#include <bits/stdc++.h>
using namespace std;
#define el '\n'
// #define int long long
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template <class M>
M rand(M l, M r) {
    return rng() % (r - l + 1) + l;
}

int turn;
stringstream in, out1, out2;
struct in_unit
{
    in_unit operator>>(auto& x) {
        in >> x;
        return *this;
    }
} cinn;
struct out_unit
{
    out_unit operator<<(const auto& x) {
        if (turn == 0) {
            in << x;
        }
        else if (turn == 1) {
            out1 << x;
        }
        else if (turn == 2) {
            out2 << x;
        }
        else {
            cout << x;
        }
        return *this;
    }
} coutt;
#define cin cinn
#define cout coutt

// generate random input
void generate() {

}

// brute force solution
// This is the brute force solution that you want to test against
// It should be correct but slow
void brute() {
}

// main solution
// This is the solution that you want to test

void Main(...) {
}

int T = 100;
signed main() {
    if (fopen("inp.txt", "r")) {
        freopen("inp.txt", "r", stdin);
        freopen("outp.txt", "w", stdout);
    }
    while (T--) {
        in = stringstream(), out1 = stringstream(), out2 = stringstream();
        turn = 0, generate();
        stringstream copy(in.str());
        turn = 1, brute();
        in = stringstream(copy.str());
        turn = 2, Main();
        in = stringstream(copy.str());
        turn = 3;
        if (out1.str() != out2.str()) {
            cout << in.str() << "\n\n";
            cout << "Correct: " << out1.str() << "\n\n";
            cout << "Main: " << out2.str() << "\n\n";
            exit(0);
        }
    }
    cout << "Accepted";
}
