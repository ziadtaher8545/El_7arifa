// time =sqrt4(n)
typedef __int128_t int128;

ll power(ll base, ll exp, ll mod) {
    ll res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (ll)((int128)res * base % mod);
        base = (ll)((int128)base * base % mod);
        exp /= 2;
    }
    return res;
}

bool miller_rabin(ll n, int a) {
    if (a % n == 0) return true;
    ll d = n - 1;
    while (d % 2 == 0) d /= 2;
    ll x = power(a, d, n);
    if (x == 1 || x == n - 1) return true;
    while (d != n - 1) {
        x = (ll)((int128)x * x % n);
        d *= 2;
        if (x == n - 1) return true;
        if (x == 1) return false;
    }
    return false;
}

bool is_prime(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    static const vector<int> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (int a : bases) {
        if (n == a) return true;
        if (!miller_rabin(n, a)) return false;
    }
    return true;
}

ll pollard_rho(ll n) {
    if (n % 2 == 0) return 2;
    if (is_prime(n)) return n;
    ll x = rand() % (n - 2) + 2;
    ll y = x;
    ll c = rand() % (n - 1) + 1;
    ll d = 1;
    while (d == 1) {
        x = (ll)(((int128)x * x + c) % n);
        y = (ll)(((int128)y * y + c) % n);
        y = (ll)(((int128)y * y + c) % n);
        d = std::gcd(abs(x - y), n);
        if (d == n) return pollard_rho(n);
    }
    return d;
}

void factorize(ll n, vector<ll>& factors) {
    if (n == 1) return;
    if (is_prime(n)) {
        factors.push_back(n);
        return;
    }
    ll d = pollard_rho(n);
    factorize(d, factors);
    factorize(n / d, factors);
}

void solve() {
    vector<int>v;
    factorize(a*b,v);
}  
