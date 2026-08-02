string sum_string(string a, string b)
{
    reverse(all(a));
    reverse(all(b)); string s = "";
    int x = 0; int i = 0;
    for (; i < min(a.size(), b.size()); i++)
    {
        x += (a[i] - '0' + b[i] - '0');
        s += to_string(x % 10); x /= 10;/// 18
    }
    while (i < a.size())
    {
        x += (a[i] - '0');
        s += to_string(x % 10); x /= 10;
        i++;
    }
    while (i < b.size())
    {
        x += (b[i] - '0');
        s += to_string(x % 10); x /= 10; i++;
    }
    while (x)
    {
        s += to_string(x % 10); x /= 10;
    }
    reverse(all(s));
    return s;

}
