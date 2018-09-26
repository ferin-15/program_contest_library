// BEGIN CUT
// N以下の数を求める桁DP
dp[0][0] = 1;
REP(i, n) REP(j, 2) {
  int lim = j?9:s[i]-'0';
  REP(d, lim+1) {
    (dp[i+1][j || d<lim] += dp[i][j]) %= MOD;
  }
}

int ans = 0;
REP(i, 2) (ans += dp[n][i]) %= MOD;
cout << ans << endl;
// END CUT