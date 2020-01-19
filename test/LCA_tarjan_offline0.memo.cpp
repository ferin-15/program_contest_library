#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C"
#include "../memo/macro.hpp"
#include "../graph/LCA_tarjan_offline.cpp"

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n;
    cin >> n;
    vector<PII> edges;
    REP(i, n) {
        ll k;
        cin >> k;
        REP(j, k) {
            ll c;
            cin >> c;
            edges.emplace_back(i, c);
        }
    }
    ll q;
    cin >> q;

    tarjan_offline_lca graph(n, q);
    for(auto e: edges) graph.add_edge(e.first, e.second);
    REP(i, q) {
        ll u, v;
        cin >> u >> v;
        graph.add_query(u, v, i);
    }
    auto ret = graph.build();
    for(auto i: ret) cout << i << endl;

    return 0;
}