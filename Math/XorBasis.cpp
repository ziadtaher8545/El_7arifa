
const int Log=64;
struct XorBasis {
    int size;
    array<int, Log> basis,close;
    XorBasis() {
        size = 0;
        for (int i = 0; i < Log; i++)
            basis[i] = 0, close[i] = -1;
    }
    bool have(int x,int i) {
        return ((x >>i)&1LL);
    }
    void  add(int x) {
        for (int i=Log-1; i>=0; i--) {
            if (!have(x,i))continue;
           if (basis[i]==0) {
               basis[i] = x;

            //   close[i] = x;
               size++;
               return;
           }
            x^=basis[i];
        }
    }
    int fun(int x) {
        int ans=0;
        // number of ways make x
        for (int i=Log-1; i>=0; i--) {
            if (!have(x,i)||!basis[i])
               continue;
            x^=basis[i];
        }
        return (x==0);
    }
    int GetBig() {
        int ans=0;
        // max xor
        for (int i=Log-1; i>=0; i--) {
            if (have(ans,i))continue;
            if (basis[i]==0) continue;
           ans^=basis[i];
        }
        return ans;
    }
};
