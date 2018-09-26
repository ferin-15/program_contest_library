// dp[i][j] = i個をj個のdisjointで全てを覆うようなグループに分割するパターン数
VVI dp(n+1, VI(n+1));
REP(i, n+1) {
  dp[i][0] = 1;
  FOR(j, 1, i+1) {
    dp[i][j] = (dp[i-1][j]*j + dp[i-1][j-1]) % MOD;
  }
}
