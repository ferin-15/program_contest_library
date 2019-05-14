/**
* @brief i番目の高さがh[i]のヒストグラム中で最大の長方形の面積
*/
auto largest_rectangle_histogram() {
  int n; V<int> h(n), l(n), r(n), st(n);
  cin >> n;
  REP(i, n) cin >> h[i];
  int t = 0;
  REP(i, n) {
    while(t>0 && h[st[t-1]] >= h[i]) t--;
    l[i] = t == 0 ? 0 : (st[t-1]+1);
    st[t++] = i;
  }
  t = 0;
  for(int i=n-1; i>=0; --i) {
    while(t > 0 && h[st[t-1]] >= h[i]) t--;
    r[i] = t == 0 ? n : st[t-1];
    st[t++] = i;
  }
  ll ret = 0;
  REP(i, n) ret = max(ret, (ll)h[i]*(r[i]-l[i]));
  return ret;
};