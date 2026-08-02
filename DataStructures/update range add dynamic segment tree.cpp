#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DynSeg {
    struct Node {
        Node *L=nullptr, *R=nullptr;
        ll sum=0;
        ll lazy=0;
        ~Node(){ if(L) delete L; if(R) delete R; }
    };
    Node* root;
    int MINX, MAXX;
    DynSeg(int lo, int hi){ MINX=lo; MAXX=hi; root = new Node(); }

    void apply(Node* node, int l, int r, ll val){
        node->sum += val * (r - l + 1);
        node->lazy += val;
    }
    void push(Node* node, int l, int r){
        if(node->lazy==0) return;
        int m = l + (r-l)/2;
        if(!node->L) node->L = new Node();
        if(!node->R) node->R = new Node();
        apply(node->L, l, m, node->lazy);
        apply(node->R, m+1, r, node->lazy);
        node->lazy = 0;
    }
    void _add(Node* node, int l, int r, int ql, int qr, ll val){
        if(ql>r || qr<l) return;
        if(ql<=l && r<=qr){
            apply(node, l, r, val);
            return;
        }
        push(node, l, r);
        int m = l + (r-l)/2;
        if(ql<=m){
            if(!node->L) node->L = new Node();
            _add(node->L, l, m, ql, qr, val);
        }
        if(qr>m){
            if(!node->R) node->R = new Node();
            _add(node->R, m+1, r, ql, qr, val);
        }
        node->sum = (node->L?node->L->sum:0) + (node->R?node->R->sum:0);
    }
    ll _sum(Node* node, int l, int r, int ql, int qr){
        if(!node || ql>r || qr<l) return 0;
        if(ql<=l && r<=qr) return node->sum;
        push(node, l, r);
        int m = l + (r-l)/2;
        return _sum(node->L, l, m, ql, qr) + _sum(node->R, m+1, r, ql, qr);
    }

    void range_add(int l,int r,ll v){ if(l>r) return; _add(root, MINX, MAXX, l, r, v); }
    ll range_sum(int l,int r){ if(l>r) return 0; return _sum(root, MINX, MAXX, l, r); }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // نطاق من 1 إلى 1e9
    DynSeg seg(1, 1000000000);

    // زود +5 على الرينج [10, 20]
    seg.range_add(10, 20, 5);

    // زود +3 على الرينج [15, 30]
    seg.range_add(15, 30, 3);

    // استعلامات
    cout << seg.range_sum(1, 9) << "\n";      // = 0
    cout << seg.range_sum(10, 20) << "\n";    // = 5*(11) + 3*(6) = 55 + 18 = 73
    cout << seg.range_sum(25, 40) << "\n";    // = 3*(6) = 18
}
