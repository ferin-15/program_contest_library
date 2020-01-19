#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2996"
#include "../memo/macro.hpp"
#include "../math/modint.cpp"
#include "../math/NTT.cpp"

using mint = modint<65537>;
signed main(void) {
    ll t;
    cin >> t;
    while(t--) {
        ll n;
        mint k;
        cin >> n >> k;
        vector<mint> a(n);
        REP(i, n) cin >> a[n-1-i];
        // a[i] を i! で割る
        mint inv = 1;
        FOR(i, 1, n) {
            inv *= mint(i).inv();
            a[i] *= inv;
        }
        // b[i] = (-k)^i / i!
        vector<mint> b(n);
        b[0] = 1;
        FOR(i, 1, n) b[i] = b[i-1] * (65537-k) * mint(i).inv();
        // a と b の畳み込みに i! を掛ける
        auto conv = any_mod_convolution<mint>(a, b);
        mint frac = 1;
        vector<mint> ret(n);
        REP(i, n) {
            if(i > 0) frac *= i;
            ret[i] = conv[i] * frac;
            cout << ret[i] << (i==n-1?'\n':' ');
        }
        cout << flush;
    }

    return 0;
}