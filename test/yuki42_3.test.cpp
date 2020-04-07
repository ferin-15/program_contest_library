#define PROBLEM "https://yukicoder.me/problems/no/42"
#include "../memo/macro.hpp"
#include "../math/modint.cpp"
using mint = modint<1000000009>;
#include "../math/lagrange_interpolation.cpp"

signed main(void) {
    vector<ll> c({1, 5, 10, 50, 100, 500});
    vector<mint> dp(3010, 1);
    FOR(i, 1, 6) FOR(j, c[i], 3010) dp[j] += dp[j-c[i]];

    ll t;
    cin >> t;
    while(t--) {
        ll M;
        cin >> M;

        if(M < 3010) {
            cout << dp[M] << endl;
            continue;
        }

        mint m = M/500;
        ll q = M % 500;
        vector<mint> x(6), y(6);
        REP(i, 6) {
            x[i] = i;
            y[i] = dp[i*500+q];
        }
        cout << lagrange_interpolation_arithmetic(mint(0), mint(1), y, m) << endl;
    }

    return 0;
}