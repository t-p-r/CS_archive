#include <bits/stdc++.h>
#define allof(a) a.begin(), a.end()
#define int long long
#define fi first
#define se second
#define pb emplace_back
#define double long double
#define F(i, a, b) for (int i = a; i <= b; i++)
#define D(i, a, b) for (int i = a; i >= b; i--)
#define inf 0x3f3f3f3f3f3f3f3f
#define mn 50001
#define task "match1"
using namespace std;
const int mod = 1e9 + 7;
typedef pair<int, int> ii;
typedef pair<int, ii> ip;

// Given that the graph can be bipartited into two set U and V
int n, m, p;
int pu[mn], pv[mn];
int d[mn];
vector<int> adj[mn];

bool bfs() {
    // This BFS partitions the graph into layers
    queue<int> q;
    // Use the free verticles in U to form the first layer:
    F(u, 1, n) if (pu[u] == 0) d[u] = 0, q.push(u);
    else d[u] = inf;  // undefined

    d[0] = inf;  // placeholding

    /*At the first level of the search, there are only unmatched edges,
    since the free vertices in U are by definition not adjacent to any matched
    edges.*/
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (d[u] < d[0])
            for (int v : adj[u])
                if (d[pv[v]] == inf) d[pv[v]] = d[u] + 1, q.push(pv[v]);
        /* At subsequent levels of the search, the traversed edges are required
        to alternate between matched and unmatched. That is, when searching for
        successors from a vertex in U, only unmatched edges may be traversed,
        while from a vertex in V only matched edges may be traversed.
        The search terminates at the first layer k where one or more free
        vertices in V are reached.*/
    }

    return d[0] != inf;
}

bool dfs(int u) {
    if (u == 0) return true;
    for (int v : adj[u])
        if (d[pv[v]] == d[u] + 1 && dfs(pv[v]))
            return pv[v] = u, pu[u] = v, true;
    d[u] = inf;
    return false;
}
int hopcroft_karp() {
    int res = 0;
    while (bfs())
        F(u, 1, n) if (pu[u] == 0) res += dfs(u);
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
#ifdef _TPR_
    freopen("t.inp", "r", stdin);
    freopen("t.out", "w", stdout);
#endif
    cin >> n >> m >> p;
    while (p--) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
    }
    cout << hopcroft_karp();
}