template <typename T>
struct BIT {
  vector<T> bit;
  // 単位元, 要素数以下の最大の2べき
  int neutral = 0, n;
  // 更新クエリ, 区間クエリ
  function<T(T,T)> f = [](const T l, const T r) { return l+r; },
                   g = [](const T l, const T r) { return l+r; };

  BIT(int n_ = 1e5) { init(n_); }
  void init(int n_) { 
    bit.assign(n_+1, neutral); 
    n=1; while(n*2 < n_+1) n*=2;
  }
  void update(int i, T w) {
    for(int x = i+1; x < bit.size(); x += x&-x) bit[x] = g(bit[x], w);
  }
  // [0,i]
  T query(int i) {
    T ret = neutral;
    for(int x = i+1; x > 0; x -= x & -x) ret = f(ret, bit[x]);
    return ret;
  }
  // 合計がw以上の最小の位置 ToDo:verify
  int lower_bound(T w) {
    if(w <= 0) return 0;
    int idx = 0;
    for(int i=n; i>0; i>>=1) {
      if(idx+i < bit.size() && bit[idx+i] <= w) {
        w -= bit[idx+i];
        idx += i;
      }
    }
    return idx;
  }
};