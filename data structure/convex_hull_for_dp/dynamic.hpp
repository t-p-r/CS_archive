#include <bits/stdc++.h>
using namespace std;

struct line {
    mutable int a, b, p;
    bool operator<(const line& o) const { return a < o.a; }
    bool operator<(const int& x) const { return p < x; }
};
class convex_hull : private multiset<line, less<>> {
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    static const int inf = 0x3f3f3f3f3f3f3f3f;

   public:
    int div(int a, int b) {  // floored division
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool overtake(iterator x, iterator y) {
        if (y == end()) return x->p = inf, false;
        if (x->a == y->a)
            x->p = x->b > y->b ? inf : -inf;
        else
            x->p = div(y->b - x->b, x->a - y->a);  //(b2-b1)/(a1-a2)
        return x->p >= y->p;
    }
    void add(int a, int b) {
        auto z = insert({a, b, 0}), y = z++, x = y;
        while (overtake(y, z))
            z = erase(z);
        if (x != begin() && overtake(--x, y)) overtake(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            overtake(x, erase(y));
    }
    int get(int x) {
        if (empty()) return -inf;
        auto l = *lower_bound(x);
        return l.a * x + l.b;
    }
} st;