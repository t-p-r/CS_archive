#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100 +10;
const string NO = "IMPOSSIBLE";

map<pair<int, int>, string> m;

string save(int x, int y, string s) {
    m[make_pair(x, y)] = s;
    return s;
}

string calc(int x, int y) {
    if (x == 0 && y == 0) return "";
    if (abs(x) % 2 == 0 && abs(y) % 2 == 0) return NO;
    if (abs(x) % 2 == 1 && abs(y) % 2 == 1) return NO;
    
    if (m.count(make_pair(x, y)) == 1) return m[make_pair(x, y)];
    
    if (abs(x) % 2 == 1) {
        if (y != 0 || (x - 1) / 2 != x) {
            string res1 = calc((x - 1) / 2, y / 2);
            if (res1 != NO) return save(x, y, "E" + res1);
        }
        if (y != 0 || (x + 1) % 2 != x) {
            string res2 = calc((x + 1) / 2, y / 2);
            if (res2 != NO) return save(x, y, "W" + res2);
        }
    } else {
        if (x != 0 || (y - 1) / 2 != y) {
            string res1 = calc(x / 2, (y - 1) / 2);
            if (res1 != NO) return save(x, y, "N" + res1);
        }
        if (x != 0 || (y + 1) / 2 != y) {
            string res2 = calc(x / 2, (y + 1) / 2);
            if (res2 != NO) return save(x, y, "S" + res2);
        }
    }
    return save(x, y, NO);
}

int cnt_ok = 0;
void solve() {
    int x, y;
    cin >> x >> y;
    string res = calc(x, y);
    cnt_ok += (res != NO);
    cout << res << "\n";
}

int main() {
    int ntests = 1;
    cin >> ntests;
    for(int tc = 1; tc <= ntests; ++tc) {
        solve();
    }
    cerr << cnt_ok << "/" << ntests << "\n";
}
