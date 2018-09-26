// BEGIN CUT
int dp[1010][1010];
signed main(void)
{
  string s, t;
  cin >> t >> s;
  const int n = s.size(), m = t.size();
  REP(i, n+1) REP(j, m+1) {
    if(i == 0) dp[i][j] = j;
    else if(j == 0) dp[i][j] = i;
    else {
      if(s[i-1] == t[j-1]) {
        dp[i][j] = min({dp[i-1][j-1], dp[i-1][j]+1, dp[i][j-1]+1});
      } else {
        dp[i][j] = min({dp[i-1][j] + 1, dp[i][j-1] + 1, dp[i-1][j-1]+1});
      }
    }
  }
  cout << dp[n][m] << endl;
  return 0;
}
// END CUT