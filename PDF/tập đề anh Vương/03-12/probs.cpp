#include <bits/stdc++.h>

using namespace std;

const int MAXK =  5 + 2;
const int MAXB = 50;
const int MOD = (int)(1e9) + 7;

int n, k;
int dp[MAXB][(1 << MAXK)][MAXK];
int memo[(1 << MAXK)][(1 << MAXK)];

int get_bit(int x, int n) { return ((x >> n) & 1); }
int check(int less, int mask) {
    if (memo[less][mask] != 0) return (memo[less][mask]);
    int new_less = 0;
    for(int i = 0; i + 1 < k; ++i) {
        int j = ( get_bit(mask, i) < get_bit(mask, i + 1) 
              || ( get_bit(less, i) == 1 && get_bit(mask, i) == get_bit(mask, i + 1) ) ) 
              ? 1 : 0;
        new_less += (1 << i) * j;
    }
    new_less += (1 << (k - 1)) * (get_bit(less, k - 1) || get_bit(mask, 0));
     
    return memo[less][mask] = new_less;
}

void add(int &a, int b) { a = (a + b) % MOD; }

int solve() {
    int len = 0; int nn = n; while (nn > 0) { len++; nn = nn / 2; };
    dp[0][0][0] = 1;
    for(int i = 0; i < len; ++i) {
        for(int less = 0; less < (1 << k); ++less)
            for(int carry = 0; carry <= k; ++carry) {
                if (dp[i][less][carry] == 0) continue;                
                for(int mask = 0; mask < (1 << k); ++mask) {
                    int nxt_less = check(less, mask);
                    if (nxt_less == -1) continue;
                    
                    int s = __builtin_popcount(mask);
                    int r = (s + carry) % 2, p = (s + carry) / 2;
                    if (r == get_bit(n, i)) {
                        add(dp[i + 1][nxt_less][p], dp[i][less][carry]);
                    }
                }
            }
    }
    
    int res = dp[len][(1 << k) - 1][0];
    
    return res;
}

int main() {
    cin >> n >> k;
    
    assert(1 <= k && k <= 5);
    assert(1 <= n && n <= (int)(1e9));
    
    int res = solve(); 
    cout << res << "\n"; 
    
    return 0;
}
