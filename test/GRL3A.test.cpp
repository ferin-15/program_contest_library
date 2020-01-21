#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A&lang=jp"
#include "../memo/macro.hpp"
#include "../graph/articulation.cpp"

int main() {
    ll n, m;
    cin >> n >> m;
    articulation graph(n);
    REP(i, m) {
        ll s, t;
        cin >> s >> t;
        graph.add_edge(s, t);
    }
    auto ret = graph.build();
    sort(ALL(ret));
    for(auto i: ret) cout << i << "\n";
    cout << flush;
}