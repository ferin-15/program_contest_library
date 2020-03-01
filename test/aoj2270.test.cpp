#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2270"
#include "../memo/macro.hpp"
#include "../data_structure/BIT.cpp"
#include "../data_structure/Mo_tree_vertex.cpp"

signed main(void) {
    ll n, q;
    cin >> n >> q;
    vector<ll> x(n);
    REP(i, n) cin >> x[i];
    
    vector<ll> vs(x);
    sort(ALL(vs));
    vs.erase(unique(ALL(vs)), vs.end());
    REP(i, n) x[i] = lower_bound(ALL(vs), x[i]) - vs.begin();

    BIT<ll> bit(vs.size());
    auto add = [&](ll idx) { bit.update(x[idx], 1); };
    auto del = [&](ll idx) { bit.update(x[idx], -1); };
    Mo_Tree_Vertex mo(n, add, del);

    REP(i, n-1) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        mo.add_edge(a, b);
    }
    mo.prepare();

    vector<ll> k(q);
    REP(i, q) {
        ll a, b;
        cin >> a >> b >> k[i];
        a--, b--;
        mo.insert(a, b);
    }
    mo.build();

    vector<ll> ans(q);
    REP(i, q) {
        ll idx = mo.process();
        ans[idx] = vs[bit.lower_bound(k[idx])];
    }
    REP(i, q) cout << ans[i] << "\n";
    cout << flush;

    return 0;
}