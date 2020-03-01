#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../memo/macro.hpp"
#include "../data_structure/segtree.cpp"

int main(void) {
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    REP(i, n) cin >> a[i];

    segtree<min_monoid<ll>> seg(n);
    seg.build(a);

    REP(i, q) {
        ll l, r;
        cin >> l >> r;
        cout << seg.query(l, r) << "\n";
    }
    cout << flush;

    return 0;
}