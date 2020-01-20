---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: graph/LCA_can_weight_change.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/LCA_can_weight_change.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 04:35:05+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// Binary Indexed Tree
// 0-indexed
template <typename T>
class BIT {
private:
  // データ
  vector<T> bit;
  // 単位元, 要素数
  int neutral = 0;
  // 更新クエリ, 区間クエリ
  function<T(T,T)> f = [](const T l, const T r) -> T { return l+r; },
                   g = [](const T l, const T r) -> T { return l+r; };
public:
  // 初期化
  BIT(int n_ = 1e5) { init(n_); }
  void init(int n_ = 1e5) { bit.assign(n_+1, neutral); }
  // iに対する点更新クエリ
  void update(int i, T w) {
    for(int x = i+1; x < bit.size(); x += x&-x) bit[x] = f(bit[x], w);
  }
  // [0,i)に対する区間クエリ
  T query(int i) {
    T ret = neutral;
    for(int x = i+1; x > 0; x -= x & -x) ret = g(ret, bit[x]);
    return ret;
  }
};

template <typename S>
class sparseTable {
public:
  using T = typename S::T;
  int n;
  vector<int> log2;
  vector<vector<T>> t;

  sparseTable(int nn = 1e5) { init(nn); }
  void init(int nn) {
    n = nn;
    log2.assign(n+1, 0);
    for(int i=2; i<=n; ++i) log2[i] = log2[i >> 1] + 1;
    t.assign(log2[n]+1, vector<T>(n));
  }
  void build(vector<T> v) {
    for(int i=0; i<n; ++i) t[0][i] = v[i];
    for(int j=1; j<=log2[n]; ++j) {
      int w = 1LL<<(j-1);
      for (int i = 0; i+(w<<1) <= n; ++i) {
        t[j][i] = S::op(t[j-1][i], t[j-1][i+w]);
      }
    }
  }
  // [l, r]
  T query(int l, int r) {
    int j = log2[r - l];
    return S::op(t[j][l], t[j][r-(1 << j)+1]);
  }
};
struct minimum {
  using T = PII;
  static T op(const T& a, const T& b) { return min(a, b); }
};

struct LCA {
  struct edge { int id, to, cost; };
  const int n = 0;
  const int log2_n = 0;
  vector<vector<int>> par;
  vector<vector<edge>> g;
  vector<int> depth;     // 頂点iの深さ
  vector<int> vs;        // 頂点を訪問順に並べたもの
  vector<int> depth_seq; // depth_seq[i] = (頂点vs[i]の深さ)
  vector<int> id;        // 頂点が初めてvsに登場するインデックス
  vector<int> es;        // 辺のインデックス(i*2+(葉方向:0,根方向:1))
  vector<int> w;         // 辺の重み
  BIT<int> bit;
  sparseTable<minimum> st;

  void dfs(int v, int p, int d, int &k) {
    id[v] = k; vs[k] = v; depth_seq[k++] = d; depth[v] = d;
    for(auto e: g[v]) {
      if(e.to == p) continue;
      bit.update(k, e.cost); es[e.id*2] = k;
      dfs(e.to, v, d+1, k);
      vs[k] = v; depth_seq[k++] = d;
      bit.update(k, -e.cost); es[e.id*2+1] = k;
    }
  }

  LCA(int n_=1e5) :
    n(n_), g(n, vector<edge>()), depth(n), vs(2*n-1),
    depth_seq(2*n-1), id(n), es((n-1)*2), w(n-1)
  {
    bit.init(2*n-1);
  }
  // u-vに重みcostのi番目の辺を張る
  void add_edge(int i, int u, int v, int cost) {
    g[u].PB({i, v, cost});
    g[v].PB({i, u, cost});
    w[i] = cost;
  }
  // rootを根として初期化
  void build(int root = 0) {
    int k = 0;
    dfs(root, -1, 0, k);
    // RMQの初期化
    vector<PII> v(2*n-1);
    REP(i, 2*n-1) v[i] = {depth_seq[i], i};
    st.init(2*n-1);
    st.build(v);
  }

  // uとvのlcaを返す O(logN)
  int get(int u, int v) {
    if(id[u] > id[v]) swap(u, v);
    return vs[st.query(id[u], id[v]).second];
  }
  // uとvの距離を返す O(logN)
  int length(int u, int v) {
    int lca = get(u, v);
    return bit.query(id[v]) + bit.query(id[u]) - 2*bit.query(id[lca]);
  }
  // 辺xのコストをtに変更 O(logN)
  void update(int x, int t) {
    t = !w[x];
    bit.update(es[x*2], t - w[x]);
    bit.update(es[x*2+1], w[x] - t);
    w[x] = t;
  }
};
// ---------------------------------------------------------------

