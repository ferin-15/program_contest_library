#include "../memo/macro.hpp"
#include "../math/modint.cpp"
using mint = modint<998244353>;
#include "../math/combination.cpp"
#include "../math/sum_of_powers.cpp"

signed main(void) {
    ll n, s0;
    cin >> n >> s0;
    mint s = s0;

    mint ans = s * (s+1).pow(n-1) / 2;
    if(s0%2 == 0) {
        ans += mint(2).pow(n) * sum_of_powers(s0/2+1, n-1);
        ans -= sum_of_powers(s0+1, n-1);
    } else {
        ans -= mint(2).pow(n) * sum_of_powers(s0/2+1, n-1);
        ans += sum_of_powers(s0+1, n-1);
    }
    cout << ans << endl;

    return 0;
}