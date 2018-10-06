<!--
{"id":"8599973812300296413","title":"ライブラリ","categories":[],"draft":false}
-->
BIT sum
```c++
  int bit[100010], n = 100010;

  //0からi-1番目までの和
  int sum(int i) {
    i++;
    int s = 0;
    while(i > 0) {
      s += bit[i];
      i -= i&-i;
    }
    return s;
  }

  //i番目(0-index)にxを加える
  void add(int i, int x) {
    i++;
    while(i <= n) {
      bit[i] += x;
      i += i&-i;
    }
  }
  $1
```

BIT max
```c++
  // Binary Indexed Tree
  // 区間和じゃなくて区間の最大を求められる版
  class BIT {
  private:
    int n;
    int bit[MAX_N];

  public:
    void init(int num);
    void add(int a, int w);
    int maximum(int a);
    void debug(void);
  };

  void BIT::init(int num) {
    n = MAX_N;
    for (int i = 0; i < MAX_N; i++)
      bit[i] = 0;
  }

  // a-1の位置にwを更新
  void BIT::add(int a, int w) {
    for (int x = a; x < n; x |= x + 1) {
      if (bit[x] < w)
        bit[x] = w;
    }
  }

  // 0 から a-1 までの最大値を求める
  int BIT::maximum(int a) {
    int ret = -INF;
    for (int x = a - 1; x >= 0; x = (x & (x + 1)) - 1)
      ret = max(ret, bit[x]);
    return ret;
  }

  // BITの中身を表示（デバッグ用）
  void BIT::debug(void) {
    for(int i=0; i<10; i++) {
      cout << "i:" << i << " bit:" << bit[i] << endl;
    }
    cout << endl;
  }
  $1
```
エラトステネス
```c++
  //素数ならtrue
  bool prime[1000000];
  memset(prime, true, sizeof(prime));
  prime[0] = prime[1] = false;
  for (int i = 2; i * i <= 1000000; i++) {
    if (prime[i]) {
      for (int j = 2 * i; j <= 1000000; j += i) {
        prime[j] = false;
      }
    }
  }
  $1
```

LCA
```c++
  VI G[MAX_N];  //グラフの隣接リスト
  int root = 0;     //根のノード

  int parent[MAX_LOG_N][MAX_N];
  int depth[MAX_N];

  void dfs(int v, int p, int d) {
    parent[0][v] = p;
    depth[v] = d;
    REP(i, G[v].size()) if(G[v][i] != p) dfs(G[v][i], v, d+1);
  }

  //初期化 O(logn)
  void init(int n) {
    dfs(root, -1, 0);
    REP(k, MAX_LOG_N-1) REP(v, n) {
      if(parent[k][v] < 0) parent[k+1][v] = -1;
      else parent[k+1][v] = parent[k][parent[k][v]];
    }
  }

  // uとvのlcaを求める
  int lca(int u, int v) {
    if(depth[u] > depth[v]) swap(u, v);
    REP(k, MAX_LOG_N) {
      if((depth[v]-depth[u]) >> k & 1) v = parent[k][v];
    }
    if(u == v) return u;
    for(int k = MAX_LOG_N-1; k>=0; k--) {
      if(parent[k][u] != parent[k][v]) {
        u = parent[k][u];
        v = parent[k][v];
      }
    }
    return parent[0][u];
  }
  $1
```

matrix
```c++
  VVL mul(VVL &a, VVL &b) {
    VVL res(a.size(), VL(b[0].size(), 0));
    REP(i, a.size()) REP(j, b.size()) REP(k, b[0].size())
      res[i][k] ^= a[i][j] & b[j][k];
    return res;
  }

  VVL mypow(VVL x, ll n) {
    VVL y(x.size(), VL(x.size()));
    REP(i, x.size()) y[i][i] = (1LL << 32) - 1;
    while(n > 0) {
      if(n&1) y = mul(y, x);
      x = mul(x, x);
      n >>= 1;
    }
    return y;
  }
  $1
```

ford fulkerson
```c++
  struct edge {int to, cap, rev;};
  vector<edge> G[MAX_N+1];
  bool used[MAX_N+1];

  void add_edge(int from, int to, int cap) {
    G[from].push_back((edge){to, cap, (int)G[to].size()});
    G[to].push_back((edge){from, 0, (int)G[from].size()-1});
  }

  int dfs(int v, int t, int f) {
    if(v == t) return f;
    used[v] = true;
    REP(i, G[v].size()) {
      edge &e = G[v][i];
      if(!used[e.to] && e.cap > 0) {
        int d = dfs(e.to, t, min(f, e.cap));
        if(d > 0) {
          e.cap -= d;
          G[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }

  int max_flow(int s, int t) {
    int flow = 0;
    while(true) {
      memset(used, 0, sizeof(used));
      int f = dfs(s, t, INF);
      if(f == 0) return flow;
      flow += f;
    }
  }
  $1
```

binary pow
```c++
  //二分累乗法 xのe乗
  ll binpow(ll x, ll e) {
    ll a = 1, p = x;
    while(e > 0) {
      if(e%2 == 0) {p = (p*p) % MOD; e /= 2;}
      else {a = (a*p) % MOD; e--;}
    }
    return a % MOD;
  }
  $1
```

string split
```c++
  // sepで区切る
  vector<string> split(const string &str, char sep)
  {
    vector<string> v;
    auto first = str.begin();
    while( first != str.end() ) {
      auto last = first;
      while( last != str.end() && *last != sep ) ++last;
      v.push_back(std::string(first, last));
      if( last != str.end() ) ++last;
      first = last;
    }
    return v;
  }
  $1
```

toporojikaru Sort
```c++
  //グラフの隣接リスト
  VI g[100010];
  //頂点の入次数を管理
  int h[100010];
  signed main(void)
  {
    //頂点数v、辺の数e
    int v, e;
    cin >> v >> e;
    REP(i, e) {
      int s, t;
      cin >> s >> t;
      //頂点sから頂点tへの有向辺
      g[s].push_back(t);
      h[t]++;
    }

    //入次数が0の頂点の集合
    stack<int> st;

    //入次数が0の頂点であればstに追加
    REP(i, v) if(h[i] == 0) st.push(i);

    //ソートされた後のグラフ
    VI ans;
    //stがなくなるまでループ
    while(st.size()) {
      //stの集合のから一つ取り出す
      int i = st.top(); st.pop();
      ans.push_back(i);
      for(auto& j: g[i]) {
        //隣接する頂点の入次数をマイナス1
        h[j]--;
        //これによって入次数が0になればstに追加
        if(h[j] == 0) st.push(j);
      }
    }

    //ansを順に出力
    for(int i: ans) cout << i << endl;

    return 0;
  }
  $1
```

