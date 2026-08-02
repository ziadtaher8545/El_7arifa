class Trie
{
private:
    struct Node
    {
        Node *ch[26];
        int pre, end;

        Node()
        {
            pre = end = 0;
            memset(ch, 0, sizeof ch);
        }
    };
    Node *root = new Node();

public:
    void insert(string &s)
    {
        Node *cur = root;
        for (auto c : s)
        {
            int i = c - 'a';
            if (!cur->ch[i])
                cur->ch[i] = new Node();
            cur = cur->ch[i];
            cur->pre++;
        }
        cur->end++;
    }
    int query(string &s)
    {
        Node *cur = root;
        for (auto &c : s)
        {
            int x = c - 'a';
            if (!cur->ch[x])
                return 0;
            cur = cur->ch[x];
        }
        return cur->pre;
    }
};
