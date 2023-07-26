#include <bits/stdc++.h>
#define int long long
using namespace std;

using ll = long long;
const int mm = 20005;

ll f[mm], g[mm];
int w, v, a;

ll cal(int i, int j) {
    return f[i] + (j - i) / w * v;
}

struct base_deque {
    int l = mm - 1, r = mm - 1, dq[2 * mm];
    int size() { return r - l; }
    int back() { return dq[r - 1]; }
    int front() { return dq[l]; }
    void pop_front() { l++; }
    void pop_back() { r--; }

    void emplace_back(int val) { dq[r++] = val; }
    void emplace_front(int val) { dq[--l] = val; }
    void clear() { l = r = 20000; }
} dq;
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
#ifdef _TPR_
    freopen("t.inp", "r", stdin);
    freopen("t.out", "w", stdout);
#endif
    memset(f, 0xc0, sizeof f);
    f[0] = 0;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        memcpy(f, g, sizeof g);
        cin >> a >> w >> v;
        for (int d = 0; d < w; d++) {
            dq.clear();
            for (int x = d; x <= m; x += w) {
                while (dq.size() && dq.front() < x - w * a)
                    dq.pop_front();
                while (dq.size() && cal(dq.back(), x) <= f[x])
                    dq.pop_back();
                dq.emplace_back(x);
                g[x] = cal(dq.front(), x);
            }
        }
    }
    cout << *max_element(g, g + m + 1) << '\n';
}