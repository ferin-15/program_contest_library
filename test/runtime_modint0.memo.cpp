#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"
#include "../memo/macro.hpp"
#include "../math/runtime_modint.cpp"

signed main(void) {
    ll t;
    cin >> t;
    while(t--) {
        ll a;
        cin >> a >> MOD;
        cout << sqrt(mint(a)) << endl;
    }

    return 0;
}