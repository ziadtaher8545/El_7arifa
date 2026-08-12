get_prev_equal_greater_between(vector<int>& a) {
    int n = a.size();
    vector<int> eq(n, -1);
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && a[st.top()] >
       a[i]) {
            st.pop();
        }
        if (!st.empty() && a[st.top()] ==
       a[i]) {
            eq[i] = st.top();
        }
        st.push(i);
    }
    return eq;
}
