#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_G"
#include "../memo/macro.hpp"
#include "../data_structure/rbst.cpp"

signed main(void) {
    int n, q;
    cin >> n >> q;

    struct add_sum {
        using T = PII;
        using E = ll;
        static T dt() { return PII(0, 0); }
        static constexpr E de() { return 0; }
        static T f(const T &l, const T &self, const T &r) {
            return PII(self.first, l.second + self.first + r.second);
        }
        static T g(const T &a, const E &b, const int &sz) {
            return PII(a.first + b, a.second + b * sz);
        }
        static E h(const E &a, const E &b) {
            return a + b;
        }
    };
    RBST<add_sum> tree;

    RBST<add_sum>::node* root = nullptr;
    for(int i = 0; i < n; i++) tree.insert(root, i, PII(0, 0));
    while(q--) {
        int c, s, t;
        cin >> c >> s >> t;
        s--, t--;
        if(c == 0) {
            int x;
            cin >> x;
            tree.update(root, s, t + 1, x);
        } else {
            cout << tree.query(root, s, t + 1).second << endl;
        }
    }

    return 0;
}