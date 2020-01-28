#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A"
#include "../memo/macro.hpp"
#include "../data_structure/rbst.cpp"

signed main(void) {
    int n, q;
    cin >> n >> q;

    struct update_min {
        using T = PII;
        using E = ll;
        static T dt() { return PII(INT_MAX, INT_MAX); }
        static constexpr E de() { return INT_MAX; }
        static T f(const T &l, const T &self, const T &r) {
            return PII(self.first, min({l.second, self.first, r.second}));
        }
        static T g(const T &a, const E &b, const int &sz) {
            return b == de() ? a : PII(b, b);
        }
        static E h(const E &a, const E &b) {
            return b == de() ? a : b;
        }
    };
    RBST<update_min> tree;

    RBST<update_min>::node* root = nullptr;
    for(int i = 0; i < n; i++) tree.insert(root, i, PII(INT_MAX, INT_MAX));
    while(q--) {
        int c, x, y;
        cin >> c >> x >> y;
        if(c == 0) {
            tree.update(root, x, y);
        } else {
            cout << tree.query(root, x, y+1).second << endl;
        }
    }

    return 0;
}