struct persistentUnionFind {
  persistentArray<int> data;

  persistentUnionFind() {}
  persistentUnionFind(int sz) { data.build(V<int>(sz, -1)); }

  int find(int k) {
    int p = data[k];
    return p >= 0 ? find(p) : k;
  }
  void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) return;
    auto u = data[x];
    auto v = data[y];
    if(u < v) {
      auto a = data.mutable_get(x);
      *a += v;
      auto b = data.mutable_get(y);
      *b = x;
    } else {
      auto a = data.mutable_get(y);
      *a += u;
      auto b = data.mutable_get(x);
      *b = y;
    }
  }
  bool same(int x, int y) {
    return find(x) == find(y);
  }
  int size(int x) {
    return -data[find(x)];
  }
};