// BEGIN CUT
struct partial_persistent_uf {
    int now;
    vector<int> time, par, rank;
    vector<vector<PII>> sz;
    partial_persistent_uf(int n) : now(0), time(n, 1<<30), par(n, 1), sz(n, vector<PII>({{0,1}})) {}
    // t(1-indexed) 回目までuniteしたときのxの根
    int find(int x, int t) {
        if(time[x] > t) return x;
        return find(par[x], t);
    }
    int unite(int x, int y) {
        ++now;
        x = find(x, now), y = find(y, now);
        if(x == y) return now;
        if(par[x] < par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        time[y] = now;
        sz[x].emplace_back(now, par[x]);
        return now;
    }
    bool same(int x, int y, int t) { 
        return find(x, t) == find(y, t);
    }
    int size(int x, int t) { 
        x = find(x, t);
        return prev(upper_bound(ALL(sz[x]), PII(t, INF)))->second; 
    }
};
// END CUT