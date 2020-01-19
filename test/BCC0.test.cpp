#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_B"
#include "../graph/BCC.cpp"

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n, m;
    cin >> n >> m;
    twoEdgeComponent graph(n);
    REP(i, m) {
        ll a, b;
        cin >> a >> b;
        graph.add_edge(a, b);
    }
    graph.build();

    for(auto &e: graph.bridge) if(e.first > e.second) swap(e.first, e.second);
    sort(ALL(graph.bridge));
    for(auto e: graph.bridge) cout << e.first << " " << e.second << endl;

    return 0;
}