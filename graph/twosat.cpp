// BEGIN CUT
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
// END CUT