UnionFind
```c++
  #define MAX_N 200000

  class UnionFind {
  private:
    // 親と木の深さ
    int par[MAX_N];
    int rank[MAX_N];
    int s[MAX_N];
    bool used[MAX_N];
  public:
    UnionFind();
    UnionFind(int);
    int find(int x);
    void unite(int, int);
    bool same(int, int);
    int size(int);
    int group(int);
  };

  //MAX_Nで初期化
  UnionFind::UnionFind() {
    for(int i=0; i<MAX_N; ++i) {
      par[i] = i;
      rank[i] = 0;
      s[i] = 1;
    }
  }

  // 要素数nで初期化
  UnionFind::UnionFind(int n) {
    for(int i=0; i<n; i++) {
      par[i] = i;
      rank[i] = 0;
      s[i] = 1;
    }
  }

  // 要素xの親を求める
  int UnionFind::find(int x) {
    if(par[x] == x) return x;
    else return par[x] = find(par[x]);
  }

  // xとyの属する集合を併合
  void UnionFind::unite(int x, int y) {
    // xとyの親
    x = find(x);
    y = find(y);
    if(x == y) return;

    // yのほうが深さが深い　xの親はyの親
    if(rank[x] < rank[y]) {
      par[x] = y;
      s[y] = s[x] + s[y];
    }
    else {
      par[y] = x;
      s[x] = s[x] + s[y];
      if( rank[x] == rank[y] ) rank[x]++;
    }
  }

  // xの属する連結成分のサイズ
  int UnionFind::size(int x) { return s[find(x)];}

  // xとyが同じ集合に属するか
  bool UnionFind::same(int x, int y) { return find(x) == find(y);}

  // 連結成分数
  int UnionFind::group(int n) {
    REP(i, n) used[find(i)] = true;
    int ret = 0;
    REP(i, n) if(used[i]) ret++;
    return ret;
  }

  UnionFind uf;
  $1
```
構文解析
```c++
  typedef string::const_iterator State;
  class ParseError {};
  int expression(State&);
  int term(State&);
  int number(State&);
  int factor(State&);

  int expression(State &begin) {
    int ret = term(begin);
    while(1) {
      if(*begin == '+') {
        begin++;
        ret += term(begin);
      } else if(*begin == '-') {
        begin++;
        ret -= term(begin);
      } else {
        break;
      }
    }
    return ret;
  }

  int term(State &begin) {
    int ret = factor(begin);
    while(1) {
      if(*begin == '*') {
        begin++;
        ret *= factor(begin);
      } else if(*begin == '/') {
        begin++;
        ret /= factor(begin);
      } else {
        break;
      }
    }
    return ret;
  }

  int factor(State &begin) {
    if(*begin == '(') {
      begin++;
      int ret = expression(begin);
      begin++;
    } else {
      return number(begin);
    }
  }

  int number(State &begin) {
    int ret = 0;
    while(isdigit(*begin)) {
      ret *= 10;
      ret += *begin - '0';
      begin++;
    }
    return ret;
  }

  signed main(void)
  {
    string s;
    getline(cin, s);

    //REP(i, n) REP(j, n)
    State begin = s.begin();
    int ans = expression(begin);
    cout << ans << endl;

    return 0;
  }
  $1
```

strongly connected component
```c++
int V;
VI G[310], rG[310], vs;
VVI g;
bool used[310];
int cmp[310];

void add_edge(int from, int to) {
G[from].PB(to);
rG[to].PB(from);
}

void dfs(int v) {
used[v] = true;
// cout << "v:" << v << endl;
for(int i: G[v]) {
  if(!used[i]) dfs(i);
}
// cout << v << endl;
vs.PB(v);
}

void rdfs(int v, int k) {
// cout << v << "," << k << endl;
used[v] = true;
cmp[v] = k;
for(int i: rG[v]) {
  if(!used[i]) rdfs(i, k);
}
}

int scc() {
memset(used, 0, sizeof(used));
vs.clear();
REP(v, V) if(!used[v]) dfs(v);
// cout << "vs:"; REP(i, vs.size()) cout << vs[i] << " "; cout << endl;
memset(used, 0, sizeof(used));
int k = 0;
for(int i = vs.size() - 1; i >= 0; --i) {
  if(!used[vs[i]]) rdfs(vs[i], k++);
}
return k;
}

VVI getDAG() {
int N = scc();
VVI res(N);
vector<set<int>> st(N);
REP(i, V) st[cmp[i]].insert(i);
REP(i, N) {
  set<int> out;
  for(const auto& v : st[i]) {
    for(const auto& to : G[v]) {
      out.insert(cmp[to]);
    }
  }
  for(const auto& to : out) {
    res[i].emplace_back(to);
  }
}
return res;
}
  $1
```

区間更新 区間最小
```c++
// 区間更新、区間最小の遅延セグメントツリー
const int MAX_N = 1<<20;
struct RMQRUQ {
int n, dat[MAX_N*2-1], lazy[MAX_N*2-1];
bool flag[MAX_N*2-1];
RMQRUQ(){}
RMQRUQ(int n_) {init(n_);}
void init(int n_) {
  n = 1; while(n < n_) n *= 2;
  REP(i, n*2-1) dat[i] = INT_MAX, lazy[i] = 0, flag[i] = false;
}
void eval(int k, int l, int r) {
  if(flag[k]) {
    dat[k] = lazy[k];
    if(r-l>1) {
      lazy[2*k+1] = lazy[k]; flag[2*k+1] = true;
      lazy[2*k+2] = lazy[k]; flag[2*k+2] = true;
    }
    flag[k] = false;
  }
}
void update(int a, int b, ll x) {update(a,b,x,0,0,n);}
void update(int a, int b, ll x, int k, int l, int r) {
  eval(k, l, r);
  if(b <= l || r <= a) return;
  if(a <= l && r <= b) {
    lazy[k] = x;
    flag[k] = true;
    eval(k, l, r);
  } else {
    update(a, b, x, 2*k+1, l, (l+r)/2);
    update(a, b, x, 2*k+2, (l+r)/2, r);
    dat[k] = min(dat[2*k+1], dat[2*k+2]);
  }
}
ll query(int a, int b) {return query(a,b,0,0,n);}
ll query(int a, int b, int k, int l, int r) {
  eval(k, l, r);
  if(b <= l || r <= a) {
    return INT_MAX;
  }
  if(a <= l && r <= b) {
    return dat[k];
  }
  ll vl = query(a, b, 2*k+1, l, (l+r)/2);
  ll vr = query(a, b, 2*k+2, (l+r)/2, r);
  return min(vl, vr);
}
};
  $1
```

