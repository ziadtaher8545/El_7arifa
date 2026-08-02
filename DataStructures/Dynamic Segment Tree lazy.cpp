#include "bits/stdc++.h"
#define el '\n'
#define ll long long
//#define int long long
using namespace std;
//  لو مش الديك موجود الفرحه هتبيض ازاي ؟
// داخل سباق انا واحمد علي اللي يشيل


template<typename T>
struct Node {
    T val;
    Node* left;
    Node* right;
    T lazy;
    bool toSet;
    Node(T v = 0) : val(v), left(nullptr), right(nullptr), lazy(0), toSet(false) {}
};

template<typename T>
struct SegmentTree {
    int L, R;
    Node<T>* root;

    SegmentTree(int l, int r) : L(l), R(r) {
        root = new Node<T>();
    }

    void push(Node<T>* node, int l, int r) {
        if (node->toSet) {
            node->val = (r - l + 1) * node->lazy;
            if (l != r) {
                if (!node->left) node->left = new Node<T>();
                if (!node->right) node->right = new Node<T>();
                node->left->lazy = node->lazy;
                node->right->lazy = node->lazy;
                node->left->toSet = node->right->toSet = true;
            }
            node->toSet = false;
        }
    }

    void update(Node<T>* node, int l, int r, int ql, int qr, T value) {
        push(node, l, r);
        if (qr < l || ql > r) return;
        if (ql <= l && r <= qr) {
            node->lazy = value;
            node->toSet = true;
            push(node, l, r);
            return;
        }
        int m = (l + r) / 2;
        if (!node->left) node->left = new Node<T>();
        if (!node->right) node->right = new Node<T>();
        update(node->left, l, m, ql, qr, value);
        update(node->right, m + 1, r, ql, qr, value);
        node->val = (node->left ? node->left->val : 0) + (node->right ? node->right->val : 0);
    }

    T query(Node<T>* node, int l, int r, int ql, int qr) {
        if (!node || qr < l || ql > r) return 0;
        push(node, l, r);
        if (ql <= l && r <= qr) return node->val;
        int m = (l + r) / 2;
        return query(node->left, l, m, ql, qr) + query(node->right, m + 1, r, ql, qr);
    }

    void update(int l, int r, T value) { update(root, L, R, l, r, value); }
    T query(int l, int r) { return query(root, L, R, l, r); }
};
void solve() {
    int n,q;
    cin >> n >> q;
    SegmentTree<int> st(1, n);

    while (q--) {
        int l,r;
        cin >> l >> r;
        st.update(l, r,1);
        cout<<n-st.query(1, n)<<el;
    }


}

/*






 **/
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    //freopen("help.in", "r", stdin);
    //freopen("output.txt", "w", stdout);
  //  cin >> T;
    for (int i = 1; i <= T; i++)
        solve();
}
