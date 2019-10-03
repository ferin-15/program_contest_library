#define PROBLEM https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A
#include "../data_structure/segtree.cpp"

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int n, q;
    cin >> n >> q;

    segtree<min_monoid<ll>> seg(n);
    while(q--) {
        int c, x, y;
        cin >> c >> x >> y;
        if(c == 0) {
            seg.update(x, y);
        } else {
            cout << seg.query(x, y+1) << endl;
        }
    }

    return 0;
}