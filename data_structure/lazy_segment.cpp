/**
* @file lazy_segment.cpp
* @brief 遅延セグメントツリー
* @detail verify: 色々
* @author ferin
*/

/**
* @brief セグメント木
* @details 抽象化した遅延セグメント木\n
* 区間更新区間max d1=d0=INT_MAX f=max(a,b) g=h=(b==INT_MAX?a:b)\n
* 区間加算区間和  d1=d0=0 f=g=h=a+b p=a*b\n
* 区間加算区間min d1=d0=0 f=min(a,b) g=h=a+b\n
* 区間更新区間和  d1=d0=0 f=a+b g=h=(b==0?a:b) p=a*b\n
* 区間xor区間和   d1=d0=0 f=a+b g=(b>=1?b-a:a) h=a^b p=a*b
*/
template <typename T, typename E>
struct lazySegTree {
  using F = function<T(T,T)>;
  using G = function<T(T,E)>;
  using H = function<E(E,E)>;
  using P = function<E(E,int)>;
  F f; G g; H h; P p; T d1; E d0;
  int n;
  vector<T> dat;
  vector<E> lazy;

  lazySegTree(){}
  lazySegTree(int n_, F f_, G g_, H h_, 
    T d1_, E d0_, P p_=[](E a, int b){return a;})
    : f(f_), g(g_), h(h_), p(p_), d1(d1_), d0(d0_) 
  {
    n = 1; while(n < n_) n *= 2;
    dat.assign(n*2-1, d1);
    lazy.assign(n*2-1, d0);
  }
  void build(vector<T> v) {
    REP(i, v.size()) dat[i+n-1] = v[i];
    for(int i=n-2; i>=0; --i) dat[i] = f(dat[i*2+1], dat[i*2+2]);
  }

  // 区間の幅がlenの節点kについて遅延評価
  inline void eval(int len, int k) {
    if(lazy[k] == d0) return;
    if(k*2+1 < n*2-1) {
      lazy[2*k+1] = h(lazy[k*2+1], lazy[k]);
      lazy[2*k+2] = h(lazy[k*2+2], lazy[k]);
    }
    dat[k] = g(dat[k],p(lazy[k],len));
    lazy[k] = d0;
  }
  // [a, b)
  T update(int a, int b, E x, int k, int l, int r) {
    eval(r-l, k);
    if(b <= l || r <= a) return dat[k];
    if(a <= l && r <= b) {
      lazy[k] = h(lazy[k], x);
      return g(dat[k], p(lazy[k],r-l));
    }
    return dat[k] = f(update(a, b, x, 2*k+1, l, (l+r)/2),
                      update(a, b, x, 2*k+2, (l+r)/2, r));
  }
  T update(int a, int b, E x) { return update(a, b, x, 0, 0, n); }
  // [a, b)
  T query(int a, int b, int k, int l, int r) {
    eval(r-l, k);
    if(a <= l && r <= b) return dat[k];
    bool left = !((l+r)/2 <= a || b <= l), right = !(r <= 1 || b <= (l+r)/2);
    if(left&&right) return f(query(a, b, 2*k+1, l, (l+r)/2), query(a, b, 2*k+2, (l+r)/2, r));
    if(left) return query(a, b, 2*k+1, l, (l+r)/2);
    return query(a, b, 2*k+2, (l+r)/2, r);
  }
  T query(int a, int b) { return query(a, b, 0, 0, n); }
  // デバッグ出力
  void debug() {
    cout << "---------------------" << endl;
    int cnt = 0;
    for(int i=1; i<=n; i*=2) {
      REP(j, i) {
        cout << "(" << dat[cnt] << "," << lazy[cnt] << ") "; 
        cnt++;
      }
      cout << endl;
    }
    cout << "---------------------" << endl;
  }
};