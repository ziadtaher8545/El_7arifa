const int MAX = 10000001;
int spf[MAX];

void SPF() {
    for (int i = 0; i < MAX; i++)
        spf[i] = i;

    for (int i = 2; i * i < MAX; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j < MAX; j += i) {
                if (spf[j] == j)
                    spf[j] = i;
            }
        }
    }

}
vector<int> getPrimeFactors(int x) {
    vector<int> factors;
    while (x != 1) {
        factors.push_back(spf[x]);
        x /= spf[x];
    }
    return factors;
}
