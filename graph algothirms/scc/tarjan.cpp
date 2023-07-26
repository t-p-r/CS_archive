#include <bits/stdc++.h>
#define file "tarjan"
#define ii pair<int, int>
#define fi first
#define se second
#define pb push_back
#define F(i, a, b) for (int i = (a); i <= (b); i++)
#define D(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
const int inf = 1e9 + 7;
int n, m, i, j;
int cnt = 0, res = 0;
int vs[10001], lo[10001];
int onStack[10001];
vector<int> adj[10001];
vector<int> scc[10001];
vector<int> st;

void op(const string ff) {
    ios::sync_with_stdio(0);
    freopen((ff + ".inp").c_str(), "r", stdin);
    freopen((ff + ".out").c_str(), "w", stdout);
}
void init() {
    op((fopen("t.inp", "r")) ? "t" : file);
}

void dfs(int u) {
    st.pb(u);
    onStack[u] = 1;
    lo[u] = vs[u] = ++cnt;
    for (int v : adj[u]) {
        if (!vs[v]) dfs(v);
        if (onStack[v]) lo[u] = min(lo[u], lo[v]);
    }
    if (vs[u] == lo[u]) {
        res++;
        while (1) {
            int v = st.back();
            scc[res].pb(v);
            st.pop_back();
            onStack[v] = 0;
            if (u == v) break;
        }
    }
}
int main() {
    init();
    cin >> n >> m;
    while (m--) {
        cin >> i >> j;
        adj[i].pb(j);
    }
    F(i, 1, n) if (!vs[i]) dfs(i);
    cout << res;
}
