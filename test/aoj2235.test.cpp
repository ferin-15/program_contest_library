#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2235"
#include "../memo/macro.hpp"
#include "../data_structure/dynamic_connectivity.cpp";
#include "../data_structure/unionfindundo.cpp"

int main(void) {
    ll n, q;
    cin >> n >> q;
    dynamicConnectivity dc(n, q);
    vector<ll> t(q), u(q), v(q);
    REP(i, q) {
        cin >> t[i] >> u[i] >> v[i];
        if(t[i] == 1) dc.insert(i, {u[i], v[i]});
        else if(t[i] == 2) dc.erase(i, {u[i], v[i]});
    }
    dc.build();

    UnionFindUndo uf(n);
    auto add = [&](edge e) {
        uf.unite(e.first, e.second);
    };
    auto undo = [&] {
        uf.undo();
    };
    auto f = [&](ll x) {
        if(x < q && t[x] == 3) {
            cout << (uf.same(u[x], v[x]) ? "YES" : "NO") << endl;
        }
    };
    dc.execute(f, add, undo);

    return 0;
}