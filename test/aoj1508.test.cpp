#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1508"
#include "../memo/macro.hpp"
#include "../data_structure/rbst.cpp"

int main() {
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

    REP(i, n) {
        int a;
        cin >> a;
        tree.insert(root, i, PII(a, a));
    }

    REP(i, q) {
        int t, l, r; cin >> t >> l >> r;
        if(t == 0) {
            // [0,l)[l,r)[r,r+1)[r+1,n)
            auto p1 = tree.split(root, r+1);
            auto p2 = tree.split(p1.first, r);
            auto p3 = tree.split(p2.first, l);
            root = tree.merge(tree.merge(tree.merge(p3.first, p2.second), p3.second), p1.second); 
        } else if(t == 1) {
            cout << tree.query(root, l, r+1).second << endl;
        } else if(t == 2) {
            tree.update(root, l, r);
        }
    }

    return 0;
}