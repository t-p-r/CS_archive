#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define F(i, a, b) for (int i = a; i <= b; i++)
#define D(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
typedef pair<int, int> ii;
const int inf = 1610612741;
int n, m;
int t[1000001];
char w[1000001], s[1000001];

void build() {
    F(i, 2, m) {
        int k = t[i - 1];
        while (k && w[k + 1] != w[i])
            k = t[k];
        t[i] = (w[k + 1] == w[i]) ? k + 1 : 0;
    }
}
void kmp() {
    int k = 0;
    F(i, 1, n) {
        while (k && w[k + 1] != s[i])
            k = t[k];
        if (w[k + 1] == s[i]) k++;
        if (k == m) {
            cout << i - m + 1 << ' ';
            k = t[k];
        }
    }
}
int32_t main() {
    ios::sync_with_stdio(0);
#ifdef _TPR_
    freopen("t.inp", "r", stdin);
    freopen("t.out", "w", stdout);
#endif
    cin >> s + 1 >> w + 1;
    n = strlen(s + 1);
    m = strlen(w + 1);
    build();
    kmp();
}