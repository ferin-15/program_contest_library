//#define __USE_MINGW_ANSI_STDIO 0
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
  // [a, b)
  void add(int a, int b, int x) {add(a, b, x, 0, 0, n);}
  void add(int a, int b, int x, int k, int l, int r) {
    if(r <= a || b <= l) return;
    if(a <= l && r <= b) lazya[k] += x;
    else {
      add(a, b, x, k*2+1, l, (l+r)/2);
      add(a, b, x, k*2+2, (l+r)/2, r);
      lazym[k] = max(lazym[k*2+1]+lazya[k*2+1],
                      lazym[k*2+2]+lazya[k+2+2]);
    }
  }
  // [a, b)
  int query(int a, int b) {return query(a, b, 0, 0, n);}
  int query(int a, int b, int k, int l, int r) {
    if(r <= a || b <= l) return init_;
    if(a <= l && r <= b) return lazym[k] + lazya[k];
    int vl = query(a, b, k*2+1, l, (l+r)/2),
        vr = query(a, b, k*2+2, (l+r)/2, r);
    return max(vl, vr)+lazya[k];
  }
};

starrysky seg(100000);
signed main(void)
{
  int n;
  cin >> n;
  REP(i, n) {
    int s, t;
    cin >> s >> t;
    --s;
    seg.add(s, t, 1);
  }
  cout << seg.query(0, seg.n) << endl;

  return 0;
}
