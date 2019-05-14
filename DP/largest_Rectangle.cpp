int largeest_rectangle() {
  int n, h, w;
  VV<int> c(h, V<int>(w)), dp(h, V<int>(w));
  V<int> l(h), r(h), st(h);

  cin >> h >> w;
  REP(i, h) REP(j, w) cin >> c[i][j];

  REP(i, w) {
    int cnt = 1;
    REP(j, h) {
      if(!c[j][i]) {
        dp[j][i] = cnt;
        cnt++;
      } else {
        dp[j][i] = 0;
        cnt = 1;
      }
    }
  }
  int ret = 0;
  REP(j, h) {
    int t = 0;
    REP(i, w) {
      while(t>0 && dp[j][st[t-1]] >= dp[j][i]) t--;
      l[i] = t == 0 ? 0 : (st[t-1]+1);
      st[t++] = i;
    }
    t = 0;
    for(int i=w-1; i>=0; --i) {
      while(t > 0 && dp[j][st[t-1]] >= dp[j][i]) t--;
      r[i] = t == 0 ? n : st[t-1];
      st[t++] = i;
    }
    REP(i, w) chmax(ret, (ll)dp[j][i]*(r[i]-l[i]));
  }
  return ret;
};