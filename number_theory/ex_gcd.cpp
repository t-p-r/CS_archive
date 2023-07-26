#include <bits/stdc++.h>
#define allof(a) a.begin(), a.end()
#define int long long
#define fi first
#define se second
#define pb push_back
#define F(i, a, b) for (int i = a; i <= b; i++)
#define D(i, a, b) for (int i = a; i >= b; i--)
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
using ii = pair<int, int>;
using u128 = __uint128_t;

ii ex(int a, int b)  // finding x,y that ax+by=__gcd(a,b)
{
    if (b == 0) return {1, 0};
    int x1, y1;
    tie(x1, y1) = ex(b, a % b);
    return {y1, x1 - y1 * (a / b)};
}
ii diop(int a, int b, int c)  // solving ax+by=c
{
    int x, y;
    tie(x, y) = ex(a, b);
    int g = __gcd(a, b);
    return (c % g == 0) ? ii{x * c / g, y * c / g} : ii{inf, inf};
}
int32_t main() {
    ios::sync_with_stdio(0);
#ifdef _TPR_
    freopen("t.inp", "r", stdin);
    freopen("t.out", "w", stdout);
#endif
    int a, b, c;
    while (cin >> a >> b >> c)
        cout << diop(a, b, c).fi << ' ' << diop(a, b, c).se << '\n';
}