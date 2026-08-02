ll y, x;
cin >> y >> x;
ll n = max(y, x);
ll result;
if (n % 2 == 0) {
    if (y == n) {
        result = n * n - x + 1;
    }
    else {
        result = (n - 1) * (n - 1) + y;
    }
}
else {
    if (x == n) {
        result = n * n - y + 1;
    }
    else {
        result = (n - 1) * (n - 1) + x;
    }
}
cout << result << '\n';
