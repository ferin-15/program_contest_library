// nのm乗根 整数でなければ-1 O(mlogn)
ll root(ll n, ll m) {
  ll lb = 1, ub = n;
  while(ub-lb > 1) {
    ll mid = (lb+ub)/2, tmp = mid, prev = 1;
    REP(i, m-1) {
      if(tmp/prev != (tmp*mid)/tmp) {tmp = n+1; break;}
      prev = tmp;
      tmp *= mid;
    }
    if(tmp >= n) ub = mid;
    else lb = mid;
  }
  ll tmp = ub, prev = 1;
  REP(i, m-1) {
    if(tmp/prev != (tmp*ub)/tmp) {tmp = -1; break;}
    prev = tmp;
    tmp *= ub;
  }
  if(tmp == n) return ub;
  return -1;
}
