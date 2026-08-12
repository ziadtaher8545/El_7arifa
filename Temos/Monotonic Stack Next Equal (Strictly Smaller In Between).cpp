get_next_equal_smaller_between(vector<int>& a) {
    int n = a.size();
    vector<int> eq(n, -1);
    stack<int> st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.top()] <
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
