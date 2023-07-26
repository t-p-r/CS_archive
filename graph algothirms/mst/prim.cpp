#include <bits/stdc++.h>
#define file "kruskal1."
#define pair pair<long, long>
#define int long long
#define fi first
#define se second
#define INF 0x3f3f3f3f
using namespace std;
int n, m, ans = 0;
int u, v, w;
vector<pair> road[100001];
vector<pair> graph;
bool tham[100001] = {};
int key[100001];
int trace[100001];

void init() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    if (fopen("t.inp", "r")) {
        freopen("t.inp", "r", stdin);
        freopen("t.out", "w", stdout);
    } else {
        freopen(file "inp", "r", stdin);
        freopen(file "out", "w", stdout);
    }
}

void prim(int u) {
    tham[u] = 1;
    for (auto v : road[u]) {
        key[v.fi] = v.se;
        trace[v.fi] = u;
    }
    for (int tem = 1; tem < n; tem++) {
        int v1 = -1, v2 = -1, ans_w = INF;
        for (int i = 2; i <= n; i++) {
            if (!tham[i] && trace[i] && key[i] < ans_w) {
                ans_w = key[i];
                v1 = trace[i];
                v2 = i;
            }
        }
        if (v1 == -1 || v2 == -1) return;
        ans += ans_w;
        graph.push_back({v1, v2});
        tham[v2] = 1;
        for (auto v3 : road[v2]) {
            if (v3.se < key[v3.fi]) {
                key[v3.fi] = v3.se;
                trace[v3.fi] = v2;
            }
        }
    }
}

bool vs[100001] = {};
void dfs(int i) {
    vs[i] = 1;
    for (auto j : road[i])
        if (!vs[j.fi]) dfs(j.fi);
}
int kt() {
    int kq = 0;
    for (int i = 1; i != n; i++) {
        if (!vs[i]) {
            kq++;
            dfs(i);
        }
    }
    return kq;
}

void opt() {
    for (int i = 0; i < graph.size(); i++) {
        if (graph[i].fi > graph[i].se) swap(graph[i].fi, graph[i].se);
    }
    sort(graph.begin(), graph.end());
}

main() {
    init();

    cin >> n >> m;
    while (cin >> u >> v >> w) {
        road[u].push_back({v, w});
        road[v].push_back({u, w});
    }
    cout << kt() << '\n';

    int f = clock();
    fill(key + 2, key + n + 1, INF);
    for (int i = 1; i <= n; i++)
        if (!tham[i]) prim(i);

    opt();
    cout << clock() - f << '\n' << ans << '\n';
    for (auto i : graph)
        cout << i.fi << ' ' << i.se << '\n';
}
