#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_I"
#include "../memo/macro.hpp"
#include "../data_structure/lazysegtree.cpp"

signed main(void) {
    int n, q;
    cin >> n >> q;

    lazysegtree<linear_exp> seg(n);
    seg.build(vector<node>(n, node(0)));
    while(q--) {
        int c, s, t;
        cin >> c >> s >> t;
        if(c == 0) {
            int x;
            cin >> x;
            seg.update(s, t+1, PII(0, x));
        } else {
            cout << seg.query(s, t+1).sum << endl;
        }
    }

    return 0;
}
