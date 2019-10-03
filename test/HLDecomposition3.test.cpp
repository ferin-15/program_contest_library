#define PROBLEM https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C
#include "../graph/HLDecomposition.cpp"

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n;
    cin >> n;
    HLDecomposition hld(n);
    REP(i, n) {
        ll k;
        cin >> k;
        REP(j, k) {
            ll c;
            cin >> c;
            hld.add_edge(i, c);
        }
    }
    hld.build();

    ll q;
    cin >> q;
    while(q--) {
        ll u, v;
        cin >> u >> v;
        cout << hld.lca(u, v) << endl;
    }

    return 0;
}