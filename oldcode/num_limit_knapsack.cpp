// 重さX[i]、価値Y[i]、個数上限Z[i] としたときの個数制限付きナップザック
// O(N^2maxy^2logN)
// ARC096-F でverify

const int maxy = 50;
// dp[i] = (価値がiのときの最小の重さ)
VI dp(maxy*maxy*maxy+5, INF);
// i番目のアイテムについて重さと価値がそれぞれ(X[i],Y[i])(2X[i],Y[i])…(2^kX[i],2^kY[i])が一つずつ存在すると考える
dp[0] = 0;
REP(i, n) {
  int num = min(maxy, Z[idx[i]]);
  for(int k=1; num; k<<=1) {
    int mul = min(k, num);
    for(int j=maxy*maxy*maxy; j>=0; --j) {
      if(j+mul*Y[idx[i]] <= maxy*maxy*maxy) {
        chmin(dp[j+mul*Y[idx[i]]], dp[j] + mul*X[idx[i]]);
      }
    }
    num -= mul;
  }
}

int ans = 0;
REP(i, maxy*maxy*maxy+1) {
  // 価値iとして残りをgreedyに決める
  if(dp[i]>x) continue;
  int ret=i, w = x-dp[i];
  REP(j, n) {
    // cnt個取る
    int cnt = Z[idx[j]] - min(maxy, Z[idx[j]]);
    chmin(cnt, w/X[idx[j]]);
    ret += cnt*Y[idx[j]];
    w -= cnt*X[idx[j]];
  }
  chmax(ans, ret);
}
cout << ans << endl;
