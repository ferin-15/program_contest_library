// BEGIN CUT
struct UnionFind {
    vector<int> par, s;
    UnionFind(int n=2e5) { init(n); }
    void init(int n) {
        s.assign(n, 1); par.resize(n);
        iota(par.begin(), par.end(), 0);
    }
    int find(int x) {
        if(par[x] == x) return x;
        return par[x] = find(par[x]);
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y) return;
        if(s[x] < s[y]) par[x] = y, s[y] = s[x] + s[y];
        else par[y] = x, s[x] = s[x] + s[y];
    }
    bool same(int x, int y) { return find(x) == find(y); }
    int size(int x) { return s[find(x)]; }
};

class tarjan_offline_lca {
private:
    ll n;
    UnionFind uf;
    vector<ll> anc, lca, visit, used;
    vector<vector<ll>> g;
    vector<vector<PII>> query;
    void dfs(ll v=0, ll p=-1) {
        anc[v] = v;
        for(auto to: g[v]) if(to != p) {
            dfs(to, v);
            uf.unite(to, v);
            anc[uf.find(v)] = v;
        }
        visit[v] = 1;
        for(auto i: query[v]) {
            if(visit[i.first] == 1 && used[i.second]++ == 0) {
                lca[i.second] = anc[uf.find(i.first)];
            }
        }
    }
public:
    tarjan_offline_lca() {}
    tarjan_offline_lca(ll n, ll q) : n(n), uf(n), anc(n), lca(q), visit(n), used(q), g(n), query(n) {}
    // 辺とクエリの追加
    void add_edge(ll a, ll b) {
        g[a].push_back(b);
        g[b].push_back(a);
    }
    // i番目のクエリは頂点aと頂点bのLCA
    void add_query(ll a, ll b, ll i) {
        query[a].push_back({b, i});
        query[b].push_back({a, i});
    }
    // lcaを求める
    vector<ll> build() { dfs(); return lca; }
};
// END CUT