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


# :warning: oldcode/zz_icpcYokohama2018-J.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#bf50ccff88ac9b2562bee63cf804278c">oldcode</a>
* <a href="{{ site.github.repository_url }}/blob/master/oldcode/zz_icpcYokohama2018-J.cpp">View this file on GitHub</a>
    - Last commit date: 2019-10-03 22:20:29+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
// #define int ll
using PII = pair<ll, ll>;

#define FOR(i, a, n) for (ll i = (ll)a; i < (ll)n; ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(x) x.begin(), x.end()

template<typename T> T &chmin(T &a, const T &b) { return a = min(a, b); }
template<typename T> T &chmax(T &a, const T &b) { return a = max(a, b); }
template<typename T> bool IN(T a, T b, T x) { return a<=x&&x<b; }
template<typename T> T ceil(T a, T b) { return a/b + !!(a%b); }

template<typename T> vector<T> make_v(size_t a) { return vector<T>(a); }
template<typename T,typename... Ts>
auto make_v(size_t a,Ts... ts) {
  return vector<decltype(make_v<T>(ts...))>(a,make_v<T>(ts...));
}
template<typename T,typename V> typename enable_if<is_class<T>::value==0>::type
fill_v(T &t, const V &v) { t=v; }
template<typename T,typename V> typename enable_if<is_class<T>::value!=0>::type
fill_v(T &t, const V &v ) { for(auto &e:t) fill_v(e,v); }

template<class S,class T>
ostream &operator <<(ostream& out,const pair<S,T>& a){
  out<<'('<<a.first<<','<<a.second<<')'; return out;
}
template<typename T>
istream& operator >> (istream& is, vector<T>& vec){
  for(T& x: vec) {is >> x;} return is;
}
template<class T>
ostream &operator <<(ostream& out,const vector<T>& a){
  out<<'['; for(T i: a) {out<<i<<',';} out<<']'; return out;
}