区間加算 区間和
```c++
// 区間加算、区間和の遅延セグメントツリー
const int MAX_N = 1<<20;
struct RSQRAQ {
int n;
ll dat[2*MAX_N-1], lazy[2*MAX_N-1];

RSQRAQ(){}
RSQRAQ(int n_) {init(n_);}
void init(int n_) {
  n = 1; while(n < n_) n *= 2;
  REP(i, 2*n-1) dat[i] = lazy[i] = 0;
}

void eval(int k, int l, int r) {
  if(lazy[k]) {
    dat[k] += lazy[k];
    if(r-l>1) {
      lazy[2*k+1] += lazy[k] / 2;
      lazy[2*k+2] += lazy[k] / 2;
    }
    lazy[k] = 0;
  }
}

void update(int a, int b, ll x) {update(a, b, x, 0, 0, n);}
void update(int a, int b, ll x, int k, int l, int r) {
  eval(k, l, r);
  if(b <= l || r <= a) return;
  if(a <= l && r <= b) {
    lazy[k] += (r-l)*x;
    eval(k, l, r);
  } else {
    update(a, b, x, 2*k+1, l, (l+r)/2);
    update(a, b, x, 2*k+2, (l+r)/2, r);
    dat[k] = dat[2*k+1] + dat[2*k+2];
  }
}

ll query(int a, int b) {return query(a, b, 0, 0, n);}
ll query(int a, int b, int k, int l, int r) {
  eval(k, l, r);
  if(b <= l || r <= a) return 0;
  if(a <= l && r <= b) return dat[k];
  ll vl = query(a, b, 2*k+1, l, (l+r)/2);
  ll vr = query(a, b, 2*k+2, (l+r)/2, r);
  return vl + vr;
}
};
  $1
```

セグメントツリー
```c++
template<class T>
class SegmentTree {
private:
int size_;
vector<T> dat;
T init__;

T calc(T d1, T d2) {
  return min(d1, d2);     // minnimum
  // return max(d1, d2);  // maximum
  // return d1+d2;        // sum
}
T query(int a, int b, int k, int l, int r) {
  if(r <= a || b <= l) return init__;
  if(a <= l && r <= b) return dat[k];
  return calc(query(a, b, 2*k+1, l, (l+r)/2),
                query(a, b, 2*k+2, (l+r)/2, r));
}

public:
SegmentTree() {}
SegmentTree(int n) {
  init__ = {INT_MAX, INT_MAX};  // 初期化用のを指定！！！
  for(size_ = 1; size_ < n; size_ *= 2);
  dat.assign(2*size_-1, init__);
}

void update(int k, PII a) {
  k += size_ - 1;
  dat[k] = a;      // max or min
  // dat[k] += a;  // sum
  while(k > 0) {
    k = (k-1) / 2;
    dat[k] = calc(dat[k*2+1], dat[k*2+2]);
  }
}

T query(int a, int b) {return query(a, b, 0, 0, size_);}

int size() {return size_;}

void debug() {
  int num = 1, nn = 0;
  REP(i, 2*size_-1) {
    cout << dat[i].first << "," << dat[i].second << " ";
    if(i == nn) {cout << endl; num *= 2; nn += num;}
  }
}
};
  $1
```

平衡二分探索木
```c++
unsigned xorShift() {
  static unsigned z = time(NULL);
  z ^= z << 13; z ^= z >> 17; z ^= z << 5;
  return z;
}

struct node {
  int val;
  node *ch[2];
  int pri;
  int cnt; //部分木のサイズ
  int sum; //部分木の値の和

  node(int v, double p): val(v),pri(p),cnt(1),sum(v) {
    ch[0] = ch[1] = nullptr;
  }
};

int count(node *t) {return t == nullptr ? 0: t->cnt;}
int sum(node *t) {return t == nullptr ? 0: t->sum;}

node *update(node *t) {
  t->cnt = count(t->ch[0]) + count(t->ch[1]) + 1;
  t->sum = sum(t->ch[0]) + sum(t->ch[1]) + t->val;
  return t;
}

// b=0で左回転、b=1で右回転
node *rotate(node *t, int b) {
  node *s = t->ch[1-b];
  t->ch[1-b] = s->ch[b];
  s->ch[b] = t;
  update(t);
  update(s);
  return s;
}

node *insert(node *t, int val, int pri) {
  if(t == nullptr) return new node(val, pri);
  else if(val == t->val) return t;
  else if(val < t->val) {
    t->ch[0] = insert(t->ch[0], val, pri);
    if(t->pri > t->ch[0]->pri) {
      t = rotate(t, 1);
    }
  } else{
    t->ch[1] = insert(t->ch[1], val, pri);
    if(t->pri > t->ch[1]->pri) {
      t = rotate(t, 0);
    }
  }
  return update(t);
}

node *erase(node *t, int x) {
  if (t->val == x) {
    if (t->ch[0] && t->ch[1]) {
      if (t->ch[0]->pri < t->ch[1]->pri) {
        t = rotate(t, 1);
        t->ch[1] = erase(t->ch[1], x);
        return update(t);
      } else {
        t = rotate(t, 0);
        t->ch[0] = erase(t->ch[0], x);
        return update(t);
      }
    } else {
      return t->ch[0] ? t->ch[0] : t->ch[1];
    }
  } else if (x < t->val) {
    t->ch[0] = erase(t->ch[0], x);
  } else {
    t->ch[1] = erase(t->ch[1], x);
  }
  return update(t);
}

int level(node *t, int k) {
  if(k < count(t->ch[0])) return level(t->ch[0], k);
  if(k == count(t->ch[0])) return t->val;
  return level(t->ch[1], k-count(t->ch[0])-1);
}
  $1
```

starryskytree
```c++
// 区間加算、区間最大のstarrysky木
struct starrysky {
int n;
const int init_ = 0;
VI lazym, lazya;
starrysky(){}
starrysky(int n_) {init(n_);}
void init(int n_) {
  n = 1; while(n<n_) n *= 2;
  lazym.assign(2*n-1, init_);
  lazya.assign(2*n-1, 0);
}
void add(int a, int b, int x) {add(a, b, x, 0, 0, n);}
void add(int a, int b, int x, int k, int l, int r) {
  if(r <= a || b <= l) return;
  if(a <= l && r <= b) lazya[k] += x;
  else {
    add(a, b, x, k*2+1, l, (l+r)/2);
    add(a, b, x, k*2+2, (l+r)/2, r);
    lazym[k] = max(lazym[k*2+1]+lazya[k*2+1],
                    lazym[k*2+2]+lazya[k*2+2]);
  }
}
int query(int a, int b) {return query(a, b, 0, 0, n);}
int query(int a, int b, int k, int l, int r) {
  if(r <= a || b <= l) return init_;
  if(a <= l && r <= b) return lazym[k] + lazya[k];
  int vl = query(a, b, k*2+1, l, (l+r)/2),
      vr = query(a, b, k*2+2, (l+r)/2, r);
  return max(vl, vr)+lazya[k];
}
};
  $1
```

パスカルの三角形
```c++
int c[50][50];
void init_comb(int n) {
REP(i, n) REP(j, n) c[i][j] = 1;
REP(i, n) {
  FOR(j, 1, i) c[i][j] = c[i-1][j] + c[i-1][j-1];
}
}
int C(int n, int r) {
return c[n][r];
}
  $1
```

