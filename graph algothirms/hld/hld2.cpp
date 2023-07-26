#include <bits/stdc++.h>
#define allof(a) a.begin(), a.end()
#define int long long
#define fi first
#define se second
#define pb emplace_back
#define F(i, a, b) for (int i = a; i <= b; i++)
#define D(i, a, b) for (int i = a; i >= b; i--)
#define inf 0x3f3f3f3f3f3f3f3f
#define mn 10001
#define task "holiday"
using namespace std;
const int mod = 1337377;
typedef pair<int, int> ii;
typedef pair<int, ii> ip;
int g = 0;

class segment_tree {
#define mid (l + r >> 1)
#define lc 2 * id, l, mid
#define rc 2 * id + 1, mid + 1, r
   public:
    int LB = 0, RB = 0;
    vector<int> lo, hi, lazy;

    void down(int id, int l, int r) {
        if (!lazy[id]) return;
        int pre_lo = lo[id], pre_hi = hi[id];
        lo[id] = -pre_hi, hi[id] = -pre_lo;
        if (l != r) lazy[2 * id] ^= 1, lazy[2 * id + 1] ^= 1;
        lazy[id] = 0;
    }
    void range_update(int id, int l, int r, int u, int v) {
        down(id, l, r);
        if (v < l || r < u) return;
        if (u <= l && r <= v) {
            lazy[id] ^= 1;
            down(id, l, r);
            return;
        }
        range_update(lc, u, v);
        range_update(rc, u, v);
        lo[id] = min(lo[2 * id], lo[2 * id + 1]);
        hi[id] = max(hi[2 * id], hi[2 * id + 1]);
    }
    void point_update(int id, int l, int r, int i, int val) {
        down(id, l, r);
        if (i < l || r < i) return;
        if (l == r) {
            lo[id] = hi[id] = val;
            return;
        }
        point_update(lc, i, val);
        point_update(rc, i, val);
        lo[id] = min(lo[2 * id], lo[2 * id + 1]);
        hi[id] = max(hi[2 * id], hi[2 * id + 1]);
    }

    int get(int id, int l, int r, int u, int v) {
        down(id, l, r);
        if (v < l || r < u) return -inf;
        if (u <= l && r <= v) return hi[id];
        return max(get(lc, u, v), get(rc, u, v));
    }

   public:
    segment_tree() {}
    void resize(int l, int r) {
        LB = l, RB = r;
        lo.resize(4 * (r - l + 1) + 7, inf);
        hi.resize(4 * (r - l + 1) + 7, -inf);
        lazy.resize(4 * (r - l + 1) + 7, 0);
    }
    void point_update(int i, int val) { point_update(1, LB, RB, i, val); }
    void range_update(int u, int v) { range_update(1, LB, RB, u, v); }
    int get(int u, int v) { return u > v ? -inf : get(1, LB, RB, u, v); }
};
vector<int> a[mn];
int n, q;
int t[mn], h[mn], sz[mn];
int head[mn], edge_id[mn];
int chain[mn], tc[mn], p[mn][14];
vector<ii> adj[mn];
vector<segment_tree> st;

void prevs(int u, int pre) {
    sz[u] = 1;
    for (ii v : adj[u])
        if (v.fi != pre)
            p[v.fi][0] = t[v.fi] = u, h[v.fi] = h[u] + 1, prevs(v.fi, u),
            sz[u] += sz[v.fi];
}
int cnt = 1;
void dfs(int u, int pre, int len) {
    tc[u] = len;
    a[chain[u] = cnt].pb(len), edge_id[u] = a[cnt].size() - 1;
    int idx = -1, cur = -1, clen = -inf;
    for (ii v : adj[u])
        if (v.fi != pre && cur < sz[v.fi])
            cur = sz[v.fi], idx = v.fi, clen = v.se;
    if (idx != -1) dfs(idx, u, clen);
    for (ii v : adj[u])
        if (v.fi != pre && v.fi != idx) head[++cnt] = v.fi, dfs(v.fi, u, v.se);
}

int lca(int u, int v) {
    if (h[u] < h[v]) swap(u, v);
    int log = __lg(h[u]);
    D(i, log, 0) if (h[u] - (1 << i) >= h[v]) u = p[u][i];
    if (u == v) return u;
    D(i, log, 0) if (p[u][i] != p[v][i] && p[u][i]) {
        u = p[u][i];
        v = p[v][i];
    }
    return p[u][0];
}
int adv(int u, int k) {
    if (k == 0) return u;
    int log = __lg(k);
    D(i, log, 0) if (k >= (1 << i)) u = p[u][i], k -= (1 << i);
    return u;
}

ii e[mn];
vector<int> res;

int dir(int u, int v) {
    return adv(v, h[v] - h[u] - 1);
}
void solve() {
    int n;
    cin >> n;
    cnt = 1;
    memset(p, 0, sizeof(p));
    F(i, 1, n) adj[i].clear();
    F(i, 1, n) a[i].clear();
    st.clear();
    st.resize(n + 1);

    F(i, 1, n - 1) {
        int u, v, w;
        cin >> u >> v >> w;
        e[i] = {u, v};
        adj[u].pb(ii{v, w});
        adj[v].pb(ii{u, w});
    }

    prevs(1, -1);
    dfs(1, -1, -inf);
    st[1].resize(1, a[1].size() - 1);
    F(i, 2, cnt) st[i].resize(0, a[i].size() - 1);

    F(j, 1, 13) F(i, 1, n) p[i][j] = p[p[i][j - 1]][j - 1];
    F(i, 2, n) st[chain[i]].point_update(edge_id[i], tc[i]);
    string s;
    while (cin >> s) {
        if (s == "DONE") break;
        if (s == "CHANGE") {
            int i, val;
            cin >> i >> val;
            int u, v;
            tie(u, v) = e[i];
            if (h[u] > h[v]) swap(u, v);
            st[chain[v]].point_update(edge_id[v], val);
        } else {
            int u, v;
            cin >> u >> v;
            if (h[u] > h[v]) swap(u, v);
            int k = lca(u, v);

            if (s == "QUERY") {
                int cur = -inf;
                if (u == v)
                    res.pb(0);
                else {
                    while (chain[u] != chain[k]) {
                        cur = max(cur, st[chain[u]].get(0, edge_id[u]));
                        u = t[head[chain[u]]];
                    }
                    if (u != k)
                        cur = max(cur, st[chain[u]].get(edge_id[dir(k, u)],
                                                        edge_id[u]));

                    while (chain[v] != chain[k]) {
                        cur = max(cur, st[chain[v]].get(0, edge_id[v]));
                        v = t[head[chain[v]]];
                    }
                    if (v != k)
                        cur = max(cur, st[chain[v]].get(edge_id[dir(k, v)],
                                                        edge_id[v]));

                    res.pb(cur);
                }
            } else if (u != v) {
                while (chain[u] != chain[k]) {
                    st[chain[u]].range_update(0, edge_id[u]);
                    u = t[head[chain[u]]];
                }
                if (u != k)
                    st[chain[u]].range_update(edge_id[dir(k, u)], edge_id[u]);

                while (chain[v] != chain[k]) {
                    st[chain[v]].range_update(0, edge_id[v]);
                    v = t[head[chain[v]]];
                }
                if (v != k)
                    st[chain[v]].range_update(edge_id[dir(k, v)], edge_id[v]);
            }
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
#ifdef _TPR_
    freopen("t.inp", "r", stdin);
    freopen("t.out", "w", stdout);
#endif
    head[1] = 1;
    int t;
    cin >> t;
    while (t--)
        solve();
    for (int i : res)
        cout << i << '\n';
}