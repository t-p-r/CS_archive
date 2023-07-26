#include <bits/stdc++.h>

struct fenwick_tree {
    std::vector<int> fen1, fen2;
    fenwick_tree() {}
    fenwick_tree(int n) : fen1(n + 1), fen2(n + 1) {}

    inline int lsb(int i) { return i & (-i); }
    void update(std::vector<int>& f, int i, int val) {
        for (; i < f.size(); i += lsb(i))
            f[i] += val;
    }

    inline void update(int l, int r, int val) {
        update(fen1, l, val);
        update(fen1, r + 1, -val);
        update(fen2, l, val * (l - 1));
        update(fen2, r + 1, -val * r);
    }
    int query(const std::vector<int>& f, int i) {
        int ans = 0;
        for (; i; i -= lsb(i))
            ans += f[i];
        return ans;
    }
    int get(int p) { return query(fen1, p) * p - query(fen2, p); }
    int get(int l, int r) { return get(r) - get(l - 1); }
};
