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

class LCA {
private:
  const int n = 0;
  const int log2_n = 0;
  VVI par;
  vector<vector<PII>> g;
  VI depth, d;

  // parとdを構築する
  void dfs(int v, int p, int dist, int n_depth) {
    par[0][v] = p; d[v] = dist; depth[v] = n_depth;
    for (auto e : g[v]) {
      if (e.first != p) dfs(e.first, v, dist + e.second, n_depth+1);
    }
  }

public:
  LCA(int n_=1e5) :
    n(n_), log2_n(log2(n)+1), par(log2_n, VI(n)), g(n, vector<PII>()), depth(n), d(n) {}
  // u-vに重みcostの辺を張る
  void add_edge(int u, int v, int cost) { g[u].PB({v, cost}); g[v].PB({u, cost}); }
  // rootを根としてparとdを構築
  void build(int root = 0) {
    dfs(root, -1, 0, 0);
    REP(k, log2_n-1) {
      REP(v, n) {
        if(par[k][v] < 0) par[k+1][v] = -1;
        else par[k+1][v] = par[k][par[k][v]];
      }
    }
  }
  // uとvのlcaを返す
  int get(int u, int v) {
    if (depth[u] > depth[v]) std::swap(u, v);
    for (int k = 0; k < log2_n; k++) {
      if ((depth[v] - depth[u]) >> k & 1) {
        v = par[k][v];
      }
    }
    if (u == v) return u;
    for (int k = log2_n - 1; k >= 0; k--) {
      if (par[k][u] != par[k][v]) {
        u = par[k][u];
        v = par[k][v];
      }
    }
    return par[0][u];
  }
  // uとvの距離を返す
  int length(int u, int v) {
    int lca = get(u, v);
    return d[u] + d[v] - 2*d[lca];
  }
  void debug() {
    cout << depth << endl << d << endl;
  }
};

signed main(void)
{
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  cin >> n;
  LCA graph(n);
  REP(i, n-1) {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    graph.add_edge(a, b, c);
  }
  graph.build();
  // graph.debug();
  int q, k;
  cin >> q >> k; k--;
  REP(i, q) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    cout << graph.length(a, k) + graph.length(b, k) << endl;
  }

  return 0;
}
