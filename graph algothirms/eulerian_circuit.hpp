#include <bits/stdc++.h>
using namespace std;

namespace eulerian_circuit {
const int mn = 1e5 + 11, mod = 1e9 + 7;
int n, m;
int deg[mn];
unordered_set<int> adj[mn];
vector<int> circ;

void generate_eulerian_circuit() {
    vector<int> st(1, 1);
    while (!st.empty()) {
        int u = st.back();
        if (adj[u].empty()) {
            st.pop_back();
            circ.emplace_back(u);
        } else {
            int v = *adj[u].begin();
            st.emplace_back(v);
            adj[u].erase(v);
            adj[v].erase(u);
        }
    }
}
void exec() {
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        adj[u].emplace(v);
        adj[v].emplace(u);
        deg[u]++, deg[v]++;
    }
    for (int i = 1; i <= n; i++)
        if (deg[i] & 1) {
            cout << -1;
            throw("Vertex with odd degree; concept requirement not met");
            // An Eulerian circuit enters a vertex as frequently as it leaves,
            // thus the degree of all vertex must be even.
        }
    generate_eulerian_circuit();
}
}  // namespace eulerian_circuit