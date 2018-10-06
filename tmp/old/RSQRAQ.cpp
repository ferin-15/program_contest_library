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

// 区間加算区間和
struct RSQRAQ {
  int n;
  vector<ll> dat, lazy;

  RSQRAQ(){}
  RSQRAQ(int n_) {
    n = 1; while(n < n_) n *= 2;
    dat.assign(n*2, 0);
    lazy.assign(n*2, 0);
  }

  void eval(int len, int k) {
    if(lazy[k] == 0) return;
    if(k*2+1 < n*2-1) {
      lazy[2*k+1] += lazy[k];
      lazy[2*k+2] += lazy[k];
    }
    dat[k] += lazy[k]*len;
    lazy[k] = 0;
  }

  // [a, b)
  ll update(int a, int b, ll x, int k, int l, int r) {
    eval(r-l, k);
    if(b <= l || r <= a) return dat[k];
    if(a <= l && r <= b) {
      lazy[k] += x;
      return dat[k] + lazy[k]*(r-l);
    }
    return dat[k] = update(a, b, x, 2*k+1, l, (l+r)/2) + update(a, b, x, 2*k+2, (l+r)/2, r);
  }
  ll update(int a, int b, ll x) { return update(a, b, x, 0, 0, n); }

  // [a, b)
  ll query(int a, int b, int k, int l, int r) {
    eval(r-l, k);
    if(b <= l || r <= a) return 0;
    if(a <= l && r <= b) return dat[k];
    ll vl = query(a, b, 2*k+1, l, (l+r)/2);
    ll vr = query(a, b, 2*k+2, (l+r)/2, r);
    return vl + vr;
  }
  ll query(int a, int b) { return query(a, b, 0, 0, n); }
};

signed main(void)
{
  int n, q;
  cin >> n >> q;
  RSQRAQ seg(n);
  REP(i, q) {
    int type;
    cin >> type;
    if(type == 0) {
      int s, t, x;
      cin >> s >> t >> x;
      s--;
      seg.update(s, t, x);
      // REP(i, n) {
      //   cout << seg.query(i, i+1) << " ";
      // }
      // cout << endl;
    } else {
      int s, t;
      cin >> s >> t;
      s--;
      cout << seg.query(s, t) << endl;
    }
  }

  return 0;
}
