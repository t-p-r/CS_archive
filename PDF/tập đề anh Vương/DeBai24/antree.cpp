#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200000 + 10;
const int MAXL = 20;

struct Edge {
    int id;
    int u, v, c;
    
    int next(int x) {
        return (x == u) ? v : u;
    }
};

int n;
vector<int> adj[MAXN];
Edge E[MAXN];
int par[MAXN][MAXL + 10];
int depth[MAXN], EID[MAXN];
long long len[MAXN];

void DFS(int u, int p) {
    for(int eid : adj[u]) {
        int v = E[eid].next(u);
        if (v != p) {
            depth[v] = depth[u] + 1;
            len[v] = len[u] + E[eid].c; // len[v] = tong do dai goc->v
            EID[v] = eid;
            par[v][0] = u;
            DFS(v, u);
        }
    }
}

int jump(int u, int h) {
    for(int i = MAXL; i >= 0; --i)
        if (h >= (1 << i)) {
            u = par[u][i];
            h -= (1 << i);
        }
    return u;
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    v = jump(v, depth[v] - depth[u]);
    if (u == v) return u;
    for(int i = MAXL; i >= 0; --i)
        if (par[u][i] != par[v][i]) {
            u = par[u][i];
            v = par[v][i];
        }
    return par[u][0];
}

// c = lca(a, b)
// get_len() se return tong do dai duong di tu a->b
// voi dieu kien da di duoc DUNG k CANH
long long get_len(int a, int b, int c, int k) {
    int da = depth[a] - depth[c], db = depth[b] - depth[c];
    if (k <= da) return len[a] - len[ jump(a, k) ];
    else return (len[a] + len[b] - len[c] * 2) - (len[b] - len[ jump(b, da + db - k) ]);
}

int query(int a, int b, long long t) {
    int c = lca(a, b);
    int dist = depth[a] + depth[b] - 2 * depth[c];
    long long len_ab = len[a] + len[b] - len[c] * 2;

    if (len_ab <= t) return -1;
    
    int low = 1, high = dist;
    while (low <= high) {
        int mid = (low + high) / 2;
        long long x = get_len(a, b, c, mid);
        if (x - 1 < t) low = mid + 1;
        else high = mid - 1;
    }
    
    int k = high + 1;
    int da = depth[a] - depth[c], db = depth[b] - depth[c];
    if (k <= da) return EID[ jump(a, k - 1) ];
    else return EID[ jump(b, dist - k) ];
}

int main() {
    //freopen("input.txt", "r", stdin);
    
    cin >> n;
    for(int i = 1; i <= n - 1; ++i) {
        E[i].id = 1;
        cin >> E[i].u >> E[i].v >> E[i].c;
        adj[ E[i].u ].push_back(i);
        adj[ E[i].v ].push_back(i);
    }
    
    DFS(1, -1);
    for(int j = 1; j <= MAXL; ++j) {
        for(int i = 1; i <= n; ++i)
            par[i][j] = par[ par[i][j - 1] ][j - 1];
    }
    
    int q;
    cin >> q;
    for(int i = 1; i <= q; ++i) {
        int a, b;
        long long t;
        cin >> a >> b >> t;
        cout << query(a, b, t) << "\n";
    }
}
