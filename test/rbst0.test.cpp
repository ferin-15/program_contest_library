#define PROBLEM https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_I
#include "../data_structure/rbst.cpp"

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int n, q;
    cin >> n >> q;

    auto f = [](ll l, ll r) { return l+r; };
    auto g = [](ll l, ll r) { return r==INT_MAX?l:r; };
    auto p = [](ll l, int r) { return l*r; };
    RBST<ll,ll> tree(f, g, g, p, 0, INT_MAX);

    RBST<ll,ll>::node* root = nullptr;
    for(int i = 0; i < n; i++) tree.insert(root, i, 0);
    while(q--) {
        int c, s, t;
        cin >> c >> s >> t;
        if(c == 0) {
            int x;
            cin >> x;
            tree.update(root, s, t+1, x);
        } else {
            cout << tree.query(root, s, t+1) << endl;
        }
    }

    return 0;
}