const int N = 2e5 + 5;
int nm_of_dv[N];
vector<int> dv[N];
void pre()
{
    for (int i = 1; i < N; i++)
        for (int j = i; j < N; j += i)
            nm_of_dv[j]++, dv[j].push_back(i);
}
