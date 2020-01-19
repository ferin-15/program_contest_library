#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_D"
#include "../memo/macro.hpp"
#include "../graph/HLDecomposition.cpp"
#include "../data_structure/lazysegtree.cpp"

signed main(void) {
    ll n;
    cin >> n;
    HLDecomposition hld(n);
    vector<ll> p(n, -1);
    REP(i, n) {
        ll k;
        cin >> k;
        REP(j, k) {
            ll c;
            cin >> c;
            hld.add_edge(i, c);
            p[c] = i;
        }
    }
    hld.build();

    lazysegtree<linear_exp> seg(n);
    vector<node> init(n);
    REP(i, n) init[i] = node(0);
    seg.build(init);

    ll q;
    cin >> q;
    while(q--) {
        ll type;
        cin >> type;
        if(type == 0) {
            ll v, w;
            cin >> v >> w;
            hld.for_each_edge(v, p[v], [&](ll a, ll b){
                seg.update(a, b+1, PII(1, w));
            });
        } else {
            ll v;
            cin >> v;
            ll ans = 0;
            hld.for_each_edge(v, 0, [&](ll a, ll b){
                ans += seg.query(a, b+1).sum;
            });
            cout << ans << endl;
        }
    }

    return 0;
}