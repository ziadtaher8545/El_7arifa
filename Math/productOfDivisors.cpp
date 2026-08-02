
int productOfDivisors(vector<pair<int,int>>v)
{

    //o(N)

    map<int, int> prime;
for (auto x:v)
    prime[x.first]+=x.second;

    int product = 1, d = 1;


    for (auto itr : prime) {

        int val
            = power(itr.first,
                    (itr.second) * (itr.second + 1) / 2,
                    MOD);

        // Update the product
        product = (power(product, itr.second + 1, MOD)
                   * power(val, d, MOD))
                  % MOD;

        // Update the count of divisors
        d = (d * (itr.second + 1)) % (MOD - 1);
    }

    return product;
}
