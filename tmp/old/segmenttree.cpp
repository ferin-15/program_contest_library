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

template<class T>
class segmentTree {
public:
  int size_;
  vector<T> dat;
  // 単位元
  T init__ = INT_MAX;
  // 更新部分
  function<T(T,T)> f = [](T l, T r) {return l;};
  // クエリ部分
  function<T(T,T)> g = [](T l, T r) {return min(l,r);};

  // 初期化
  segmentTree(int n=1e5, int ini=INT_MAX,
    function<int(int,int)> _f = [](int l, int r) {return l;},
    function<int(int,int)> _g = [](int l, int r) {return min(l,r);})
  {
    init(n, ini, _f, _g);
  }
  void init(int n=1e5, int ini=INT_MAX,
    function<int(int,int)> _f = [](int l, int r) {return l;},
    function<int(int,int)> _g = [](int l, int r) {return min(l,r);})
  {
    f = _f; g = _g;
    for(size_ = 1; size_ < n; size_ *= 2);
    dat.assign(2*size_-1, init__);
  }

  void update(int k, T a) {
    k += size_ - 1;
    dat[k] = f(dat[k], a);
    while(k > 0) {
      k = (k-1) / 2;
      dat[k] = g(dat[k*2+1], dat[k*2+2]);
    }
  }
  T query(int a, int b, int k, int l, int r) {
    if(r <= a || b <= l) return init__;
    if(a <= l && r <= b) return dat[k];
    return g(query(a, b, 2*k+1, l, (l+r)/2),
                query(a, b, 2*k+2, (l+r)/2, r));
  }
  T query(int a, int b) {return query(a, b, 0, 0, size_);}
};

signed main(void)
{


  return 0;
}
