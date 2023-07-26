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
bool sieve[100000001];

void atkin(int limit) {
    int n;
    sieve[2] = sieve[3] = 1;
    for (int x = 1; x * x < limit; x++) {
        for (int y = 1; y * y < limit; y++) {
            n = (4 * x * x) + (y * y);
            if (n <= limit && (n % 12 == 1 || n % 12 == 5)) sieve[n] ^= 1;

            n = (3 * x * x) + (y * y);
            if (n <= limit && n % 12 == 7) sieve[n] ^= 1;

            n = (3 * x * x) - (y * y);
            if (x > y && n <= limit && n % 12 == 11) sieve[n] ^= 1;
        }
    }
    for (int r = 5; r * r < limit; r++)
        if (sieve[r])
            for (int i = r * r; i < limit; i += r * r)
                sieve[i] = 0;
}

main() {
#ifdef _TPR_
    freopen("t.inp", "r", stdin);
    freopen("t.out", "w", stdout);
#endif
    atkin(100000000);
    cout << clock() << '\n';

    int n, m;
    cin >> n >> m;
    for (int i = n; i <= m; i++)
        if (sieve[i]) cout << i << '\n';
}
