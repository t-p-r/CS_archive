#include <bits/stdc++.h>
#define allof(a) a.begin(), a.end()
#define ll long long
#define fi first
#define se second
#define pb push_back
#define F(i, a, b) for (int i = a; i <= b; i++)
#define D(i, a, b) for (int i = a; i >= b; i--)
#define inf 0x3f3f3f3f
#define mn 1000001
#define task "holiday"
using namespace std;
const int mod = 1e9 + 7;
typedef pair<int, int> ii;
typedef pair<int, ii> ip;

int n;
int z[mn];
char a[mn];
int32_t main() {
    ios::sync_with_stdio(0);
#ifdef _TPR_
    freopen("t.inp", "r", stdin);
    freopen("t.out", "w", stdout);
#endif
    cin >> a + 1;
    n = strlen(a + 1);

    // Z algothirm :
    z[1] = n;
    int l = 1, r = 1;
    F(i, 2, n) {
        if (i > r) {
            l = r = i;
            while (r <= n && a[r - l + 1] == a[r])
                r++;
            z[i] = r - l, r--;  //[l,r)
        } else {
            int k =
                i - l + 1;  // a[i..] match with a[k..] at least r-i+1 elements
            if (z[k] < r - i + 1)
                z[i] = z[k];
            else {
                l = i;
                while (r <= n && a[r - l + 1] == a[r])
                    r++;
                z[i] = r - l, r--;
            }
        }
    }
    int cur = 0, pcur = 0, res = 0, pos = 0;
    F(i, 2, n) {
        if (i + z[i] - 1 == n && cur >= z[i] && res < z[i])
            res = z[i], pos = pcur;

        if (cur < z[i]) cur = z[i], pcur = i;
    }
    if (pos == 0)
        cout << "Just a legend";
    else
        F(i, pos, pos + res - 1) cout << a[i];
}