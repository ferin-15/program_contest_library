#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
#include "../memo/macro.hpp"
#include "../data_structure/linkcuttree_subtree.cpp"

int main(void) {
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    REP(i, n) cin >> a[i];
    
    struct SUM {
        ll ret, laz, all;
        SUM() : ret(0), laz(0), all(0) {}
        void toggle() {}
        void merge(ll key, const SUM &left, const SUM &right) {
            ret = laz + key + right.all;
            all = ret + left.all;
        }
        void add(const SUM &ch) { laz += ch.all; }
        void erase(const SUM &ch) { laz -= ch.all; }
    };
    LinkCutTreeForSubTree<ll,SUM> lct(a);

    REP(i, n-1) {
        ll p;
        cin >> p;
        lct.link(i+1, p);
    }
    while(q--) {
        ll t;
        cin >> t;
        if(t == 0) {
            ll u, x;
            cin >> u >> x;
            auto g = [](ll p, ll q) { return p+q; };
            lct.update(u, x, g);
        } else {
            ll u;
            cin >> u;
            cout << lct.query(u).ret << endl;
        }
    }

    return 0;
}