#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C"
#include "../graph/LCA_sparsetable.cpp"

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n;
    cin >> n;
    LCA graph(n);
    REP(i, n) {
        ll k;
        cin >> k;
        REP(j, k) {
            ll c;
            cin >> c;
            graph.add_edge(i, c);
        }
    }
    graph.build();

    ll q;
    cin >> q;
    while(q--) {
        ll u, v;
        cin >> u >> v;
        cout << graph.get(u, v) << endl;
    }

    return 0;
}