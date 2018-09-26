/**
* @file unionfind.cpp
* @brief unionfind
* @detail verify: 色々
* @author ferin
*/

// BEGIN CUT
class UnionFind {
public:
  const static int MAX_N = 100010;
  int par[MAX_N];
  int s[MAX_N];
  UnionFind() { init(); }
  UnionFind(int n) { init(n); }
  void init() { for(int i=0; i<MAX_N; ++i) par[i] = i, s[i] = 1; }
  void init(int n) { for(int i=0; i<n; ++i) par[i] = i, s[i] = 1; }
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
UnionFind uf;
// END CUT