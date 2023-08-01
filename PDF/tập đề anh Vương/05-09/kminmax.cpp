#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2000000 + 10;

int n, k;
int a[MAXN];

void kmin(int sgn = 1) {
    deque<int> s;
    for(int i = 1; i <= n; ++i) {
        while (s.size() > 0 && a[i] <= a[s.back()]) s.pop_back();
        s.push_back(i);
        while (i - s.front() + 1 > k) s.pop_front();
        if (i >= k) {
            cout << a[s.front()] * sgn;
            if (i < n) cout << " "; else cout << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    cin >> n >> k;
    for(int i = 1; i <= n; ++i) cin >> a[i];
    
    kmin();
    for(int i = 1; i <= n; ++i) a[i] = -a[i];
    kmin(-1);
}
