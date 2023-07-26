#include <bits/stdc++.h>

int getc() {
    static char buf[1 << 16];
    static size_t bufsize = 1 << 16, bufat = 0, bufend = 0;
    if (bufat == bufend) {
        bufend = fread(buf, sizeof(char), bufsize, stdin);
        bufat = 0;
    }
    return bufend ? buf[bufat++] : EOF;
}
template <typename _t>
_t getd() {
    int sgn = 1, c;
    while (!isdigit(c = getc()) && c != '-')
        ;
    if (c == '-') sgn = -1, c = getc();

    _t res = 0;
    for (; isdigit(c); c = getc())
        res *= 10, res += c - '0';
    return res * sgn;
}
inline void scan() {}
template <typename _t, typename... _ts>
void scan(_t& n, _ts&... args) {
    n = getd<_t>();
    scan(args...);
}
