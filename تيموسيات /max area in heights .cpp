
vector<int> nextSmaller(vector<int>& arr) {
    int n = arr.size();

    vector<int> nextS(n, n);

    stack<int> st;

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && arr[i] < arr[st.top()]) {

            // Setting the index of the next smaller element
            // for the top of the stack
            nextS[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return nextS;
}

// Function to find previous smaller for every element
vector<int> prevSmaller(vector<int>& arr) {
    int n = arr.size();

    vector<int> prevS(n, -1);

    stack<int> st;

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && arr[i] < arr[st.top()]) {

           st.pop();
        }
        if (!st.empty()) {
            prevS[i] = st.top();
        }
        st.push(i);
    }
    return prevS;
}

int getMaxArea(vector<int>& arr) {
    vector<int> prevS = prevSmaller(arr);
    vector<int> nextS = nextSmaller(arr);

    int maxArea = 0;

    for (int i = 0; i < arr.size(); ++i) {
        int width = nextS[i] - prevS[i] - 1;
        int area = arr[i] * width;
        maxArea = max(maxArea, area);
    }

    return maxArea;
}
