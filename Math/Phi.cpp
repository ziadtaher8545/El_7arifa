
// phi[x] = number of integers in [1, x] that are coprime with x.
const int N = 1E6 + 5;
vector<int> phi(N);
void totient()
{
    iota(phi.begin(), phi.end(), 0);
    for (int i = 2; i < N; i++)
    {
        if (phi[i] == i)
        {
            for (int j = i; j < N; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}
