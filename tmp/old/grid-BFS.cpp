//grid-BFS
string s[MAX_N];
int h, w, sx, sy, gx, gy, d[10010][10010];

int bfs() {
  queue<PII> que;
  REP(i, h) REP(j, w) d[i][j] = INF;
  que.push(PII{sx, sy});
  d[sy][sx] = 0;

  while(que.size()) {
    PII p = que.front(); que.pop();
    if(p.first == gx && p.second == gy) break;
    REP(i, 4) {
      int nx = p.first + dx[i], p.second + dy[i];
      if(IN(0, w, nx) && IN(0, h, ny) && s[i][j] != '#' && d[ny][nx] == INF) {
        que.push(PII{nx, ny});
        d[ny][nx] = d[p.first][p.second] + 1;
      }
    }
  }

  return d[gy][gx];
}
