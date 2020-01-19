#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_A"
#include "../graph/dinic.cpp"

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll v, e;
    cin >> v >> e;
    dinic<ll> flow(v);
    REP(i, e) {
        ll u, v, c;
        cin >> u >> v >> c;
        flow.add_edge(u, v, c);
    }

    cout << flow.maxflow(0, v-1) << endl;

    return 0;
}