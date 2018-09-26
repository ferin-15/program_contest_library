/**
* @file BIT.cpp
* @brief binary index tree
* @detail verify: 色々
* @author ferin
*/

// BEGIN CUT
/**
* @brief binary index tree
* @details 抽象化したBIT
*/
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
  // [0,i]に対する区間クエリ
  T query(int i) {
    T ret = neutral;
    for(int x = i+1; x > 0; x -= x & -x) ret = g(ret, bit[x]);
    return ret;
  }
  // 合計がw以上の最小の位置
  // ToDo: http://hos.ac/slides/20140319_bit.pdf p72
  int lower_bound(T w) {
    int lb = -1, ub = bit.size();
    while(ub-lb>1) {
      int mid = (lb+ub)/2;
      if(query(mid) >= w) ub = mid;
      else lb = mid;
    }
    return ub;
  }
};
// END CUT