フェルマーの小定理を使ったnCrの計算
```c++
ll combi(ll N_, ll C_) {
const int NUM_=400001;
static ll fact[NUM_+1],factr[NUM_+1],inv[NUM_+1];
if (fact[0]==0) {
  inv[1]=fact[0]=factr[0]=1;
  for (int i=2;i<=NUM_;++i) inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
  for (int i=1;i<=NUM_;++i) fact[i]=fact[i-1]*i%MOD, factr[i]=factr[i-1]*inv[i]%MOD;
}
if(C_<0 || C_>N_) return 0;
return factr[C_]*fact[N_]%MOD*factr[N_-C_]%MOD;
}
  $1
```

多倍長整数
```c++
typedef long long Int;
const Int B = 10000;      // base (power of 10)
const int BW = 4;         // log B
const int MAXDIGIT = 100; // it can represent 4*MAXDIGIT digits (in base 10)
struct BigNum {
Int digit[MAXDIGIT];
int size;
BigNum(int size = 1, Int a = 0) : size(size) {
  memset(digit, 0, sizeof(digit));
  digit[0] = a;
}
};
const BigNum ZERO(1, 0), ONE(1, 1);

// Comparators
bool operator<(BigNum x, BigNum y) {
if (x.size != y.size) return x.size < y.size;
for (int i = x.size-1; i >= 0; --i)
  if (x.digit[i] != y.digit[i]) return x.digit[i] < y.digit[i];
return false;
}
bool operator >(BigNum x, BigNum y) { return y < x; }
bool operator<=(BigNum x, BigNum y) { return !(y < x); }
bool operator>=(BigNum x, BigNum y) { return !(x < y); }
bool operator!=(BigNum x, BigNum y) { return x < y || y < x; }
bool operator==(BigNum x, BigNum y) { return !(x < y) && !(y < x); }

// Utilities
BigNum normal(BigNum x) {
Int c = 0;
for (int i = 0; i < x.size; ++i) {
  while (x.digit[i] < 0)
    x.digit[i+1] -= 1, x.digit[i] += B;
  Int a = x.digit[i] + c;
  x.digit[i] = a % B;
  c          = a / B;
}
for (; c > 0; c /= B) x.digit[x.size++] = c % B;
while (x.size > 1 && x.digit[x.size-1] == 0) --x.size;
return x;
}
BigNum convert(Int a) {
return normal(BigNum(1, a));
}
BigNum convert(const string &s) {
BigNum x;
int i = s.size() % BW;
if (i > 0) i -= BW;
for (; i < (int)s.size(); i += BW) {
  Int a = 0;
  for (int j = 0; j < BW; ++j)
    a = 10 * a + (i + j >= 0 ? s[i+j] - '0' : 0);
  x.digit[x.size++] = a;
}
reverse(x.digit, x.digit+x.size);
return normal(x);
}
// Input/Output
ostream &operator<<(ostream &os, BigNum x) {
os << x.digit[x.size-1];
for (int i = x.size-2; i >= 0; --i)
  os << setw(BW) << setfill('0') << x.digit[i];
return os;
}
istream &operator>>(istream &is, BigNum &x) {
string s; is >> s;
x = convert(s);
return is;
}

// Basic Operations
BigNum operator+(BigNum x, BigNum y) {
if (x.size < y.size) x.size = y.size;
for (int i = 0; i < y.size; ++i)
  x.digit[i] += y.digit[i];
return normal(x);
}
BigNum operator-(BigNum x, BigNum y) {
assert(x >= y);
for (int i = 0; i < y.size; ++i)
  x.digit[i] -= y.digit[i];
return normal(x);
}
BigNum operator*(BigNum x, BigNum y) {
BigNum z(x.size + y.size);
for (int i = 0; i < x.size; ++i)
  for (int j = 0; j < y.size; ++j)
    z.digit[i+j] += x.digit[i] * y.digit[j];
return normal(z);
}
BigNum operator*(BigNum x, Int a) {
for (int i = 0; i < x.size; ++i)
  x.digit[i] *= a;
return normal(x);
}
pair<BigNum, Int> divmod(BigNum x, Int a) {
Int c = 0, t;
for (int i = x.size-1; i >= 0; --i) {
  t          = B * c + x.digit[i];
  x.digit[i] = t / a;
  c          = t % a;
}
return pair<BigNum, Int>(normal(x), c);
}
BigNum operator/(BigNum x, Int a) {
return divmod(x, a).first;
}
Int operator%(BigNum x, Int a) {
return divmod(x, a).second;
}
pair<BigNum, BigNum> divmod(BigNum x, BigNum y) {
if (x.size < y.size) return pair<BigNum, BigNum>(ZERO, x);
int F = B / (y.digit[y.size-1] + 1); // multiplying good-factor
x = x * F; y = y * F;
BigNum z(x.size - y.size + 1);
for (int k = z.size-1, i = x.size-1; k >= 0; --k, --i) {
  z.digit[k]  = (i+1 < x.size ? x.digit[i+1] : 0) * B + x.digit[i];
  z.digit[k] /= y.digit[y.size-1];
  BigNum t(k + y.size);
  for (int m = 0; m < y.size; ++m)
    t.digit[k+m] = z.digit[k] * y.digit[m];
  t = normal(t);
  while (x < t) {
    z.digit[k] -= 1;
    for (int m = 0; m < y.size; ++m)
      t.digit[k+m] -= y.digit[m];
    t = normal(t);
  }
  x = x - t;
}
return pair<BigNum, BigNum>(normal(z), x / F);
}
BigNum operator/(BigNum x, BigNum y) {
return divmod(x, y).first;
}
BigNum operator%(BigNum x, BigNum y) {
return divmod(x, y).second;
}

// Advanced Operations
BigNum shift(BigNum x, int k) {
if (x.size == 1 && x.digit[0] == 0) return x;
x.size += k;
for (int i = x.size - 1; i >= k; --i) x.digit[i] = x.digit[i-k];
for (int i = k-1; i >= 0; --i) x.digit[i] = 0;
return x;
}
BigNum sqrt(BigNum x) { // verified UVA 10023
const BigNum _20 = convert(2*B);
BigNum odd = ZERO;
BigNum rem(2,0);
BigNum ans = ZERO;
for (int i = 2*((x.size-1)/2); i >= 0; i -= 2) {
  int group = (i+1 < x.size ? x.digit[i+1] : 0) * B + x.digit[i];
  odd =  _20 * ans + ONE;
  rem = shift(rem, 2) + convert(group);
  int count = 0;
  while (rem >= odd) {
    count = count + 1;
    rem = rem - odd;
    odd.digit[0] += 2;
    odd = normal(odd);
  }
  ans = shift(ans,1) + convert(count);
}
return ans;
}
  $1
```

