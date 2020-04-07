#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1595"
#include "../memo/macro.hpp"
#include "../DP/rerooting.cpp"

int main(void) {
    ll n;
    cin >> n;

    auto merge = [&](ll l, ll r) { return max(l, r); };
    auto add = [&](ll v, ll w) { return v+w; };
    rerooting<ll, ll> graph(n, merge, add, 0);

    REP(i, n-1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        graph.add_edge(u, v, 1);
    }
    auto ans = graph.build();

    REP(i, n) cout << 2*(n-1) - ans[i] << "\n";

    return 0;
}