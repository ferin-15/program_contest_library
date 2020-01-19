#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2996"
#include "../memo/macro.hpp"
#include "../math/FFT.cpp"
#include "../math/modint.cpp"
using mint1 = modint<65537>;

signed main(void) {
    ll t;
    cin >> t;
    while(t--) {
        ll n;
        mint1 k;
        cin >> n >> k;
        vector<mint1> a0(n);
        REP(i, n) cin >> a0[n-1-i];

        // a[i] を i! で割る
        mint1 inv = 1;
        FOR(i, 1, n) {
            inv *= mint1(i).inv();
            a0[i] *= inv;
        }
        // b[i] = (-k)^i / i!
        vector<mint1> b0(n);
        b0[0] = 1;
        FOR(i, 1, n) b0[i] = b0[i-1] * (65537-k) * mint1(i).inv();

        // a と b の畳み込みに i! を掛ける
        vector<int> a(n), b(n);
        REP(i, n) a[i] = a0[i].x, b[i] = b0[i].x;
        auto conv = fft::multiply_mod<65537>(a, b);

        mint1 frac = 1;
        REP(i, n) {
            if(i > 0) frac *= i;
            cout << conv[i] * frac << (i==n-1?'\n':' ');
        }
        cout << flush;
    }

    return 0;
}