#define PROBLEM https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B
#include "../data_structure/rbst.cpp"

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int n, q;
    cin >> n >> q;

    auto f = [](ll l, ll r) { return l+r; };
    RBST<ll> tree(f, 0);

    RBST<ll,ll>::node* root = nullptr;
    for(int i = 0; i < n; i++) tree.insert(root, i, 0);
    while(q--) {
        int c, x, y;
        cin >> c >> x >> y;
        if(c == 0) {
            x--;
            tree.set_element(root, x, tree.get(root, x) + y);
        } else {
            x--, y--;
            cout << tree.query(root, x, y+1) << endl;
        }
    }

    return 0;
}