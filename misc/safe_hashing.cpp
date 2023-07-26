#include <bits/extc++.h>
#include <bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define pb push_back
#define F(i, a, b) for (int i = a; i <= b; i++)
#define D(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
using namespace chrono;
using namespace __gnu_pbds;
using __gnu_pbds::rc_binomial_heap_tag;
const int inf = 1e9 + 7;

struct chash {
    const int rng = steady_clock::now().time_since_epoch().count();
    const uint64_t c = uint64_t(4e18 * acos(0)) | 71;
    int operator()(int x) const { return __builtin_bswap64((x ^ rng) * c); }
};
struct better_chash {
    const int rng = (int)(make_unique<char>().get()) ^
                    steady_clock::now().time_since_epoch().count();
    static uint64_t hash_f(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    static int hash_combine(int a, int b) { return a * 31 + b; }
    int operator()(int x) const { return hash_f(x) ^ rng; }
};
gp_hash_table<int, int, chash> mp;

signed main() {
    ios::sync_with_stdio(0);
#ifdef _TPR_
    freopen("t.inp", "r", stdin);
    freopen("t.out", "w", stdout);
#endif
    int n, a;
    cin >> n;
    while (n--) {
        cin >> a;
        mp[a]++;
    }
    cout << mp.size() << '\n';
    for (auto a : mp)
        cout << a.fi << ' ' << a.se << '\n';
}