インタラクティブ
```c++
// #define DEBUG
string ans = "qazwsxedcrfvtgbyhnujmikolp";
int query(string q) {
#ifdef DEBUG
  cout << q << endl;
  if(q == ans) cout << "equal" << endl, exit(0);
  else if(q > ans) {cout << "less" << endl; return 0;}
  else {cout << "greater" << endl; return 1;}
#else
  cout << q << endl;
  string res;
  cin >> res;
  if(res == "less") return 0;
  else if(res == "greater") return 1;
  else exit(0);
#endif
}
  $1
```

modint構造体
 ```c++
template<unsigned MOD>
class ModInt {
public:
unsigned x;
ModInt(): x(0) { }
ModInt(signed y) : x(y >= 0 ? y % MOD : MOD - (-y) % MOD) {}
unsigned get() const { return x; }

// 逆数
ModInt inv() const {
  ll a = 1, p = x, e = MOD-2;
  while(e > 0) {
    if(e%2 == 0) {p = (p*p) % MOD; e /= 2;}
    else {a = (a*p) % MOD; e--;}
  }
  a %= MOD;
  return ModInt(a);
}
// e乗
ModInt pow(ll e) {
  ll a = 1, p = x;
  while(e > 0) {
    if(e%2 == 0) {p = (p*p) % MOD; e /= 2;}
    else {a = (a*p) % MOD; e--;}
  }
  a %= MOD;
  return ModInt(a);
}
// 2のx乗
ModInt pow2() {
  ll a = 1, p = 2, e = x;
  while(e > 0) {
    if(e%2 == 0) {p = (p*p) % MOD; e /= 2;}
    else {a = (a*p) % MOD; e--;}
  }
  a %= MOD;
  return ModInt(a);
}

// Comparators
bool operator <(ModInt b) { return x < b.x; }
bool operator >(ModInt b) { return x > b.x; }
bool operator<=(ModInt b) { return x <= b.x; }
bool operator>=(ModInt b) { return x >= b.x; }
bool operator!=(ModInt b) { return x != b.x; }
bool operator==(ModInt b) { return x == b.x; }

// increment, decrement
ModInt operator++() { x++; return *this; }
ModInt operator++(int) {ModInt a = *this; x++; return a;}
ModInt operator--() { x--; return *this; }
ModInt operator--(int) {ModInt a = *this; x--; return a;}

// Basic Operations
ModInt &operator+=(ModInt that) {
  x = ((ll)x+that.x)%MOD;
  return *this;
}
ModInt &operator-=(ModInt that) {
  x = ((((ll)x-that.x)%MOD)+MOD)%MOD;
  return *this;
}
ModInt &operator*=(ModInt that) {
  x = (ll)x * that.x % MOD;
  return *this;
}
// O(log(mod))かかるので注意
ModInt &operator/=(ModInt that) {
  x = (ll)x * that.inv() % MOD;
  return *this;
}
ModInt &operator%=(ModInt that) {
  x = (ll)x % that.x;
  return *this;
}
ModInt operator+(ModInt that)const{return ModInt(*this) += that;}
ModInt operator-(ModInt that)const{return ModInt(*this) -= that;}
ModInt operator*(ModInt that)const{return ModInt(*this) *= that;}
ModInt operator/(ModInt that)const{return ModInt(*this) /= that;}
ModInt operator%(ModInt that)const{return ModInt(*this) %= that;}
};
typedef ModInt<998244353> mint;
// Input/Output
ostream &operator<<(ostream& os, mint a) { return os << a.x; }
istream &operator>>(istream& is, mint &a) { return is >> a.x; }
  $1
```

座圧
```c++
// xx, yy, zzにそれぞれ座圧する元の配列を突っ込むとx, y, zが座圧された配列で返ってくる
// zip[座圧前] = 座圧後、unzip[座圧後] = 座圧前
VL xx, x, unzip(100010);
unordered_map<int, int> zip;
void compress() {
x = xx;
sort(ALL(xx));
xx.erase(unique(ALL(xx)), xx.end());
REP(i, xx.size()) {zip[xx[i]] = i; unzip[i] = xx[i];}
REP(i, x.size()) x[i] = zip[x[i]];
}
  $1
```

中国人配達問題
```c++
int d[17][17], f[17];
signed main(void)
{
  int v, e, tot = 0;
  cin >> v >> e;
  REP(i, v) REP(j, v) d[i][j] = INF;
  REP(i, e) {
    int a, b, c;
    cin >> a >> b >> c;
    d[a][b] = min(d[a][b], c); d[b][a] = min(d[b][a], c);
    f[a]++; f[b]++;
    tot += c;
  }
  VI o;
  REP(i, v) if(f[i]%2) o.push_back(i);
  REP(k, v) REP(i, v) REP(j, v) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
  int dp[1<<16], os = o.size();
  fill(dp, dp+(1<<os), INF);
  dp[0] = 0;
  REP(s, 1<<os) REP(i, os) if(~s>>i&1) REP(j, i) if(~s>>j&1) {
    dp[s|1<<i|1<<j] = min(dp[s|1<<i|1<<j], dp[s] + d[o[i]][o[j]]);
  }
  cout << tot + dp[(1<<os)-1] << endl;
  return 0;
}
```

サイコロ
```c++
struct Dice{
  //top, front, right, left, back, bottom
  int side[6];
  Dice(){}
  Dice(int s[]){
    for(int i=0; i<6; ++i) side[i] = s[i];
  }

  void rotate(int op){
    int tmp = ' ';
    //右に倒す
    if(op==0){
      tmp = side[0];
      side[0] = side[3];
      side[3] = side[5];
      side[5] = side[2];
      side[2] = tmp;
    }

    //前に倒す
    if(op==1){
      tmp = side[0];
      side[0] = side[4];
      side[4] = side[5];
      side[5] = side[1];
      side[1] = tmp;
    }

    //左に倒す
    if(op==2){
      tmp = side[0];
      side[0] = side[2];
      side[2] = side[5];
      side[5] = side[3];
      side[3] = tmp;
    }

    //後ろに倒す
    if(op==3){
      tmp = side[0];
      side[0] = side[1];
      side[1] = side[5];
      side[5] = side[4];
      side[4] = tmp;
    }

    //topとbottomを軸に右回転
    if(op==4){
      tmp = side[1];
      side[1] = side[2];
      side[2] = side[4];
      side[4] = side[3];
      side[3] = tmp;
    }

    //topとbottomを軸に左回転
    if(op==5){
      tmp = side[1];
      side[1] = side[3];
      side[3] = side[4];
      side[4] = side[2];
      side[2] = tmp;
    }
  }
};

//24通りのサイコロを生成する
Dice initDice, dice[24];
void makeDice(){
  int tmpNum[] = {1,2,3,4,5,6};
  initDice = Dice(tmpNum);

  for(int i=0; i<24; ++i){
    if(i==4) initDice.rotate(1);
    if(i==8) initDice.rotate(1);
    if(i==12)initDice.rotate(1);
    if(i==16){
      initDice.rotate(1);
      initDice.rotate(0);
    }
    if(i==20){
      initDice.rotate(2);
      initDice.rotate(2);
    }
    initDice.rotate(4);
    dice[i] = initDice;
  }
}

// d[top][front] front, right, back, left
// 問題のdiceの設定とあっているか確認すること！！！！！
int d[6][6][4] = {
  {{-1, -1, -1, -1}, {2, 4, 5, 3}, {3, 2, 4, 5}, {4, 5, 3, 2}, {5, 3, 2, 4}, {-1, -1, -1, -1}}
  ,{{1, 3, 6, 4}, {-1, -1, -1, -1}, {3, 6, 4, 1}, {4, 1, 3, 6}, {-1, -1, -1, -1}, {6, 4, 1, 3}}
  ,{{1, 5, 6, 2}, {2, 1, 5, 6}, {-1,-1,-1,-1}, {-1,-1,-1,-1}, {5, 6, 2, 1}, {6, 2, 1, 5}}
  ,{{1, 2, 6, 5}, {2, 6, 5, 1}, {-1,-1,-1,-1}, {-1,-1,-1,-1}, {5, 1, 2, 6}, {6, 5, 1, 2}}
  ,{{1, 4, 6, 3}, {-1,-1,-1,-1}, {3, 1, 4, 6}, {4, 6, 3, 1}, {-1,-1,-1,-1}, {6, 3, 1, 4}}
  ,{{-1,-1,-1,-1}, {2, 3, 5, 4}, {3, 5, 4, 2}, {4, 2, 3, 5}, {5, 4, 2, 3}, {-1,-1,-1,-1}}};
```

