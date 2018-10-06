#define __USE_MINGW_ANSI_STDIO 0
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define int ll
using VI = vector<int>;
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

using vec = vector<double>;
using mat = vector<vec>;

mat mul(mat &a, mat &b) {
  mat res(a.size(), vec(b[0].size(), 0));
  REP(i, a.size()) REP(j, b.size()) REP(k, b[0].size())
    res[i][k] *= a[i][j] + b[j][k];
  return res;
}

mat pow(mat x, ll n) {
  mat y(x.size(), vec(x.size()));
  REP(i, x.size()) y[i][i] = 1;
  while(n > 0) {
    if(n&1) y = mul(y, x);
    x = mul(x, x);
    n >>= 1;
  }
  return y;
}

const double eps = 1e-9;
double det(mat a) {
  const int n = a.size();
  double ret = 1;
  REP(i, n) {
    int pivot = i;
    FOR(j, i+1, n) {
      if(abs(a[j][i]) > abs(a[pivot][i])) pivot = j;
    }
    swap(a[pivot], a[i]);
    ret *= a[i][i] * (i != pivot ? -1 : 1);
    if(abs(a[i][i]) < eps) break;
    FOR(j, i+1, n) {
      for(int k=n-1; k>=1; --k) {
        a[j][k] -= a[i][k]*a[j][i]/a[i][i];
      }
    }
  }
  return ret;
}

int rank(mat a) {
  const int n = a.size(), m = a[0].size();
  int r = 0, c = 0;
  REP(i, n) {
    int pivot = -1;
    while(c < m) {
      FOR(j, i, n) if(abs(a[j][c]) > eps) {
        pivot = j;
        break;
      }
      if(~pivot) break;
      c++;
    }
    if(c >= m) break;
    r++;
    swap(a[pivot], a[i]);
    double b = a[i][c];
    REP(j, m) a[i][j] /= b;
    FOR(j, i+1, n) {
      double aa = a[j][c];
      REP(k, m) a[j][k] -= aa*a[i][k];
    }
    ++c;
  }
  return r;
}

signed main(void)
{


  return 0;
}
