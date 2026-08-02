///  1+k+k2+k3+⋯+kn    =  ans=(k^(n+1) -1 )/(k-1)
long long SumOfDivisors(long long num) {
    long long total = 1;

    for (int i = 2; (long long)i * i <= num; i++) {
        if (num % i == 0) {
            int e = 0;
            do {
                e++;
                num /= i;
            } while (num % i == 0);

            long long sum = 0, pow = 1;
            do {
                sum += pow;
                pow *= i;
            } while (e-- > 0);
            total *= sum;
        }
    }
    if (num > 1) {
        total *= (1 + num);
    }
    return total;
}


long long SumOfDivisors(vector<pair<int,int> > a) {
    int ans = 1;
    // ans=(k^(n+1) -1 )/(k-1)
    for (auto [k,n]: a) {
        int s;
        if (n == 1) {
            s = k + 1;
        } else {
            s = (power(k, n + 1, M) - 1 + M) * power(k - 1, M - 2, M);
        }
        ans = mul(ans, s);
    }

    return ans;
}
