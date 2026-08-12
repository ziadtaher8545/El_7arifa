get_next_greater_element(vector<int>& a) {
    int n = a.size();
    vector<int> nge(n, -1);
    stack<int> st;
    for (int i = n - 1; i >= 0; i--) {
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
