int h, w;
string s[10010];
bool used[10010][10010];

void dfs(int x, int y) {
  used[y][x] = true;

  REP(i, 4) {
    int nx = x + dx[i], ny = y + dy[i];
    if(!used[ny][nx] && IN(0, w, nx) && IN(0, h, ny) && s[ny][nx] == '#') {
      dfs(nx, ny);
      d[ny][nx] = d[y][x] + 1;
    }
  }
}
