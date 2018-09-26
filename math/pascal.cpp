ll combi(ll n, ll k) {
  static ll c[50][50];
  if(c[0][0] == 0) {
    REP(i, n) {
      c[i][0] = c[i][i] = 1;
      FOR(j, 1, i) c[i][j] = c[i-1][j] + c[i-1][j-1];
    }
  }
  return c[n][k];
}
