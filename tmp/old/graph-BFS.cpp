VI g[100010];
int s, g, d[100010];

int bfs() {
  queue<int> que;
  REP(i, n) d[i] = INF;
  que.push(s);
  d[s] = 0;

  while(que.size()) {
    int p = que.front(); que.pop();
    if(p == g) break;
    REP(i, 4) {
      if(d[g[p][i]] == INF) {
        que.push(g[p][i]);
        d[g[p][i]] = d[p] + 1;
      }
    }
  }
  return d[g];
}
