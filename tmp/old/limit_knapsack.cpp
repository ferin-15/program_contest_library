int dp[10010];
int v[105], w[105], m[105];
signed main(void)
{
  int n, W;
  cin >> n >> W;
  REP(i, n) cin >> v[i] >> w[i] >> m[i];
  REP(i, n) {
    int num = m[i];
    for(int k=1; num > 0; k <<= 1) {
      int mu = min(k, num);
      //ダブリング
      for(int j=W; j>=w[i]*mu; --j) {
        dp[j] = max(dp[j], dp[j-w[i]*mu]+v[i]*mu);
      }
      num -= mu;
    }
  }
  cout << dp[W] << endl;
  return 0;
}
