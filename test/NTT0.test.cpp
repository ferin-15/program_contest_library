#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2996"
#include "../memo/macro.hpp"
#include "../math/modint.cpp"
#include "../math/NTT.cpp"

using mint1 = modint<65537>;
signed main(void) {
    ll t;
    cin >> t;
    while(t--) {
        ll n;
        mint1 k;
        cin >> n >> k;
        vector<mint1> a(n);
        REP(i, n) cin >> a[n-1-i];
        // a[i] を i! で割る
        mint1 inv = 1;
        FOR(i, 1, n) {
            inv *= mint1(i).inv();
            a[i] *= inv;
        }
        // b[i] = (-k)^i / i!
        vector<mint1> b(n);
        b[0] = 1;
        FOR(i, 1, n) b[i] = b[i-1] * (65537-k) * mint1(i).inv();
        // a と b の畳み込みに i! を掛ける
        auto conv = any_mod_convolution<mint1>(a, b);
        mint1 frac = 1;
        vector<mint1> ret(n);
        REP(i, n) {
            if(i > 0) frac *= i;
            ret[i] = conv[i] * frac;
            cout << ret[i] << (i==n-1?'\n':' ');
        }
        cout << flush;
    }

    return 0;
}