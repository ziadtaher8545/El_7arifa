ll power(ll n, ll p, ll mod) {
    if (p == 0)
        return 1;

    ll a = power(n, p / 2, mod);
    a = (a * a) % mod;

    if (p % 2 == 1)
        return (a * (n % mod)) % mod;
    else
        return a;
}

vector<int> fact(N + 4), factinv(N + 4);

void pre() {
    fact[0] = 1;
    for (int i = 1; i < N; ++i) {
        fact[i] = ((i % M) * (fact[i - 1] % M)) % M;
    }
    factinv[N - 1] = power(fact[N - 1], M - 2, M);;
    for (int i = N - 2; i >= 0; i--)
        factinv[i] = (factinv[i + 1] % M * (i + 1) % M) % M;
}

int ncr(int n, int r) {
    return (((fact[n] % M * factinv[n - r] % M) % M) * factinv[r] % M) % M;
}

int s_b(int st, int b) {
    return ncr(st + b, st);
}

long long get_derangement(int m) {
    if (m == 0) return 1;
    if (m == 1) return 0;

    long long prev2 = 1; // D(0)
    long long prev1 = 0; // D(1)
    long long current = 0;

    for (int i = 2; i <= m; ++i) {
        current = (i - 1) * (prev1 + prev2);
        prev2 = prev1;
        prev1 = current;
    }
    return current;
}

int mul(int x,int y) {
    return (x % M * y % M) % M;
}

int add(int x,int y) {
    return (x % M + y % M) % M;
}
int sol(int sz,int k)
{
    ///  for(int i=0;i<sz;i++)ans+=pow(k,i) == (k^sz)-1/(k-1);
    int ans=power(k,sz,M)-1+M;
    ans%=M;
    ans=mul(ans,power(k-1,M-2,M));
    return ans;
}
