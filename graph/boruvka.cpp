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
 
template< typename T, typename F >
T boruvka(ll n, F f) {
  vector<ll> rev(n), belong(n);
  UnionFind uf(n);
  T ret = T();
  while(uf.size(0) != n) {
    ll ptr = 0;
    REP(i, n) {
      if(uf.find(i) == i) {
        belong[i] = ptr++;
        rev[belong[i]] = i;
      }
    }
    REP(i, n) belong[i] = belong[uf.find(i)];
    auto v = f(ptr, belong);
    bool update = false;
    REP(i, ptr) {
      if(~v[i].second && !uf.same(rev[i], rev[v[i].second])) {
        uf.unite(rev[i], rev[v[i].second]);
        ret += v[i].first;
        update = true;
      }
    }
    if(!update) return -1; // notice!!
  }
  return ret;
}