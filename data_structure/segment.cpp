/**
* @file segment.cpp
* @brief セグメント木
* @detail verify: 色々
* @author ferin
*/

// BEGIN CUT
/**
* @brief セグメント木
* @details 遅延評価をしない普通のセグメント木\n
* 点更新区間min d=INF, f=min(a,b), g=b\n
* 点更新区間max d=-INF, f=max(a,b), g=b\n
* 点加算区間和  d=0, f=a+b, g+=b
*/
template <typename T>
class segTree {
public:
  int n;
  vector<T> dat;
  T d;
  function<T(T,T)> f;
  function<T(T,T)> g;

  segmentTree(int n_=1e5) { init(n_); }
  void init(int n_=1e5, auto f_, auto g_, T d_) 
    : f(f_), g(g_), d(d_)
  {
    n = 1;
    while(n < n_) n *= 2;
    x.assign(sz*2, M::id()); 
  }

  // [a, b)
  T query(int a, int b, int k, int l, int r) {
    if(r <= a || b <= l) return d;
    if(a <= l && r <= b) return dat[k];
    return f(query(a, b, 2*k+1, l, (l+r)/2),
              query(a, b, 2*k+2, (l+r)/2, r));
  }
  T query(int a, int b) {return query(a, b, 0, 0, sz);}
  // 点更新
  void update(int i, const T &val) {
    i += sz-1;
    dat[i] = g(dat[i], val);
    while(i > 0) {
      i = (i-1)/2;
      dat[i] = f(dat[i*2+1], dat[i*2+2]);
    }
  }
};
// END CUT