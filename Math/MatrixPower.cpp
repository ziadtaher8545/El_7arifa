const ll mod = 1E9 + 7;
using Row = vector<ll>;
using Matrix = vector<Row>;

int add(int a, int b)
{
    return (0LL + a + b + mod) % mod;
}
int mul(int a, int b)
{
    return (1ll * a * b) % mod;
}

Matrix multiply(const Matrix &A, const Matrix &B)
{
    int n = A.size();
    int m = B[0].size();
    int p = B.size();

    Matrix C(n, Row(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < p; k++)
                C[i][j] = add(C[i][j], mul(A[i][k], B[k][j]));

    return C;
}
Matrix exp(Matrix &A, ll p)
{
    int n = A.size();
    Matrix res(n, Row(n, 0));
    for (int i = 0; i < n; i++)
        res[i][i] = 1;

    while (p)
    {
        if (p & 1)
            res = multiply(res, A);
        A = multiply(A, A);
        p >>= 1;
    }
    return res;
}
