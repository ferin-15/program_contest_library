#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A"
#include "../memo/macro.hpp"
#include "../data_structure/rbst.cpp"

signed main(void) {
    int n, q;
    cin >> n >> q;

    auto f = [](ll l, ll r) { return min(l, r); };
    RBST<ll> tree(f, INT_MAX);

    RBST<ll,ll>::node* root = nullptr;
    for(int i = 0; i < n; i++) tree.insert(root, i, INT_MAX);
    while(q--) {
        int c, x, y;
        cin >> c >> x >> y;
        if(c == 0) {
            tree.set_element(root, x, y);
        } else {
            cout << tree.query(root, x, y+1) << endl;
        }
    }

    return 0;
}