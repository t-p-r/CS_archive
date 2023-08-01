#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f3f3f3f3f;

struct line {
    int a, b;
    line() : a(0), b(-inf) {}
    line(int a, int b) : a(a), b(b) {}
};
int f(const line& g, const int& x) {
    return g.a * x + g.b;
}

template <int LB, int RB>
class li_chao_tree  // controlling array w' index from LB to RB
{
   public:
    line st[4 * (RB - LB + 1)];

    void add(line nw, int id = 1, int l = LB, int r = RB) {
        int m = (l + r) / 2;
        bool lef = f(nw, l) > f(st[id], l);
        bool mid = f(nw, m) > f(st[id], m);
        if (mid) {
            swap(st[id], nw);
        }
        if (r - l == 1) {
            return;
        } else if (lef != mid) {
            add(nw, 2 * id, l, m);
        } else {
            add(nw, 2 * id + 1, m, r);
        }
    }
    int get(int x, int id = 1, int l = LB, int r = RB) {
        int m = (l + r) / 2;
        if (r - l == 1) {
            return f(st[id], x);
        } else if (x < m) {
            return max(f(st[id], x), get(x, 2 * id, l, m));
        } else {
            return max(f(st[id], x), get(x, 2 * id + 1, m, r));
        }
    }
};
