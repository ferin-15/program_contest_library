// BEGIN CUT
struct b_match {
  static const int MAX_V = 1000;
  int V;
  VI G[MAX_V], match;
  vector<bool> used;

  // V要素で初期化
  b_match(int v_=MAX_V) : V(v_) { match.resize(v_); used.resize(v_); }
  // 辺u-vを追加する
  void add_edge(int u, int v) { G[u].PB(v); G[v].PB(u); }
  // 増加パスの探索
  bool dfs(int v) {
    used[v] = true;
    REP(i, G[v].size()) {
      int u = G[v][i], w = match[u];
      if(w < 0 || !used[w] && dfs(w)) {
        match[v] = u;
        match[u] = v;
        return true;
      }
    }
    return false;
  }
  // 二部マッチングを計算
  int matching() {
    int res = 0;
    match.assign(V, -1);
    REP(v, V) {
      if(match[v] < 0) {
        used.assign(V, false);
        if(dfs(v)) res++;
      }
    }
    return res;
  }
};
// END CUT