#define PROBLEM "https://yukicoder.me/problems/no/899"
#include "../memo/macro.hpp"
#include "../graph/bfs_euler_tour.cpp"
#include "../data_structure/lazysegtree.cpp"

struct node {
    ll sum, max, min, len;
    node() : sum(0), max(-INF), min(INF), len(0) {}
    node(ll a, ll b, ll c, ll d) : sum(a), max(b), min(c), len(d) {}
};
struct linear_exp {
    using T = node;
    using E = PII;
    static T dt() { return node(); }
    static constexpr E de() { return PII(1, 0); }
    static T f(const T &a, const T &b) {
        node ret;
        ret.sum = a.sum + b.sum;
        ret.min = min(a.min, b.min);
        ret.max = max(a.max, b.max);
        ret.len = a.len + b.len;
        return ret;
    }
    static T g(const T &a, const E &b) {
        node ret;
        ret.sum = b.first*a.sum+b.second*a.len;
        ret.min = b.first*a.min+b.second;
        ret.max = b.first*a.max+b.second;
        ret.len = a.len;
        return ret;
    }
    static E h(const E &a, const E &b) {
        return PII(b.first*a.first, b.first*a.second+b.second);
    }
};

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
    seg.build(vector<node>(n+2, node(0, 0, 0, 1)));
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