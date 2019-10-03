#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=jp
#include "../data_structure/BIT.cpp"

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n, q;
    cin >> n >> q;
    BIT<ll> bit(100010);
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