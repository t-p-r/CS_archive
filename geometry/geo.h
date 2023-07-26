#include <bits/stdc++.h>
#define allof(a) a.begin(), a.end()
#define int int64_t
#define fi first
#define se second
#define pb push_back
#define F(i, a, b) for (int i = a; i <= b; i++)
#define D(i, a, b) for (int i = a; i >= b; i--)
#define inf 0x3f3f3f3f3f3f3f3f
#define mn 100001
#define task "convexhull"
#define mp make_pair
using namespace std;
typedef pair<int, int> ii;

namespace geo {
typedef long long coord;
struct point {
    coord x, y;
    point operator-() {
        point res = *this;
        res.x = -res.x, res.y = -res.y;
        return res;
    }
    point operator=(const point& k) {
        this->x = k.x, this->y = k.y;
        return *this;
    }

    friend istream& operator>>(istream& is, point& k) {
        is >> k.x >> k.y;
        return is;
    }
    friend ostream& operator<<(ostream& os, point& k) {
        os << k.x << ' ' << k.y;
        return os;
    }
} a;
typedef point vector;

double len(const vector& u) {
    return sqrt(u.x * u.x + u.y * u.y);
}
coord sqrlen(const vector& u) {
    return u.x * u.x + u.y * u.y;
}

vector operator+(const vector& u, const vector& v) {
    return {u.x + v.x, u.y + v.y};
}
vector operator-(const vector& u, const vector& v) {
    return {u.x - v.x, u.y - v.y};
}
coord operator%(const vector& u, const vector& v) {
    return u.x * v.x + u.y * v.y;
}
coord operator*(const vector& u, const vector& v) {
    return u.x * v.y - u.y * v.x;
}
double getrad(const vector& u, const vector& v) {
    return atan2(u * v, u % v);
}

bool ccw(const point& d, const point& e, const point& f) {
    return (e - d) * (f - e) > 0;
}
std::vector<point> graham_scan(std::vector<point> p) {
    if (p.size() < 4) return p;

    int i = 0, n = p.size();
    F(j, 1, n - 1)
    if (p[j].y < p[i].y || p[j].y == p[i].y && p[j].x < p[i].x) i = j;
    swap(p[i], p[0]);
    a = p[0];

    sort(p.begin() + 1, p.end(), [](const point& b, const point& c) {
        vector u = b - a, v = c - a;
        coord temp = u * v;
        return temp > 0 || temp == 0 && sqrlen(u) < sqrlen(v);
    });

    int m = 0;
    std::vector<point> q;
    F(i, 0, n - 1) {
        while (m >= 2 && !ccw(q[m - 2], q[m - 1], p[i]))
            q.pop_back(), --m;
        q.pb(p[i]), m++;
    }
    while (m >= 2 && !ccw(q[m - 2], q[m - 1], q[0]))
        q.pop_back(), m--;
    return q;
}
int area(std::vector<point> p) {
    int n = p.size(), res = 0;
    p.pb(p[0]);
    F(i, 0, n - 1) res += p[i] * p[i + 1];
    return res;
}
}  // namespace geo