int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0}; // DRUL
const int INF = 1<<30;
const ll LLINF = 1LL<<40;
const ll MOD = 1000000007;

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

  LCA(int n_=100000) :
    n(n_), g(n, vector<edge>()), depth(n), vs(2*n-1),
    depth_seq(2*n-1), id(n), es((n-1)*2), w(n-1)
  {
    bit.init(2*n-1);
  }
  // u-vに重みcostのi番目の辺を張る
  void add_edge(int i, int u, int v, int cost) {
    g[u].push_back({i, v, cost});
    g[v].push_back({i, u, cost});
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
LCA graph;
vector<ll> pos, depth;

signed main(void)
{
  cin.tie(0);
  ios::sync_with_stdio(false);

  ll n;
  cin >> n;
  vector<vector<ll>> g(n);
  REP(i, n-1) {
    ll a, b;
    cin >> a >> b;
    a--, b--;
    graph.add_edge(i, a, b, 1);
    g[a].push_back(b);
    g[b].push_back(a);
  }
  graph.build();
  vector<ll> c(n);
  REP(i, n) cin >> c[i], c[i]--;

  ll k = 0;
  // 頂点vがpre-orderで何番目か、深さが何か
  pos.resize(n), depth.resize(n);
  function<void(ll,ll,ll)> dfs = [&](ll v, ll p, ll d) {
    depth[v] = d;
    pos[v] = k++;
    for(auto to: g[v]) {
      if(to == p) continue;
      dfs(to, v, d+1);
    }
  };
  dfs(0, -1, 0);

  // LCA, edgeの数, 頂点集合
  // add
  // LCAが変化した場合→元のLCAから変更した頂点の距離の分edgeの数が増加
  // LCAが変化していない場合→closest LCAから変更した頂点までの距離の分edgeの数が増加
  // sub
  // LCAが変化した場合→変化した後のLCAから変更した頂点の距離の分edgeの数が減少
  // LCAが変化していない場合→closest LCAから変更した頂点までの距離の分edgeの数の減少

  struct node {
    ll lca, e_num;
    set<PII> vertex;
    node() : lca(-1), e_num(-1) {}

    void add(ll v) {
      if(vertex.size() == 0) {
        e_num = 0;
        lca = v;
      } else {
        ll n_lca = graph.get(lca, v);
        if(n_lca == lca) {
          // closest LCAを見つける
          auto itr = vertex.upper_bound({pos[v], v});
          ll clca = -1;
          if(itr != vertex.end()) {
            clca = graph.get(itr->second, v);
          }
          itr = vertex.lower_bound({pos[v], v});
          if(itr != vertex.begin()) {
            itr--;
            ll tmp = graph.get(itr->second, v);
            if(clca == -1 || depth[clca] < depth[tmp]) clca = tmp;
          }
          assert(clca != -1);
          e_num += graph.length(clca, v);
        } else {
          e_num += graph.length(lca, v);
          lca = n_lca;
        }
      }
      vertex.insert({pos[v], v});
    }

    void sub(ll v) {
      assert(vertex.size() != 0);
      vertex.erase({pos[v], v});
      if(vertex.size() == 0) {
        lca = -1;
        e_num = -1;
      } else {
        ll mi = vertex.begin()->second;
        ll ma = vertex.rbegin()->second;
        ll n_lca = graph.get(mi, ma);
        if(n_lca == lca) {
          // closest LCAを見つける
          auto itr = vertex.upper_bound({pos[v], v});
          ll clca = -1;
          if(itr != vertex.end()) {
            clca = graph.get(itr->second, v);
          }
          itr = vertex.lower_bound({pos[v], v});
          if(itr != vertex.begin()) {
            itr--;
            ll tmp = graph.get(itr->second, v);
            if(clca == -1 || depth[clca] < depth[tmp]) clca = tmp;
          }
          assert(clca != -1);
          e_num -= graph.length(clca, v);
        } else {
          e_num -= graph.length(lca, v);
          lca = n_lca;
        }
      }
    }
  };
  vector<node> dat(100000);
  REP(i, n) dat[c[i]].add(i);

  ll m;
  cin >> m;
  REP(i, m) {
    char ch;
    cin >> ch;
    if(ch == 'Q') {
      ll x; cin >> x; x--;
      cout << /*"ans=" <<*/ dat[x].e_num << endl;
    } else if(ch == 'U') {
      ll x, y;
      cin >> x >> y;
      x--, y--;
      dat[c[x]].sub(x);
      dat[y].add(x);
      c[x] = y;

//      cout << "dat" << endl;
//      REP(j, 4) {
//        cout << dat[j].lca << " " << dat[j].e_num << endl;
//        for (auto k: dat[j].vertex) cout << k << " ";
//        cout << endl;
//      }
    }
  }

  return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "oldcode/zz_icpcYokohama2018-J.cpp"
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
// #define int ll
using PII = pair<ll, ll>;

#define FOR(i, a, n) for (ll i = (ll)a; i < (ll)n; ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(x) x.begin(), x.end()

template<typename T> T &chmin(T &a, const T &b) { return a = min(a, b); }
template<typename T> T &chmax(T &a, const T &b) { return a = max(a, b); }
template<typename T> bool IN(T a, T b, T x) { return a<=x&&x<b; }
template<typename T> T ceil(T a, T b) { return a/b + !!(a%b); }

template<typename T> vector<T> make_v(size_t a) { return vector<T>(a); }
template<typename T,typename... Ts>
auto make_v(size_t a,Ts... ts) {
  return vector<decltype(make_v<T>(ts...))>(a,make_v<T>(ts...));
}
template<typename T,typename V> typename enable_if<is_class<T>::value==0>::type
fill_v(T &t, const V &v) { t=v; }
template<typename T,typename V> typename enable_if<is_class<T>::value!=0>::type
fill_v(T &t, const V &v ) { for(auto &e:t) fill_v(e,v); }

template<class S,class T>
ostream &operator <<(ostream& out,const pair<S,T>& a){
  out<<'('<<a.first<<','<<a.second<<')'; return out;
}
template<typename T>
istream& operator >> (istream& is, vector<T>& vec){
  for(T& x: vec) {is >> x;} return is;
}
template<class T>
ostream &operator <<(ostream& out,const vector<T>& a){
  out<<'['; for(T i: a) {out<<i<<',';} out<<']'; return out;
}

int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0}; // DRUL
const int INF = 1<<30;
const ll LLINF = 1LL<<40;
const ll MOD = 1000000007;

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

  LCA(int n_=100000) :
    n(n_), g(n, vector<edge>()), depth(n), vs(2*n-1),
    depth_seq(2*n-1), id(n), es((n-1)*2), w(n-1)
  {
    bit.init(2*n-1);
  }
  // u-vに重みcostのi番目の辺を張る
  void add_edge(int i, int u, int v, int cost) {
    g[u].push_back({i, v, cost});
    g[v].push_back({i, u, cost});
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
LCA graph;
vector<ll> pos, depth;

signed main(void)
{
  cin.tie(0);
  ios::sync_with_stdio(false);

  ll n;
  cin >> n;
  vector<vector<ll>> g(n);
  REP(i, n-1) {
    ll a, b;
    cin >> a >> b;
    a--, b--;
    graph.add_edge(i, a, b, 1);
    g[a].push_back(b);
    g[b].push_back(a);
  }
  graph.build();
  vector<ll> c(n);
  REP(i, n) cin >> c[i], c[i]--;

  ll k = 0;
  // 頂点vがpre-orderで何番目か、深さが何か
  pos.resize(n), depth.resize(n);
  function<void(ll,ll,ll)> dfs = [&](ll v, ll p, ll d) {
    depth[v] = d;
    pos[v] = k++;
    for(auto to: g[v]) {
      if(to == p) continue;
      dfs(to, v, d+1);
    }
  };
  dfs(0, -1, 0);

  // LCA, edgeの数, 頂点集合
  // add
  // LCAが変化した場合→元のLCAから変更した頂点の距離の分edgeの数が増加
  // LCAが変化していない場合→closest LCAから変更した頂点までの距離の分edgeの数が増加
  // sub
  // LCAが変化した場合→変化した後のLCAから変更した頂点の距離の分edgeの数が減少
  // LCAが変化していない場合→closest LCAから変更した頂点までの距離の分edgeの数の減少

  struct node {
    ll lca, e_num;
    set<PII> vertex;
    node() : lca(-1), e_num(-1) {}

    void add(ll v) {
      if(vertex.size() == 0) {
        e_num = 0;
        lca = v;
      } else {
        ll n_lca = graph.get(lca, v);
        if(n_lca == lca) {
          // closest LCAを見つける
          auto itr = vertex.upper_bound({pos[v], v});
          ll clca = -1;
          if(itr != vertex.end()) {
            clca = graph.get(itr->second, v);
          }
          itr = vertex.lower_bound({pos[v], v});
          if(itr != vertex.begin()) {
            itr--;
            ll tmp = graph.get(itr->second, v);
            if(clca == -1 || depth[clca] < depth[tmp]) clca = tmp;
          }
          assert(clca != -1);
          e_num += graph.length(clca, v);
        } else {
          e_num += graph.length(lca, v);
          lca = n_lca;
        }
      }
      vertex.insert({pos[v], v});
    }

    void sub(ll v) {
      assert(vertex.size() != 0);
      vertex.erase({pos[v], v});
      if(vertex.size() == 0) {
        lca = -1;
        e_num = -1;
      } else {
        ll mi = vertex.begin()->second;
        ll ma = vertex.rbegin()->second;
        ll n_lca = graph.get(mi, ma);
        if(n_lca == lca) {
          // closest LCAを見つける
          auto itr = vertex.upper_bound({pos[v], v});
          ll clca = -1;
          if(itr != vertex.end()) {
            clca = graph.get(itr->second, v);
          }
          itr = vertex.lower_bound({pos[v], v});
          if(itr != vertex.begin()) {
            itr--;
            ll tmp = graph.get(itr->second, v);
            if(clca == -1 || depth[clca] < depth[tmp]) clca = tmp;
          }
          assert(clca != -1);
          e_num -= graph.length(clca, v);
        } else {
          e_num -= graph.length(lca, v);
          lca = n_lca;
        }
      }
    }
  };
  vector<node> dat(100000);
  REP(i, n) dat[c[i]].add(i);

  ll m;
  cin >> m;
  REP(i, m) {
    char ch;
    cin >> ch;
    if(ch == 'Q') {
      ll x; cin >> x; x--;
      cout << /*"ans=" <<*/ dat[x].e_num << endl;
    } else if(ch == 'U') {
      ll x, y;
      cin >> x >> y;
      x--, y--;
      dat[c[x]].sub(x);
      dat[y].add(x);
      c[x] = y;

//      cout << "dat" << endl;
//      REP(j, 4) {
//        cout << dat[j].lca << " " << dat[j].e_num << endl;
//        for (auto k: dat[j].vertex) cout << k << " ";
//        cout << endl;
//      }
    }
  }

  return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

