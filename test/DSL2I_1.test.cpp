#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_I"
#include "../memo/macro.hpp"
#include "../data_structure/rbst.cpp"

signed main(void) {
    int n, q;
    cin >> n >> q;

    struct update_sum {
        using T = ll;
        using E = ll;
        static T dt() { return 0; }
        static constexpr E de() { return INT_MAX; }
        static T f(const T &a, const T &b) {
            return a + b;
        }
        static T g(const T &a, const E &b) {
            return b == de() ? a : b;
        }
        static E h(const E &a, const E &b) {
            return b == de() ? a : b;
        }
        static E p(const E &a, const int &b) {
            return a*b;
        } 
    };
    RBST<update_sum> tree;

    RBST<update_sum>::node* root = nullptr;
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