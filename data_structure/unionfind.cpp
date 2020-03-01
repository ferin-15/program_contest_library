struct UnionFind {
    vector<ll> par, s;
    UnionFind(ll n) : par(n), s(n, 1) { iota(ALL(par), 0); }
    ll find(ll x) {
        if(par[x] == x) return x;
        return par[x] = find(par[x]);
    }
    void unite(ll x, ll y) {
        x = find(x), y = find(y);
        if(x == y) return;
        if(s[x] < s[y]) par[x] = y, s[y] += s[x];
        else par[y] = x, s[x] += s[y];
    }
    bool same(int x, int y) { return find(x) == find(y); }
    ll size(int x) { return s[find(x)]; }
};