編集距離
```c++
int dp[1010][1010];
signed main(void)
{
  string s, t;
  cin >> t >> s;
  const int n = s.size(), m = t.size();
  REP(i, n+1) REP(j, m+1) {
    if(i == 0) dp[i][j] = j;
    else if(j == 0) dp[i][j] = i;
    else {
      if(s[i-1] == t[j-1]) {
        dp[i][j] = min({dp[i-1][j-1], dp[i-1][j]+1, dp[i][j-1]+1});
      } else {
        dp[i][j] = min({dp[i-1][j] + 1, dp[i][j-1] + 1, dp[i-1][j-1]+1});
      }
    }
  }
  cout << dp[n][m] << endl;
  return 0;
}
```

EERTREE
```c++
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<ll> VL;
typedef vector<VL> VVL;
typedef pair<int, int> PII;

#define FOR(i, a, n) for (ll i = (ll)a; i < (ll)n; ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(x) x.begin(), x.end()
#define IN(a, b, x) (a<=x&&x<b)
#define MP make_pair
#define PB push_back
#define INF (1LL<<30)
#define LLINF (1LL<<60)
#define PI 3.14159265359
#define EPS 1e-12
//#define int ll

template <typename T> T &chmin(T &a, const T &b) { return a = min(a, b); }
template <typename T> T &chmax(T &a, const T &b) { return a = max(a, b); }

int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

struct PalindromicTree{
  struct node{
    map<char,int> nxt;
    int len,suf,hei,app,cnt;
  };
  string s;
  vector<node> v;
  vector<int> ord;
  int n,suff;
  PalindromicTree(){}
  PalindromicTree(string s_){init(s_);build();}
  bool addchar(int pos){
    char ch=s[pos];
    int cur=suff;
    while(1){
      if(pos-1-v[cur].len>=0&&s[pos-1-v[cur].len]==ch) break;
      cur=v[cur].suf;
    }
    if(v[cur].nxt.count(ch)){
      suff=v[cur].nxt[ch];
      v[suff].cnt++;
      return false;
    }
    suff=n++;
    v[suff].len=v[cur].len+2;
    v[suff].app=pos-v[suff].len+1;
    v[suff].cnt=1;
    v[cur].nxt[ch]=suff;

    if(v[suff].len==1){
      v[suff].suf=1;
      v[suff].hei=1;
      return true;
    }
    while(1){
      cur=v[cur].suf;
      if(pos-1-v[cur].len>=0&&s[pos-1-v[cur].len]==ch){
	v[suff].suf=v[cur].nxt[ch];
	break;
      }
    }
    v[suff].hei=v[v[suff].suf].hei+1;
    return true;
  }

  void init(string s_){
    s=s_;
    v.clear();
    v.resize(s.length()+10);

    n=2;
    suff=1;
    v[0].app=v[1].app=-1;
    v[0].len=-1;v[1].len=0;
    v[0].suf=v[1].suf=0;
    v[0].hei=v[1].hei=0;
  }

  void calcOrder(){
    ord.clear();
    ord.push_back(0);
    ord.push_back(1);
    for(int i=0;i<(int)ord.size();i++){
      for(auto &p:v[ord[i]].nxt) ord.push_back(p.second);
    }
  }

  void calcCount(){
    assert(ord.size());
    for(int i=(int)ord.size()-1;i>=0;i--){
      v[v[ord[i]].suf].cnt+=v[ord[i]].cnt;
    }
    v[0].cnt=v[1].cnt=0;
  }

  void build(){
    for(int i=0;i<(int)s.size();i++) addchar(i);
    calcOrder();
    calcCount();
  }

};

signed main(void)
{
  PalindromicTree p("apple");
  cout << p.n - 2 << endl;

  return 0;
}
```

ヒストグラム中の最大長方形
```c++
int n, h[100010], l[100010], r[100010], st[100010];
signed main(void)
{
  // i番目の高さがh[i]のヒストグラム中で最大の長方形の面積
  cin >> n;
  REP(i, n) cin >> h[i];
  int t = 0;
  REP(i, n) {
    while(t>0 && h[st[t-1]] >= h[i]) t--;
    l[i] = t == 0 ? 0 : (st[t-1]+1);
    st[t++] = i;
  }
  t = 0;
  for(int i=n-1; i>=0; --i) {
    while(t > 0 && h[st[t-1]] >= h[i]) t--;
    r[i] = t == 0 ? n : st[t-1];
    st[t++] = i;
  }
  ll ret = 0;
  REP(i, n) ret = max(ret, (ll)h[i]*(r[i]-l[i]));
  cout << ret << endl;
  return 0;
}
```

最大長方形
```c++
int n, c[1500][1500], dp[1500][1500], l[1500], r[1500], st[1500];
signed main(void)
{
  // h * w の0,1からなる行列の中で、0のみを使ってできる最大の長方形の面積
  // O(HW)
  int H, W;
  cin >> H >> W;
  REP(i, H) REP(j, W) cin >> c[i][j];

  REP(i, W) {
    int cnt = 1;
    REP(j, H) {
      if(!c[j][i]) {
        dp[j][i] = cnt;
        cnt++;
      } else {
        dp[j][i] = 0;
        cnt = 1;
      }
    }
  }
  ll ret = 0;
  REP(j, H) {
    int t = 0;
    REP(i, W) {
      while(t>0 && dp[j][st[t-1]] >= dp[j][i]) t--;
      l[i] = t == 0 ? 0 : (st[t-1]+1);
      st[t++] = i;
    }
    t = 0;
    for(int i=W-1; i>=0; --i) {
      while(t > 0 && dp[j][st[t-1]] >= dp[j][i]) t--;
      r[i] = t == 0 ? n : st[t-1];
      st[t++] = i;
    }
    REP(i, W) chmax(ret, (ll)dp[j][i]*(r[i]-l[i]));
  }
  cout << ret << endl;
  return 0;
}
```

