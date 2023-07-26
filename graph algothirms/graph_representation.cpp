#include <cstring>
#include <iostream>
#include <list>
#include <vector>
#define allof(a) a.begin(), a.end()
#define ll long long
#define fi first
#define se second
#define pb emplace_back
#define F(i, a, b) for (int i = a; i <= b; i++)
#define D(i, a, b) for (int i = a; i >= b; i--)
#define inf 0x3f3f3f3f3f3f3f3f
#define mn 200001
using namespace std;
const int mod = 1e9 + 7;
typedef pair<int, int> ii;
typedef pair<int, ii> ip;

int n;
int a[mn];
int t[mn], sz[mn];
int nxt[mn], to[mn], fir[mn], ecnt = 0;
#define for_edges(u, v) \
    for (int pt = fir[u], v = to[pt]; pt; pt = nxt[pt], v = to[pt])

void add_edge(int u, int v) {
    nxt[++ecnt] = fir[u];
    to[ecnt] = v;
    fir[u] = ecnt;
}
void remove(int u, int v) {
    if (to[fir[u]] == v) {
        fir[u] = nxt[fir[u]];
        return;
    }
    for (int i = fir[u]; i; i = nxt[i])
        if (to[nxt[i]] == v) {
            nxt[i] = nxt[nxt[i]];
            return;
        }
}
void prevs(int u, int pre, int& cur) {
    cur++;
    sz[u] = 1;
    for_edges(u, v) if (v != pre) t[v] = u, prevs(v, u, cur), sz[u] += sz[v];
}

ll res = 0;
int d[mn], on[21], off[21];
vector<int> ds;
void dfs(int u, int pre) {
    ds.pb(d[u] = d[pre] ^ a[u]);
    for_edges(u, v) if (v != pre) dfs(v, u);
}

void solve(int u, int pre)
// find the centroid,then solve the problems concerning the subtree containing u
{
    memset(on, 0, sizeof(on));
    memset(off, 0, sizeof(off));
    int cur_sz = 0;
    prevs(u, pre, cur_sz);
    while (1) {
        int cand = -1;
        for_edges(u, v) {
            if (v == pre) continue;
            if (sz[v] > cur_sz / 2) cand = v;
        }
        if (cand != -1)
            pre = u, u = cand;
        else
            break;
    }
    d[u] = 0;
    res += a[u];
    for_edges(u, v) {
        ds.clear();
        dfs(v, u);
        for (int dist : ds) {
            int cur = dist ^ a[u];
            res += cur;
            F(i, 0, 20) if (cur & (1 << i)) res += (ll)off[i] * (1 << i);
            else res += (ll)on[i] * (1 << i);
        }
        for (int dist : ds)
            F(i, 0, 20)
        if (dist & (1 << i))
            on[i]++;
        else
            off[i]++;
    }
    for_edges(u, v) remove(v, u), solve(v, u);
}

int32_t main() {
    ios::sync_with_stdio(0);
#ifdef _TPR_
    freopen("t.inp", "r", stdin);
    freopen("t.out", "w", stdout);
#endif
    cin >> n;
    F(i, 1, n) cin >> a[i];
    F(i, 2, n) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }
    solve(1, -1);
    cout << res;
}