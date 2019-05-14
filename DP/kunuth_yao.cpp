// BEGIN CUT

// X(i,j) = min_{i<=s<j} {X(i,s)+X(s,j)} + W(i,j) を O(N^2) で計算\n
auto knuth_yao = [&]() {
  // K(i,j) = argmin_{i<=s<j} (X(i,s) + X(s,j))
  VV<int> W(n+5, V<int>(n+5, 0)), X(n+5, V<int>(n+5, 0)), K(n+5, V<int>(n+5, 0));
  REP(i, n+1) FOR(j, i+1, n+1) W[i][j] = 0LL; // !!!!!
  REP(i, m+1) REP(j, m+1) {
    X[i][j] = (i==j ? 0 : INF);
    K[i][j] = (i==j ? i : 0);
  }
  for(int w=1; w<=m; ++w) {
    for(int i=0, j=i+w; (j=i+w) <= m; ++i) {
      // K(i,j)の単調性から範囲が限定できる
      for(int r = K[i][j-1]; r <= K[i+1][j]; ++r) {
        int c = X[i][r] + X[r+1][j] + W[i][j];
        if(X[i][j] > c) { X[i][j] = c; K[i][j] = r; }
      }
    }
  }
};
// END CUT
