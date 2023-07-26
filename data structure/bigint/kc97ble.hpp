#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> bigint;
// UNSIGNED
const int BASE = 1e9, LEN = 9;

void fix(bigint& a) {
    a.push_back(0);
    for (int i = 0; i < a.size() - 1; ++i) {
        a[i + 1] += a[i] / BASE;
        a[i] %= BASE;
        if (a[i] < 0) a[i] += BASE, a[i + 1]--;
    }
    while (a.size() > 1 && a.back() == 0)
        a.pop_back();
}

bigint operator*(const bigint& a, const bigint& b) {
    bigint c(a.size() + b.size() + 1);
    for (int i = 0; i < a.size(); ++i)
        for (int j = 0; j < b.size(); ++j) {
            c[i + j] += a[i] * b[j];
            c[i + j + 1] += c[i + j] / BASE;
            c[i + j] %= BASE;
        }
    return fix(c), c;
}

bigint to_bigint(int x) {  // x < Base
    assert(x < BASE);
    return bigint(1, x);
}

bigint operator+(bigint a, const bigint& b) {
    a.resize(max(a.size(), b.size()));
    for (int i = 0; i < b.size(); ++i)
        a[i] += b[i];
    return fix(a), a;
}
bigint operator-(bigint a, const bigint& b) {
    for (int i = 0; i < b.size(); ++i)
        a[i] -= b[i];
    return fix(a), a;
}
bigint operator*(bigint a, int x) {  // x < BASE
    assert(x < BASE);
    for (int i = 0; i < a.size(); ++i)
        a[i] *= x;
    return fix(a), a;
}

bool operator<(const bigint& a, const bigint& b) {
    if (a.size() != b.size()) return a.size() < b.size();
    for (int i = a.size() - 1; i >= 0; i--)
        if (a[i] != b[i]) return a[i] < b[i];
    return false;
}

bigint operator/(bigint a, int x) {  // x < BASE
    assert(x < BASE);
    for (int i = (int)a.size() - 1, r = 0; i >= 0; --i, r %= x) {
        r = r * BASE + a[i];
        a[i] = r / x;
    }
    return fix(a), a;
}
int operator%(const bigint& a, int x) {  // x < BASE
    int r = 0;
    for (int i = (int)a.size() - 1; i >= 0; --i)
        r = (r * BASE + a[i]) % x;
    return r;
}

istream& operator>>(istream& cin, bigint& a) {
    string s;
    cin >> s;
    a.clear();
    a.resize(s.size() / 4 + 1);
    for (int i = 0; i < s.size(); ++i) {
        int x = (s.size() - 1 - i) / 4;  // <- log10(BASE)=4
        a[x] = a[x] * 10 + (s[i] - '0');
    }
    return fix(a), cin;
}

ostream& operator<<(ostream& os, const bigint& a) {
    os << a.back();
    for (int i = (int)a.size() - 2; i >= 0; i--)
        os << setw(LEN) << setfill('0') << a[i];
    return os;
}