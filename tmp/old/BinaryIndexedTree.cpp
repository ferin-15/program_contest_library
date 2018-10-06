#define __USE_MINGW_ANSI_STDIO 0
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define int ll
using VI = vector<int>;
using VVI = vector<VI>;
using PII = pair<int, int>;

#define FOR(i, a, n) for (ll i = (ll)a; i < (ll)n; ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(x) x.begin(), x.end()
#define PB push_back

const ll LLINF = (1LL<<60);
const int INF = (1LL<<30);
const int MOD = 1000000007;

template <typename T> T &chmin(T &a, const T &b) { return a = min(a, b); }
template <typename T> T &chmax(T &a, const T &b) { return a = max(a, b); }
template <typename T> bool IN(T a, T b, T x) { return a<=x&&x<b; }
template<typename T> T ceil(T a, T b) { return a/b + !!(a%b); }
template<class S,class T>
ostream &operator <<(ostream& out,const pair<S,T>& a){
  out<<'('<<a.first<<','<<a.second<<')';
  return out;
}
template<class T>
ostream &operator <<(ostream& out,const vector<T>& a){
  out<<'[';
  REP(i, a.size()) {out<<a[i];if(i!=a.size()-1)out<<',';}
  out<<']';
  return out;
}

int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

// Binary Indexed Tree
// 0-indexed
template <typename T>
class BIT {
private:
  vector<T> bit;
  // 単位元
  int neutral = 0;
  // 更新クエリ, 区間クエリ
  function<T(T,T)> f = [](const T l, const T r) { return l+r; };
  function<T(T,T)> g = [](const T l, const T r) { return l+r; };
public:
  // 初期化
  BIT(int n = 1e5, int neu = 0,
    function<T(T,T)> _f = [](const T l, const T r) { return l+r; },
    function<T(T,T)> _g = [](const T l, const T r) { return l+r; })
  {
    init(n, neu, _f, _g);
  }
  void init(int n = 1e5, int neu = 0,
    function<T(T,T)> _f = [](const T l, const T r) { return l+r; },
    function<T(T,T)> _g = [](const T l, const T r) { return l+r; })
  {
    neutral = neu; f = _f; g = _g;
    bit.assign(n+5, neutral);
  }
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

int w[100010];
signed main() {
  int n, k;
  cin >> n >> k;
  REP(i, n) cin >> w[i];

  BIT<int> bit(1e6+5);
  REP(i, n) {
    if(w[i] > 0) {
      if(bit.query(1e6+4) - bit.query(w[i]-1) < k) {
        bit.update(w[i], 1);
      }
    } else {
      w[i] = -w[i];
      if(bit.query(w[i]) - bit.query(w[i]-1) >= 1) {
        bit.update(w[i], -1);
      }
    }
  }
  cout << bit.query(1e6+4) << endl;

  return 0;
}
