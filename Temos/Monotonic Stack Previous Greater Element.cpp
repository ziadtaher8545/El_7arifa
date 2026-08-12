get_previous_greater_element(vector<int>& a) {
    int n = a.size();
    vector<int> nge(n, -1);
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && a[st.top()] <=
       a[i]) {
            st.pop();
        }
        if (!st.empty()) {
            nge[i] = st.top();
        }
        st.push(i);
    }
    return nge;
}
