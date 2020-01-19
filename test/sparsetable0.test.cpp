#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D&lang=ja"
#include "../memo/macro.hpp"
#include "../data_structure/sparse_table.cpp"

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n, l;
    cin >> n >> l;
    vector<ll> a(n);
    REP(i, n) cin >> a[i];

    sparseTable<minnimum> st(n);
    st.init(a);
    FOR(i, l-1, n) cout << st.query(i-l+1, i) << (i==n-1?'\n':' ');

    return 0;
}