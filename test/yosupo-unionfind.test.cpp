#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include "../memo/macro.hpp"
#include "../data_structure/unionfind.cpp"

int main() {
    ll n, q;
    cin >> n >> q;
    UnionFind uf(n);
    REP(i, q) {
        ll t, u, v;
        cin >> t >> u >> v;
        u--, v--;
        if(t == 0) uf.unite(u, v);
        else cout << uf.same(u, v) << "\n";
    }
    cout << flush;

    return 0;
}