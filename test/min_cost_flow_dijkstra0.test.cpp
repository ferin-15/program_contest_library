#define PROBLEM https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_B
#include "../graph/min_cost_flow_dijkstra.cpp"

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n, m, f;
    cin >> n >> m >> f;
    primal_dual mcf(n);
    REP(i, m) {
        ll u, v, c, d;
        cin >> u >> v >> c >> d;
        mcf.add_edge(u, v, c, d);
    }
    cout << mcf.min_cost_flow(0, n-1, f) << endl;

    return 0;
}