#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2987"
#include "../memo/macro.hpp"
#include "../math/modint.cpp"
using mint = modint<998244353>;
#include "../math/lagrange_interpolation.cpp"

signed main(void) {
    ll n, s0;
    cin >> n >> s0;
    mint s = s0;

    mint ans = s * (s+1).pow(n-1) / 2;
    vector<mint> xs(n), ys(n);
    REP(i, n) {
        ll x = 2*i + s0%2;
        mint y = 0;
        bool turn = true;
        REP(j, x) {
            if(turn) y += mint(x-j).pow(n-1);
            else y -= mint(x-j).pow(n-1);
            turn = !turn;
        }
        xs[i] = x, ys[i] = y;
    }
    ans += lagrange_interpolation(xs, ys, s);
    cout << ans << endl;

    return 0;
}