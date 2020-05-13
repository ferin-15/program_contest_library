using int128 = __int128_t;
using uint128 = __uint128_t;
ostream &operator<<(ostream &os, int128 value) {
    ostream::sentry s(os);
    if (s) {
        uint128 tmp = value < 0 ? -value : value;
        char buffer[128];
        char *d = end(buffer);
        do {
            --d;
            *d = "0123456789"[tmp % 10];
            tmp /= 10;
        } while (tmp != 0);
        if (value < 0) --d, *d = '-';
        int len = end(buffer) - d;
        if (os.rdbuf()->sputn(d, len) != len) {
            os.setstate(ios_base::badbit);
        }
    }
    return os;
}
istream &operator>>(istream &is, int128 &val) {
    string s; is >> s;
    val = 0;
    REP(i, s.size()) if ('0' <= s[i] && s[i] <= '9') {
        val = 10 * val + s[i] - '0';
    }
    return is;
}