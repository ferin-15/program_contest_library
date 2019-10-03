#define PROBLEM https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_C
#include "../graph/SCC.cpp"

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n, m;
    cin >> n >> m;
    SCC scc(n);
    REP(i, m) {
        ll u, v;
        cin >> u >> v;
        scc.add_edge(u, v);
    }
    scc.scc();
    ll q;
    cin >> q;
    REP(i, q) {
        ll u, v;
        cin >> u >> v;
        if(scc.cmp[u] == scc.cmp[v]) cout << 1 << endl;
        else cout << 0 << endl;
    }

    return 0;
}