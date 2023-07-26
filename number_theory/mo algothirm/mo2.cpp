#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define F(i, a, b) for (int i = a; i <= b; i++)
#define D(i, a, b) for (int i = a; i >= b; i--)
#define mn 500001
using namespace std;
using ii = pair<int, int>;
int n, m, s;
int a[mn];

class query {
   public:
    int tt, l, r;
    bool operator<(query k) {
        if (l / s == k.l / s) return ((l / s) & 1) ? r < k.r : r > k.r;
        return l / s < k.l / s;
    }
} q[mn];

int ans[mn];
class mo_holder {
   private:
    vector<int> st;
    int cnt[mn] = {};
    bool in[mn] = {};
    void insert(int k) {
        if (++cnt[k] == 1 && !in[k]) in[k] = 1, st.pb(k);
    }
    void erase(int k) {
        if (--cnt[k] == 1 && !in[k]) in[k] = 1, st.pb(k);
    }
    inline void extr(int r1, int r2) {
        if (r1 < r2) F(i, r1 + 1, r2) insert(a[i]);
        if (r1 > r2) D(i, r1, r2 + 1) erase(a[i]);
    }
    inline void extl(int l1, int l2) {
        if (l1 < l2) F(i, l1, l2 - 1) erase(a[i]);
        if (l1 > l2) D(i, l1 - 1, l2) insert(a[i]);
    }

   public:
    void init(int l, int r) { F(i, l, r) insert(a[i]); }
    void move(int l1, int r1, int l2, int r2) {
        int l = min(l1, l2), r = max(r1, r2);
        extr(r1, r);
        extl(l1, l);
        extl(l, l2);
        extr(r, r2);
    }
    inline int get() {
        while (st.size() && cnt[st.back()] != 1)
            in[st.back()] = 0, st.pop_back();
        return st.size() ? st.back() : 0;
    }
} st;

int32_t main() {
    ios::sync_with_stdio(0);
#ifdef _TPR_
    freopen("t.inp", "r", stdin);
    freopen("t.out", "w", stdout);
#endif
    cin >> n;
    s = sqrt(n);
    F(i, 1, n) cin >> a[i];
    cin >> m;
    F(i, 1, m) {
        q[i].tt = i;
        cin >> q[i].l >> q[i].r;
    }
    sort(q + 1, q + m + 1);
    st.init(q[1].l, q[1].r);
    ans[q[1].tt] = st.get();
    F(i, 2, m) {
        st.move(q[i - 1].l, q[i - 1].r, q[i].l, q[i].r);
        ans[q[i].tt] = st.get();
    }
    F(i, 1, m) cout << ans[i] << '\n';
}