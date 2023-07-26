#include <bits/stdc++.h>
#define file "kruskal"
#define int long long
#define fi first
#define se second
#define pb push_back
#define F(i, a, b) for (int i = a; i <= b; ++i)
#define D(i, a, b) for (int i = a; i >= b; --i)
using namespace std;
typedef pair<int, int> ii;
typedef pair<int, ii> ip;
int n, m, ans = 0;
int u, v, w;
vector<int> road[100001];
vector<pair<int, int>> graph;
vector<ip> pq;
int p[100001] = {}, r[100001];

void op(const string ff) {
    ios::sync_with_stdio(0);
    freopen((ff + ".inp").c_str(), "r", stdin);
    freopen((ff + ".out").c_str(), "w", stdout);
}
void init() {
    op((fopen("t.inp", "r")) ? "t" : file);
}

int par(int i) {
    return (p[i] < 0) ? i : (p[i] = par(p[i]));
}
void uni(int i, int j) {
    if ((i = par(i)) == (j = par(j))) return;
    if (r[i] < r[j]) swap(i, j);
    p[j] = i;
    if (r[i] == r[j]) r[i]++;
}

void kruskal() {
    sort(pq.begin(), pq.end(), greater<ip>());
    auto cnt = --pq.end();
    while (cnt != --pq.begin()) {
        while (par(cnt->se.fi) == par(cnt->se.se)) {
            --cnt;
            if (cnt == --pq.begin()) return;
        }
        int u = cnt->se.fi;
        int v = cnt->se.se;
        int w = cnt->fi;
        ans += w;
        uni(u, v);
        --cnt;
    }
}

main() {
    init();
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> u >> v >> w;
        road[u].pb(v);
        road[v].pb(u);
        pq.push_back({w, {u, v}});
    }
    fill(p + 1, p + n + 1, -1);
    int f = clock();
    cout << "input time: " << f << '\n';
    kruskal();
    cout << ans << '\n';
    cout << "calculating time: " << clock() - f << '\n';
}
