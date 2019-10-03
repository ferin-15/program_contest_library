int d[17][17], f[17];
signed main(void)
{
  int v, e, tot = 0;
  cin >> v >> e;
  REP(i, v) REP(j, v) d[i][j] = INF;
  REP(i, e) {
    int a, b, c;
    cin >> a >> b >> c;
    d[a][b] = min(d[a][b], c); d[b][a] = min(d[b][a], c);
    f[a]++; f[b]++;
    tot += c;
  }
  VI o;
  REP(i, v) if(f[i]%2) o.push_back(i);
  REP(k, v) REP(i, v) REP(j, v) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
  int dp[1<<16], os = o.size();
  fill(dp, dp+(1<<os), INF);
  dp[0] = 0;
  REP(s, 1<<os) REP(i, os) if(~s>>i&1) REP(j, i) if(~s>>j&1) {
    dp[s|1<<i|1<<j] = min(dp[s|1<<i|1<<j], dp[s] + d[o[i]][o[j]]);
  }
  cout << tot + dp[(1<<os)-1] << endl;
  return 0;
}
