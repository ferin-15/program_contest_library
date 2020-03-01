#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2667"
#include "../memo/macro.hpp"
#include "../graph/hld.cpp"
#include "../data_structure/lazysegtree.cpp"

signed main(void) {
    ll n, q;
    cin >> n >> q;
    HLDecomposition hld(n);
    for (ll i = 0; i < n - 1; ++i) {
        ll a, b;
        cin >> a >> b;
        hld.add_edge(a, b);
    }
    hld.build();

    lazysegtree<linear_exp> seg(n);
    seg.build(vector<node>(n, node(0)));

    for (ll i = 0; i < q; ++i) {
        ll type, u, v;
        cin >> type >> u >> v;
        if (type == 0) {
            ll ans = 0;
            auto f = [&](ll a, ll b) {
                if (a > b) swap(a, b);
                ans += seg.query(a, b+1).sum;
            };
            hld.for_each_edge(u, v, f);
            cout << ans << endl;
        }
        else {
            seg.update(hld.vid[u]+1, hld.vid[u] + hld.sz[u], PII(1, v));
        }
    }

    return 0;
}