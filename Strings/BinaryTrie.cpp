class BinaryTrie
{
private:
    struct Node
    {
        Node *ch[2];
        int fr;
        Node() : fr(0)
        {
            memset(ch, 0, sizeof ch);
        }
    };

public:
    Node *root = new Node();
    BinaryTrie() {}
    void insert(ll x)
    {
        Node *cur = root;
        for (int i = 62; i >= 0; i--)
        {
            int bit = (x >> i) & 1;
            if (!cur->ch[bit])
                cur->ch[bit] = new Node();
            cur = cur->ch[bit];
            cur->fr++;
        }
    }
    void erase(ll x)
    {
        Node *cur = root;
        for (int i = 62; i >= 0; i--)
        {
            int bit = (x >> i) & 1;
            cur = cur->ch[bit];
            cur->fr--;
        }
    }
    ll maxXor(ll x)
    {
        Node *cur = root;
        ll ret = 0;
        for (int i = 62; i >= 0; i--)
        {
            int bit = (x >> i) & 1;

            if (cur->ch[!bit] && cur->ch[!bit]->fr > 0)
                ret |= 1LL << i, cur = cur->ch[!bit];
            else
                cur = cur->ch[bit];
        }
        return ret;
    }
    ll minXor(ll x)
    {
        Node *cur = root;
        ll ret = 0;
        for (int i = 62; i >= 0; i--)
        {
            int bit = (x >> i) & 1;

            if (cur->ch[bit] && cur->ch[bit]->fr > 0)
                cur = cur->ch[bit];
            else
                ret |= 1LL << i, cur = cur->ch[!bit];
        }
        return ret;
    }
    ll query(ll x, ll l)
    { // x ^ lst < l
        Node *cur = root;
        ll cnt = 0;
        for (int i = 62; i >= 0; --i)
        {
            int xb = (x >> i) & 1;
            int lb = (l >> i) & 1;

            if (lb == 1 && cur->ch[xb])
                cnt += cur->ch[xb]->fr;
            xb ^= lb;
            if (!cur->ch[xb])
                return cnt;
            cur = cur->ch[xb];
        }
        return cnt;
    }
};
