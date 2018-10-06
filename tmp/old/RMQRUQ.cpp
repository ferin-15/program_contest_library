#define __USE_MINGW_ANSI_STDIO 0
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
// #define int ll
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

// 区間更新、区間最小の遅延セグメントツリー
struct RMQRUQ {
  int n;
  vector<int> dat, lazy;

  RMQRUQ(){}
  RMQRUQ(int n_) {
    n = 1; while(n < n_) n *= 2;
    dat.assign(n*2, INT_MAX);
    lazy.assign(n*2, INT_MAX);
  }

  void eval(int len, int k) {
    if(lazy[k] == INT_MAX) return;
    if(k*2+1 < n*2-1) {
      lazy[2*k+1] = lazy[k];
      lazy[2*k+2] = lazy[k];
    }
    dat[k] = lazy[k];
    lazy[k] = INT_MAX;
  }

  // [a, b)
  ll update(int a, int b, ll x, int k, int l, int r) {
    eval(r-l, k);
    if(b <= l || r <= a) return dat[k];
    if(a <= l && r <= b) {
      lazy[k] = x;
      return lazy[k];
    }
    return dat[k] = min(update(a, b, x, 2*k+1, l, (l+r)/2), update(a, b, x, 2*k+2, (l+r)/2, r));
  }
  ll update(int a, int b, ll x) { return update(a, b, x, 0, 0, n); }

  // [a, b)
  ll query(int a, int b, int k, int l, int r) {
    eval(r-l, k);
    if(b <= l || r <= a) return INT_MAX;
    if(a <= l && r <= b) return dat[k];
    ll vl = query(a, b, 2*k+1, l, (l+r)/2);
    ll vr = query(a, b, 2*k+2, (l+r)/2, r);
    return min(vl, vr);
  }
  ll query(int a, int b) { return query(a, b, 0, 0, n); }
};

signed main(void)
{
  int n, q;
  cin >> n >> q;
  RMQRUQ seg(n);
  REP(i, q) {
    int type;
    cin >> type;
    if(type == 0) {
      int s, t, x;
      cin >> s >> t >> x;
      seg.update(s, t+1, x);
    } else {
      int s, t;
      cin >> s >> t;
      cout << seg.query(s, t+1) << endl;
    }
  }

  return 0;
}
