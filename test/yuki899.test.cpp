#define PROBLEM "https://yukicoder.me/problems/no/899"
#include "../memo/macro.hpp"
#include "../graph/bfs_euler_tour.cpp"
#include "../data_structure/lazysegtree.cpp"

int main() {
    ll n;
    cin >> n;
    bfsEulerTour tour(n, 2);
    REP(i, n-1) {
        ll u, v;
        cin >> u >> v;
        tour.add_edge(u, v);
    }
    vector<ll> a(n);
    REP(i, n) cin >> a[i];
    tour.build();

    lazysegtree<linear_exp> seg(n+2);
    seg.build(vector<node>(n+2, node(0)));
    REP(i, n) {
        tour.for_each(i, 0, [&](ll u, ll v){
            seg.update(u, v, PII(0, a[i]));
        });
    }

    ll q;
    cin >> q;
    while(q--) {
        ll x;
        cin >> x;

        ll ret = 0;
        tour.for_each(x, 2, [&](ll u, ll v){
            ret += seg.query(u, v).sum;
            seg.update(u, v, PII(0, 0));
        });
        tour.for_each(x, 0, [&](ll u, ll v){
            seg.update(u, v, PII(1, ret));
        });
        cout << ret << endl;
    }
}