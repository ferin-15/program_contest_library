#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"
#include "../memo/macro.hpp"
#include "../math/runtime_modint.cpp"

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll t;
    cin >> t;
    while(t--) {
        ll a;
        cin >> a >> MOD;
        cout << sqrt(mint(a)) << endl;
    }

    return 0;
}