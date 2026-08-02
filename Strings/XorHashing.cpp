const int N = 2e5 + 5;
int h[N];
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
void init()
{
    for (int i = 0; i < N; i++)
        h[i] = rng();
}
