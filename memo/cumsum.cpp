const int maxh = 35, maxw = 35;
int csum[maxh][maxw];
void init(VVI vec) {
  assert(vec.size());
  REP(i, vec.size()) REP(j, vec[0].size()) {
    if(!i && !j) csum[i][j] = vec[i][j];
    else if(!i) csum[i][j] = csum[i][j-1] + vec[i][j];
    else if(!j) csum[i][j] = csum[i-1][j] + vec[i][j];
    else csum[i][j] = csum[i-1][j] + csum[i][j-1] - csum[i-1][j-1] + vec[i][j];
  }
}
// 閉区間, 0-indexedで矩形範囲の合計
int cumsum(int sx, int sy, int gx, int gy) {
  if(!sx && !sy) return csum[gy][gx];
  if(!sx) return csum[gy][gx] - csum[sy-1][gx];
  if(!sy) return csum[gy][gx] - csum[gy][sx-1];
  return csum[gy][gx] - csum[gy][sx-1] - csum[sy-1][gx] + csum[sy-1][sx-1];
}
