const int N = 2E5 + 5;
vector<bool> pr(N + 5, 1);
void sieve()
{
    pr[0] = pr[1] = 0;
    for (int i = 2; i <= N / i; i++)
    {
        if (!pr[i])
            continue;
        for (int j = i * i; j <= N; j += i)
            pr[j] = 0;
    }
}
