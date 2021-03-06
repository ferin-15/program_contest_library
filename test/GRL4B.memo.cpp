#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/4/GRL_4_B"
#include "../memo/macro.hpp"
#include "../graph/topological.cpp"

// スペシャルジャッジだからだめ
signed main(void) {
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> g(n);
    REP(i, m) {
        ll u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    auto ans = tsort(g);
    for(auto p: ans) cout << p.first << endl;

    return 0;
}