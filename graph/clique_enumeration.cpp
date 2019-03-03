// AOJ 2306 Rabbit Party
// クリーク全列挙
int n, m, ans;
int g[105][105];

void dfs(VI &v) {
  if(v.size() >= 2) {
    int tmp = 0;
    REP(i, v.size()) {
      int t = INF;
      REP(j, v.size()) if(i != j) {
        chmin(t, g[v[i]][v[j]]);
      }
      tmp += t;
    }
    chmax(ans, tmp);
  }

  int last = v.back();
  FOR(i, last+1, n) {
    bool ok = true;
    for(int j: v) {
      if(g[i][j] == 0) {
        ok = false;
        break;
      }
    }
    if(ok) {
      v.PB(i);
      dfs(v);
      v.pop_back();
    }
  }
}