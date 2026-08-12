int n;
cin >> n;
vector<int> a(n);
for (int& x : a) cin >> x;

int mx = a[0], cur = a[0];
for (int i = 1; i < n; ++i) {
    cur = max(a[i], cur + a[i]);
    mx = max(mx, cur);
}

cout << mx << endl;
