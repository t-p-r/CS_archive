#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mn = 5001, mm = 20011;

template <typename t>
bool ckmax(t& target, const t& source) {
    return target < source ? target = source, 1 : 0;
}
template <typename t>
bool ckmin(t& target, const t& source) {
    return target > source ? target = source, 1 : 0;
}

int n, m;
int w[mn], v[mn], c[mn];
pair<int, int> sorted[mn];
int se[mn];
int dp[mm];

vector<int> pre[mm];
vector<int> mval[mm];
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

// dp[i][j] = max: dp[i-1][j-k*w[i]] + k*v[i]
// <-> dp[a*w[i]+b] = max: pre[(a-k)*w[i]+b] + k*v[i] (0 <= k <= min(c[i],a))
// <-> dp[a*w[i]+b] = a*v[i] + max: eval(a-k) (0 <= k <= min(c[i],a))
// with eval(x) = pre[a*x+b] - a*v[i]
// (can be solved by a deque, as demonstrated below)
//
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
#ifdef _TPR_
    freopen("t.inp", "r", stdin);
    freopen("t.out", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> w[i] >> v[i] >> c[i];
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < w[i]; j++)
            pre[j].clear(), mval[j].clear();
        for (int j = 0; j <= m; j++) {
            int b = j % w[i], a = j / w[i];
            pre[b].emplace_back(dp[j] - a * v[i]);
        }
        int k = c[i];
        for (int j = 0; j < w[i]; j++) {
            mval[j].resize(pre[j].size());
            for (int i = 0; i < pre[j].size(); i++) {
                while (dq.size() && pre[j][dq.back()] <= pre[j][i])
                    dq.pop_back();
                dq.emplace_back(i);
                while (dq.size() && dq.front() < i - k)
                    dq.pop_front();
                mval[j][i] = pre[j][dq.front()];
            }
            dq.clear();
        }
        for (int j = m; j >= w[i]; j--) {
            int a = j / w[i], b = j % w[i];  // j=a*w[i]+b
            ckmax(dp[j], mval[b][a] + a * v[i]);
        }
    }
    cout << dp[m];
}