int c[100010];
signed main(void)
{
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  cin >> n;
  LCA lca(n);
  VI p(n);
  FOR(i, 1, n) {
    cin >> p[i]; p[i]--;
  }
  REP(i, n) cin >> c[i];

  FOR(i, 1, n) {
    int cost = c[i]==c[p[i]]?1:0;
    lca.add_edge(i-1, i, p[i], cost);
  }
  lca.build();

  vector<string> ans;
  int q;
  cin >> q;
  REP(i, q) {
    int type;
    cin >> type;
    if(type == 1) {
      int u; cin >> u; u--;
      if(u == 0) continue;
      // u と p[u] の間の辺について更新
      lca.update(u-1, 0);
    } else {
      int u, v; cin >> u >> v; u--, v--;
      ans.PB(lca.length(u,v)>=1?"NO":"YES");
    }
  }

  REP(i, ans.size()) {
    cout << ans[i] << endl;
  }

  return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/LCA_can_weight_change.cpp"
// Binary Indexed Tree
// 0-indexed
template <typename T>
class BIT {
private:
  // データ
  vector<T> bit;
  // 単位元, 要素数
  int neutral = 0;
  // 更新クエリ, 区間クエリ
  function<T(T,T)> f = [](const T l, const T r) -> T { return l+r; },
                   g = [](const T l, const T r) -> T { return l+r; };
public:
  // 初期化
  BIT(int n_ = 1e5) { init(n_); }
  void init(int n_ = 1e5) { bit.assign(n_+1, neutral); }
  // iに対する点更新クエリ
  void update(int i, T w) {
    for(int x = i+1; x < bit.size(); x += x&-x) bit[x] = f(bit[x], w);
  }
  // [0,i)に対する区間クエリ
  T query(int i) {
    T ret = neutral;
    for(int x = i+1; x > 0; x -= x & -x) ret = g(ret, bit[x]);
    return ret;
  }
};

template <typename S>
class sparseTable {
public:
  using T = typename S::T;
  int n;
  vector<int> log2;
  vector<vector<T>> t;

  sparseTable(int nn = 1e5) { init(nn); }
  void init(int nn) {
    n = nn;
    log2.assign(n+1, 0);
    for(int i=2; i<=n; ++i) log2[i] = log2[i >> 1] + 1;
    t.assign(log2[n]+1, vector<T>(n));
  }
  void build(vector<T> v) {
    for(int i=0; i<n; ++i) t[0][i] = v[i];
    for(int j=1; j<=log2[n]; ++j) {
      int w = 1LL<<(j-1);
      for (int i = 0; i+(w<<1) <= n; ++i) {
        t[j][i] = S::op(t[j-1][i], t[j-1][i+w]);
      }
    }
  }
  // [l, r]
  T query(int l, int r) {
    int j = log2[r - l];
    return S::op(t[j][l], t[j][r-(1 << j)+1]);
  }
};
struct minimum {
  using T = PII;
  static T op(const T& a, const T& b) { return min(a, b); }
};

struct LCA {
  struct edge { int id, to, cost; };
  const int n = 0;
  const int log2_n = 0;
  vector<vector<int>> par;
  vector<vector<edge>> g;
  vector<int> depth;     // 頂点iの深さ
  vector<int> vs;        // 頂点を訪問順に並べたもの
  vector<int> depth_seq; // depth_seq[i] = (頂点vs[i]の深さ)
  vector<int> id;        // 頂点が初めてvsに登場するインデックス
  vector<int> es;        // 辺のインデックス(i*2+(葉方向:0,根方向:1))
  vector<int> w;         // 辺の重み
  BIT<int> bit;
  sparseTable<minimum> st;

  void dfs(int v, int p, int d, int &k) {
    id[v] = k; vs[k] = v; depth_seq[k++] = d; depth[v] = d;
    for(auto e: g[v]) {
      if(e.to == p) continue;
      bit.update(k, e.cost); es[e.id*2] = k;
      dfs(e.to, v, d+1, k);
      vs[k] = v; depth_seq[k++] = d;
      bit.update(k, -e.cost); es[e.id*2+1] = k;
    }
  }

  LCA(int n_=1e5) :
    n(n_), g(n, vector<edge>()), depth(n), vs(2*n-1),
    depth_seq(2*n-1), id(n), es((n-1)*2), w(n-1)
  {
    bit.init(2*n-1);
  }
  // u-vに重みcostのi番目の辺を張る
  void add_edge(int i, int u, int v, int cost) {
    g[u].PB({i, v, cost});
    g[v].PB({i, u, cost});
    w[i] = cost;
  }
  // rootを根として初期化
  void build(int root = 0) {
    int k = 0;
    dfs(root, -1, 0, k);
    // RMQの初期化
    vector<PII> v(2*n-1);
    REP(i, 2*n-1) v[i] = {depth_seq[i], i};
    st.init(2*n-1);
    st.build(v);
  }

  // uとvのlcaを返す O(logN)
  int get(int u, int v) {
    if(id[u] > id[v]) swap(u, v);
    return vs[st.query(id[u], id[v]).second];
  }
  // uとvの距離を返す O(logN)
  int length(int u, int v) {
    int lca = get(u, v);
    return bit.query(id[v]) + bit.query(id[u]) - 2*bit.query(id[lca]);
  }
  // 辺xのコストをtに変更 O(logN)
  void update(int x, int t) {
    t = !w[x];
    bit.update(es[x*2], t - w[x]);
    bit.update(es[x*2+1], w[x] - t);
    w[x] = t;
  }
};
// ---------------------------------------------------------------

int c[100010];
signed main(void)
{
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  cin >> n;
  LCA lca(n);
  VI p(n);
  FOR(i, 1, n) {
    cin >> p[i]; p[i]--;
  }
  REP(i, n) cin >> c[i];

  FOR(i, 1, n) {
    int cost = c[i]==c[p[i]]?1:0;
    lca.add_edge(i-1, i, p[i], cost);
  }
  lca.build();

  vector<string> ans;
  int q;
  cin >> q;
  REP(i, q) {
    int type;
    cin >> type;
    if(type == 1) {
      int u; cin >> u; u--;
      if(u == 0) continue;
      // u と p[u] の間の辺について更新
      lca.update(u-1, 0);
    } else {
      int u, v; cin >> u >> v; u--, v--;
      ans.PB(lca.length(u,v)>=1?"NO":"YES");
    }
  }

  REP(i, ans.size()) {
    cout << ans[i] << endl;
  }

  return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

