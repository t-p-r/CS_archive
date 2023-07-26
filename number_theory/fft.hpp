#include <bits/stdc++.h>
using namespace std;
using cd = complex<double>;

const double PI = acos(-1);

void simple_fft(vector<cd>& a, bool inv) {
    int n = a.size();
    if (n == 1) return;

    // assert(__builtin_popcount(n)==1);

    vector<cd> a0(n / 2), a1(n / 2);

    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }

    simple_fft(a0, inv);
    simple_fft(a1, inv);

    double angle = 2 * PI / n * (inv ? -1 : 1);

    cd w(1), wn(cos(angle), sin(angle));

    for (int i = 0; i < 2 * n; i += 2) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        if (inv) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

void fast_fft(vector<cd>& a, bool inv) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j) swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double angle = 2 * PI / len * (inv ? -1 : 1);
        cd wlen(cos(angle), sin(angle));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if (inv)
        for (cd& x : a)
            x /= n;
}

vector<int> mul(const vector<int>& a, const vector<int>& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());

    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;

    fa.resize(n);
    fast_fft(fa, false);
    fb.resize(n);
    fast_fft(fb, false);

    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];

    fast_fft(fa, true);

    vector<int> res(n);

    for (int i = 0; i < n; i++)
        res[i] = round(fa[i].real());
    return res;
}