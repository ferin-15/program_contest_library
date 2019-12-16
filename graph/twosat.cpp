#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PII = pair<ll, ll>;
#define FOR(i, a, n) for (ll i = (ll)a; i < (ll)n; ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(x) x.begin(), x.end()
template<typename T> void chmin(T &a, const T &b) { a = min(a, b); }
template<typename T> void chmax(T &a, const T &b) { a = max(a, b); }
struct FastIO {FastIO() { cin.tie(0); ios::sync_with_stdio(0); }}fastiofastio;
#ifdef DEBUG_ 
#include "../program_contest_library/memo/dump.hpp"
#else
#define dump(...)
#endif
const ll INF = 1LL<<60;

struct twoSAT {
    ll n;
    SCC graph;
    vector<bool> ans;
    twoSAT(ll n) : n(n), graph(n*2), ans(n) {}
    // not なら false
    void add(pair<ll,bool> a0, pair<ll,bool> b0) {
        ll a = a0.first, ar = (a0.first+n)%(2*n);
        ll b = b0.first, br = (b0.first+n)%(2*n);
        if(!a0.second) swap(a, ar);
        if(!b0.second) swap(b, br);
        graph.add_edge(ar, b);
        graph.add_edge(br, a);
    }
    bool solve() {
        graph.scc();
        REP(i, n) if(graph.cmp[i] == graph.cmp[n+i]) return false;
        REP(i, n) ans[i] = graph.cmp[i] > graph.cmp[n+i];
        return true;
    }
};
