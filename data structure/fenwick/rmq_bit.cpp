#include <bits/stdc++.h>
#define allof(a) a.begin(), a.end()
#define int long long
#define fi first
#define se second
#define pb push_back
#define F(i, a, b, k) for (int i = a; i <= b; i += k)
#define D(i, a, b, k) for (int i = a; i >= b; i -= k)
#define lsb(i) (i & (-i))
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
using ii = pair<int, int>;
using u128 = __uint128_t;
int n, q;
int u, v;
int a[100001];
int min1[100001], min2[100001];
int max1[100001], max2[100001];
// ___1[i] quản lý đọan [i-lsb(i)+1,i] ; ___2[i] quản lý đoạn [i,i+lsb(i)-1];

void op(const string ff) {
    freopen((ff + ".inp").c_str(), "r", stdin);
    freopen((ff + ".out").c_str(), "w", stdout);
}
void init() {
    op((fopen("t.inp", "r")) ? "t" : "ggez");
}

void update(int p, int val) {
    F(i, p, n, lsb(i)) {
        min1[i] = min(min1[i], val);
        max1[i] = max(max1[i], val);
    }
    D(i, p, 1, lsb(i)) {
        min2[i] = min(min2[i], val);
        max2[i] = max(max2[i], val);
    }
}

int get_min(int l, int r) {
    int ans = inf, i = l;
    while (i + lsb(i) <= r) {
        ans = min(ans, min2[i]);
        i += lsb(i);
    }
    i = r;
    while (i - lsb(i) >= l) {
        ans = min(ans, min1[i]);
        i -= lsb(i);
    }
    return min(ans, a[i]);
}

int get_max(int l, int r) {
    int ans = -inf, i = l;
    while (i + lsb(i) <= r) {
        ans = max(ans, max2[i]);
        i += lsb(i);
    }
    i = r;
    while (i - lsb(i) >= l) {
        ans = max(ans, max1[i]);
        i -= lsb(i);
    }
    return max(ans, a[i]);
}

signed main() {
    init();
    cin >> n >> q;
    F(i, 1, n, 1) cin >> a[i];
    memset(min1, 0x3f, sizeof(min1));
    memset(min2, 0x3f, sizeof(min2));
    fill(max1 + 1, max1 + n + 1, -inf);
    fill(max2 + 1, max2 + n + 1, -inf);
    F(i, 1, n, 1) update(i, a[i]);
    F(i, 1, q, 1) {
        cin >> u >> v;
        cout << get_min(u, v) << ' ' << get_max(u, v) << '\n';
    }
}
