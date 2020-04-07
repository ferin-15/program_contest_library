#define PROBLEM "https://yukicoder.me/problems/no/901"
#include "../memo/macro.hpp"
#include "../data_structure/sparse_table.cpp"
#include "../graph/LCA_sparsetable.cpp"
#include "../graph/auxiliary_tree_based_lca.cpp"

signed main() {
    ll n;
    cin >> n;
    vector<vector<PII>> g(n);
    auxiliaryTreeBasedLCA tree(n);
    REP(i, n-1) {
        ll a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
        tree.add_edge(a, b);
    }
    tree.build();
    
    vector<ll> dist(n);
    function<void(ll,ll)> dfs = [&](ll v, ll p) {
        for(auto to: g[v]) {
            if(to.first == p) continue;
            dist[to.first] = dist[v] + to.second;
            dfs(to.first, v);
        }
    };
    dfs(0, -1);

    ll q;
    cin >> q;
    while(q--) {
        ll k;
        cin >> k;
        vector<ll> v(k);
        REP(i, k) cin >> v[i];

        auto edges = tree.makeTree(v);

        ll ret = 0;
        for(auto e: edges) {
            ret += dist[e.first] + dist[e.second] - 2*dist[tree.lca.get(e.first, e.second)];
        }
        cout << ret << endl;
    }

    return 0;
}