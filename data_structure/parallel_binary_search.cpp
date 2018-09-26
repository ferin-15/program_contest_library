/**
* @file parallel_binary_search.cpp
* @brief 並行二分探索
* @detail https://agc002.contest.atcoder.jp/tasks/agc002_d でverify
*/

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define int ll
using PII = pair<int, int>;
template <typename T> using V = vector<T>;
template <typename T> using VV = vector<V<T>>;
template <typename T> using VVV = vector<VV<T>>;

#define FOR(i, a, n) for (ll i = (ll)a; i < (ll)n; ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(x) x.begin(), x.end()
#define PB push_back

const ll INF = (1LL<<60);
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

/**
* @brief 並行二分探索
* @details クエリ数,クエリ範囲,init,add,check,値の最小化or最大化 を指定\n
* コンストラクタでこれをした後search()を呼ぶ
*/
struct parallelBinarySearch {
  struct query_{
    int x, y, z;
    int lb, mid, ub, idx;
    bool operator<(const query_& a){ return mid<a.mid; }
  };
  //! クエリの集合
  V<query_> query;       
  //! 二分探索する対象の区間は[llim, ulim)
  int llim, ulim;
  //! 値の最小化であればminnimum=true、最大化であればminnumum=false 
  bool minnimum;               
  //! 二分探索1段ごとに行う初期化
  function<void(void)> init;  
  //! j番目を加えるときの処理
  function<void(int)>  add;   
  //! 現在の状態でそのクエリについてtrueかfalseかを返す
  function<bool(int)> check;
  //! search関数のループで探索する対象の集合
  V<int> loop_index;

  parallelBinarySearch(int q, int llim_, int ulim_, bool mi=true, 
    auto init_, auto add_, auto check_, auto loop) 
    : llim(llim_), ulim(ulim_), minnimum(mi),
      init(init_), add(add_), check(check_), loop_index(loop) 
  { 
    query.resize(q);
    REP(i, q) {
      query[i].lb = mi?llim-1:llim;
      query[i].ub = mi?ulim-1:ulim;
      query[i].mid = (query[i].lb+query[i].ub)/2;
      query[i].idx = i;
    }
  }

  /**
  * @brief 並列二分探索を実行 O((M+Q)*logM)
  * @return V<int> res[i]=(クエリiの結果)
  * @details クエリごとに処理を行うのではなく共通にすることで高速化
  */
  V<int> search() {  
    int l = log2(ulim-llim) + 1;
    REP(i, l) {
      sort(ALL(query));
      // デバッグ用
      // REP(i, query.size()) {
      //   cout << "(" << query[i].idx << "," << query[i].lb << "," << query[i].mid << "," << query[i].ub << ") ";
      // }
      // cout << endl;
      int idx = 0;
      for(auto j: loop_index) {
        add(j);
        while(idx < query.size() && query[idx].mid==j) {
          if(query[idx].ub-query[idx].lb <= 1) {
            query[idx].mid = query[idx].ub;
            idx++;
            continue;
          }
          if(check(query[idx].idx)) {
            if(minnimum) query[idx].ub = query[idx].mid;
            else query[idx].lb = query[idx].mid;
          } else {
            if(minnimum) query[idx].lb = query[idx].mid;
            else query[idx].ub = query[idx].mid;
          }
          query[idx].mid = (query[idx].lb + query[idx].ub)/2;
          idx++;
        }
      }
    }

    V<int> res(query.size());
    REP(i, query.size()) {
      if(minnimum) res[query[i].idx] = query[i].ub;
      else res[query[i].idx] = query[i].lb;
    }
    return res;
  }
};
// END CUT

class UnionFind {
public:
  const static int MAX_N = 100010;
  int par[MAX_N];
  int s[MAX_N];
  UnionFind() { init(); }
  UnionFind(int n) { init(n); }
  void init() { for(int i=0; i<MAX_N; ++i) par[i] = i, s[i] = 1; }
  void init(int n) { for(int i=0; i<n; ++i) par[i] = i, s[i] = 1; }
  int find(int x) {
    if(par[x] == x) return x;
    return par[x] = find(par[x]);
  }
  void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) return;
    if(s[x] < s[y]) par[x] = y, s[y] = s[x] + s[y];
    else par[y] = x, s[x] = s[x] + s[y];
  }
  bool same(int x, int y) { return find(x) == find(y); }
  int size(int x) { return s[find(x)]; }
};
UnionFind uf;

signed main(void)
{
  int n, m;
  cin >> n >> m;
  V<int> a(m), b(m);
  REP(i, m) cin >> a[i] >> b[i], a[i]--, b[i]--;
  int q;
  cin >> q;
  V<int> x(q), y(q), z(q);
  REP(i, q) cin >> x[i] >> y[i] >> z[i], x[i]--, y[i]--;

  auto init = [&]() {
    uf.init(n);
  };
  auto add = [&](int i) {
    uf.unite(a[i], b[i]);
  };
  auto check = [&](int i) {
    if(uf.same(x[i], y[i])) {
      return uf.size(x[i]) >= z[i];
    } else {
      return uf.size(x[i]) + uf.size(y[i]) >= z[i];
    }
  };
  parallelBinarySearch pbs(q, 0, m, init, add, check);

  auto res = pbs.search();
  REP(i, q) cout << res[i]+1 << endl;
  
  return 0;
}

