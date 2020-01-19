#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"
#include "../memo/macro.hpp"
#include "../data_structure/segtree.cpp"

signed main(void) {
    int n, q;
    cin >> n >> q;

    segtree<sum_monoid<ll>> seg(n);
    while(q--) {
        int c, x, y;
        cin >> c >> x >> y;
        if(c == 0) {
            x--;
            seg.update(x, seg.query(x, x+1) + y);
        } else {
            x--, y--;
            cout << seg.query(x, y+1) << endl;
        }
    }

    return 0;
}