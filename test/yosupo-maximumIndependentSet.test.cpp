#define PROBLEM "https://judge.yosupo.jp/problem/maximum_independent_set"
#include "../memo/macro.hpp"
#include "../graph/max_independent_set.cpp"

int main() {
    ll n, m;
    cin >> n >> m;
    maxIndependentSet graph(n);
    REP(i, m) {
        ll u, v;
        cin >> u >> v;
        graph.add_edge(u, v);
    }
    auto ans = graph.get();
    cout << ans.size() << "\n";
    REP(i, ans.size()) cout << ans[i] << (i+1==ans.size() ? "\n" : " ");
    cout << flush;
}