#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_1_A"
#include "../memo/macro.hpp"
#include "../data_structure/unionfind.cpp"

signed main(void) {
    ll n, q;
    cin >> n >> q;
    UnionFind uf(n);
    while(q--) {
        ll type;
        cin >> type;
        if(type == 0) {
            ll x, y;
            cin >> x >> y;
            uf.unite(x, y);
        } else {
            ll x, y;
            cin >> x >> y;
            cout << uf.same(x, y) << endl;
        }
    }

    return 0;
}