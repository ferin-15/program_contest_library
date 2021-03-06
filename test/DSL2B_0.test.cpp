#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=jp"
#include "../memo/macro.hpp"
#include "../data_structure/BIT.cpp"

signed main(void) {
    ll n, q;
    cin >> n >> q;
    BIT bit(100010);
    while(q--) {
        ll t, x, y;
        cin >> t >> x >> y;
        if(t == 0) {
            bit.update(x, y);
        } else {
            cout << bit.query(y) - bit.query(x-1) << endl;
        }
    }

    return 0;
}