geometry
```c++
#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-8;
const double INF = 1e12;

//point
typedef complex<double> P;
namespace std {
	bool operator < (const P& a, const P& b) {
		return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
	}
	bool cmp_y(const P &a, const P &b){
		return a.imag() != b.imag() ? a.imag() < b.imag() : a.real() < b.real();
	}
}
double cross(const P& a, const P& b) {
	return imag(conj(a)*b);
}
double dot(const P& a, const P& b) {
	return real(conj(a)*b);
}

// line
struct L : public vector<P> {
	L(const P& a, const P& b) {
		push_back(a); push_back(b);
	}
};

// polygon
typedef vector<P> G;

// circle
struct C {
	P p; double r;
	C(const P& p, double r) : p(p), r(r) {}
};

```

poiint and line
```c++
#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-8;
const double INF = 1e12;

//point
typedef complex<double> P;
namespace std {
	bool operator < (const P& a, const P& b) {
		return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
	}
}
double cross(const P& a, const P& b) {
	return imag(conj(a)*b);
}
double dot(const P& a, const P& b) {
	return real(conj(a)*b);
}
// line
struct L : public vector<P> {
	L(const P& a, const P& b) {
		push_back(a); push_back(b);
	}
};

int ccw(P a, P b, P c) {
  b -= a; c -= a;
  if (cross(b, c) > 0)   return +1;       // counter clockwise
  if (cross(b, c) < 0)   return -1;       // clockwise
  if (dot(b, c) < 0)     return +2;       // c--a--b on line
  if (norm(b) < norm(c)) return -2;       // a--b--c on line
  return 0;								  // a--c--b on line
}

// Lが直線でSが線分、Pが頂点
bool intersectLL(const L &l, const L &m) {
  return abs(cross(l[1]-l[0], m[1]-m[0])) > EPS || // non-parallel
         abs(cross(l[1]-l[0], m[0]-l[0])) < EPS;   // same line
}
bool intersectLS(const L &l, const L &s) {
  return cross(l[1]-l[0], s[0]-l[0])*       // s[0] is left of l
         cross(l[1]-l[0], s[1]-l[0]) < EPS; // s[1] is right of l
}
bool intersectLP(const L &l, const P &p) {
  return abs(cross(l[1]-p, l[0]-p)) < EPS;
}
bool intersectSS(const L &s, const L &t) {
  return ccw(s[0],s[1],t[0])*ccw(s[0],s[1],t[1]) <= 0 &&
         ccw(t[0],t[1],s[0])*ccw(t[0],t[1],s[1]) <= 0;
}
bool intersectSP(const L &s, const P &p) {
  return abs(s[0]-p)+abs(s[1]-p)-abs(s[1]-s[0]) < EPS; // triangle inequality
}

// 射影
P projection(const L &l, const P &p) {
	double t = dot(p-l[0], l[0]-l[1]) / norm(l[0]-l[1]);
	return l[0] + t*(l[0]-l[1]);
}
// 反射
P reflection(const L &l, const P &p) {
	return p + (double)2 * (projection(l, p) - p);
}
double distanceLP(const L &l, const P &p) {
	return abs(p - projection(l, p));
}
double distanceLL(const L &l, const L &m) {
	return intersectLL(l, m) ? 0 : distanceLP(l, m[0]);
}
double distanceLS(const L &l, const L &s) {
	if (intersectLS(l, s)) return 0;
	return min(distanceLP(l, s[0]), distanceLP(l, s[1]));
}
double distanceSP(const L &s, const P &p) {
	const P r = projection(s, p);
	if (intersectSP(s, r)) return abs(r - p);
	return min(abs(s[0] - p), abs(s[1] - p));
}
double distanceSS(const L &s, const L &t) {
	if (intersectSS(s, t)) return 0;
		return min({distanceSP(s, t[0]), distanceSP(s, t[1]), distanceSP(t, s[0]), distanceSP(t, s[1])});
}
P crosspoint(const L &l, const L &m) {
  double A = cross(l[1] - l[0], m[1] - m[0]);
  double B = cross(l[1] - l[0], l[1] - m[0]);
  if (abs(A) < EPS && abs(B) < EPS) return m[0]; // same line
  if (abs(A) < EPS) assert(false); // !!!PRECONDITION NOT SATISFIED!!!
  return m[0] + B / A * (m[1] - m[0]);
}
```

poligon
```c++
#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-8;
const double INF = 1e12;

// polygon
typedef vector<P> G;

P extreme(const vector<P> &po, const L &l) {
  int k = 0;
  for (int i = 1; i < po.size(); ++i)
    if (dot(po[i], l[1]-l[0]) > dot(po[k], l[1]-l[0])) k = i;
  return po[k];
}

enum { OUT, ON, IN };
int contains(const G& po, const P& p) {
  bool in = false;
  for (int i = 0; i < po.size(); ++i) {
  	P a = po[i] - p, b = po[(i+1)%po.size()] - p;
    if (imag(a) > imag(b)) swap(a, b);
    if (imag(a) <= 0 && 0 < imag(b))
      if (cross(a, b) < 0) in = !in;
    if (cross(a, b) == 0 && dot(a, b) <= 0) return ON;
  }
  return in ? IN : OUT;
}

double area2(const G& po) {
	double A = 0;
  	for (int i = 0; i < po.size(); ++i)
    	A += cross(po[i], po[(i+1)%po.size()]);
	//�덷�|�������Ō��ɂ܂Ƃ߂Ċ���
  	return A/2;
}

bool isconvex(const G &p) {
	int n = p.size();
	if(cross(p[0]-p[n-1],p[n-2]-p[n-1]) < 0) return false;
	for(int i = 1; i < n-1; ++i) {
		if(cross(p[i+1]-p[i],p[i-1]-p[i]) < 0) return false;
	}
	return true;

}

G convex_hull(G ps) {
  int n = ps.size(), k = 0;
  sort(ps.begin(), ps.end(), cmp_y);
  G r(2*n);
  for(int i = 0; i < n; i++){
    while(k>1 && cross(r[k-1]-r[k-2],ps[i]-r[k-2]) < -EPS)k--;
    r[k++] = ps[i];
  }
  for(int i = n-2, t = k; i >= 0; i--){
    while(k>t && cross(r[k-1]-r[k-2],ps[i]-r[k-2]) < -EPS)k--;
    r[k++] = ps[i];
  }
  r.resize(k-1);
  return r;
}

// caliper
double convex_diameter(const G &pt) {
	const int n = pt.size();
	if(n <= 1) return 0;
	if(n == 2) return abs(pt[0]-pt[1]);

	int i = 0, j = 0;
	for(int k = 0; k < n; ++k){
		if(!(pt[i] < pt[k])) i = k;
		if(pt[j] < pt[k]) j = k;
	}

	double res = 0;
	int si = i, sj = j;
	while(i != sj || j != si) {
		res = max(res, abs(pt[i]-pt[j]));
		if(cross(pt[(i+1)%n]-pt[i],pt[(j+1)%n]-pt[j]) < 0) i = (i+1)%n;
		else j = (j+1)%n;
	}
	return res;
}

// po��l�Őؒf���č����݂̂��Ԃ�
G convex_cut(const G& po, const L& l) {
  G Q;
  for (int i = 0; i < po.size(); ++i) {
  	P A = po[i], B = po[(i+1)%po.size()];
    if (ccw(l[0], l[1], A) != -1) Q.push_back(A);
  	if (ccw(l[0], l[1], A)*ccw(l[0], l[1], B) < 0) {
  		Q.push_back(crosspoint(L(A, B), l));
  	}
  }
  return Q;
}

//�ŋߓ_�΋���
double closestPair(G p, int flag=1) {
	if(flag) sort(p.begin(), p.end());
	int n = p.size(), s = 0, m=n/2;
	if(n<=1) return INF;
	G b(begin(p), begin(p)+m), c(begin(p)+m, end(p)), e;
	double x = p[m].real(), d=min(closestPair(b, 0), closestPair(c, 0));
	sort(p.begin(), p.end(), cmp_y);
	for(int i=0; i<n; ++i) {
		if(abs(real(p[i])-x) >= d) continue;
		for(int j=0; j<e.size(); ++j) {
			if(imag(p[i]-e[e.size()-1-j]) >= d) break;
			d = min(d, abs(p[i]-e[e.size()-1-j]));
		}
		e.push_back(p[i]);
	}
	return d;
}
```

