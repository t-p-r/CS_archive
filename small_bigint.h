#include <bits/stdc++.h>
#define allof(a) a.begin(), a.end()
#define int long long
#define F(i, a, b) for (int i = a; i <= b; i++)
#define D(i, a, b) for (int i = a; i >= b; i--)
#define mn 10011

const int base = 1e9, base_digits = 9;
class bigint : public vector<int> {
   public:
    bigint() {}
    bigint(const string& s) {
        for (int i = s.size(); i > 0; i -= 9) {
            if (i < 9)
                this->emplace_back(atoi(s.substr(0, i).c_str()));
            else
                this->emplace_back(atoi(s.substr(i - 9, 9).c_str()));
        }
    }
    bigint(int s) {
        string v;
        while (s)
            v += (s % 10 + 48), s /= 10;
        reverse(allof(v));
        *this = v;
    }
    friend istream& operator>>(istream& is, bigint& v) {
        string s;
        is >> s;
        v = s;
        return is;
    }
    friend ostream& operator<<(ostream& os, const bigint& v) {
        os << (v.empty() ? 0 : v.back());
        D(i, (signed)v.size() - 2, 0)
            os << setw(base_digits) << setfill('0') << v[i];
        return os;
    }
    friend bigint operator+(const bigint& a, const bigint& b) {
        bigint c = a;
        int carry = 0;
        for (size_t i = 0; i < max(c.size(), b.size()) || carry; i++) {
            if (i == c.size()) c.emplace_back(0);
            c[i] += carry + (i < b.size() ? b[i] : 0);
            carry = c[i] >= base;
            if (carry) c[i] -= base;
        }
        return c;
    }
};