circle
```c++
#include <bits/stdc++.h>
using namespace std;

// circle
struct C {
	P p; double r;
	C(const P& p, double r) : p(p), r(r) {}
};

int intersectCC(const C& a, const C& b) {
	double dist = sqrt(norm(a.p-b.p)), r1 = a.r + b.r, r2 = abs(a.r - b.r);
	if(r1 < dist) return 4;		//�ڂ��Ȃ�
	if(dist == r1) return 3;	//�O��
	if(r2 < dist && dist < r1) return 2; //������
	if(dist == r2) return 1; //����
	return 0;	//����
}

vector<P> crossPointCL(C c, L l) {
	double d = distanceLP(l, c.p), r = c.r;
	P m = projection(l, c.p);
	P x = sqrt(r*r-d*d)/abs(l[1]-l[0])*(l[1]-l[0]);
	vector<P> ret(2,m);
	ret[0] -= x;
	ret[1] += x;
	sort(ret.begin(), ret.end());	//!!!
	return ret;
}

vector<P> crossPointCC(C a, C b) {
	double d = abs(a.p-b.p);
	double t = (a.r*a.r-b.r*b.r+d*d)/2/d, h = sqrt(a.r*a.r-t*t);
	P m = t/abs(b.p-a.p)*(b.p-a.p)+a.p;
	P n = n_vector(a.p-b.p);
	vector<P> ret(2, m);
	ret[0] -= h*n;
	ret[1] += h*n;
	sort(ret.begin(), ret.end());	//!!!
	return ret;
}

vector<P> tangentLC(P p, C c) {
	C c2 = C((p+c.p)/2.0, abs(p-c.p)/2.0);
	return crossPointCC(c, c2);
}

vector<P> commonTangent(C a, C b) {
	vector<P> ret, cp;
	if(a.r == b.r) {
		P n = n_vector(b.p-a.p);
		ret.push_back(P{a.p+a.r*n});
		ret.push_back(P{a.p-a.r*n});
	}
	P i = (a.p*b.r+b.p*a.r)/(a.r+b.r);
  	if(abs(a.p-b.p) > a.r+b.r){
    	cp = tangentLC(i,a);
    	for(int i = 0; i < 2; ++i) ret.push_back(cp[i]);
    	if(a.r != b.r){
      		P e = (a.p*b.r-b.p*a.r)/(b.r-a.r);
      		cp = tangentLC(e,a);
      		for(int i = 0; i < 2; ++i) ret.push_back(cp[i]);
    	}
  	}else if(abs(a.p-b.p) == a.r+b.r){
    	cp = tangentLC(i,a);
    	ret.push_back(cp[0]);
    	if(a.r != b.r){
    		P e = (a.p*b.r-b.p*a.r)/(b.r-a.r);
      		cp = tangentLC(e,a);
      		for(int i = 0; i < 2; ++i) ret.push_back(cp[i]);
    	}
  	}else if(abs(a.p-b.p) > abs(a.r-b.r)){
    	if(a.r != b.r){
    		P e = (a.p*b.r-b.p*a.r)/(b.r-a.r);
      		cp = tangentLC(e,a);
      		for(int i = 0; i < 2; ++i) ret.push_back(cp[i]);
    	}
  	}else if(abs(a.p-b.p) == abs(a.r-b.r)){
    	P e = (a.p*b.r-b.p*a.r)/(b.r-a.r);
    	cp = tangentLC(e,a);
    	ret.push_back(cp[0]);
  	}
	sort(ret.begin(), ret.end());
  	return ret;
}

/*
3点が与えられたときに円を求める
返り値は{中心のx座標、y座標、半径}
3点が直線上に並んでいるときは{0, 0, -1}を返す
*/
C calcCircle(int x1, int y1, int x2, int y2, int x3, int y3) {
  long ox, oy, a, b, c, d;
  long r1, r2, r3;

  a = x2 - x1;
  b = y2 - y1;
  c = x3 - x1;
  d = y3 - y1;

  int cx, cy, r;
  if ((a && d) || (b && c)) {
    ox = x1 + (d * (a * a + b * b) - b * (c * c + d * d)) / (a * d - b * c) / 2;
    if (b) {
      oy = (a * (x1 + x2 - ox - ox) + b * (y1 + y2)) / b / 2;
    } else {
      oy = (c * (x1 + x3 - ox - ox) + d * (y1 + y3)) / d / 2;
    }
    r1 = sqrt((ox - x1) * (ox - x1) + (oy - y1) * (oy - y1));
    r2 = sqrt((ox - x2) * (ox - x2) + (oy - y2) * (oy - y2));
    r3 = sqrt((ox - x3) * (ox - x3) + (oy - y3) * (oy - y3));
    cx = ox;
    cy = oy;
    r = (r1 + r2 + r3) / 3;
    return {P{cx, cy}, r};
  }

  return {P{0, 0}, -1};
}

```
