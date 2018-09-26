// BEGIN CUT
//二分累乗法 xのe乗
ll binpow(ll x, ll e, ll mo=MOD) {
  ll a = 1, p = x;
  while(e > 0) {
    if(e%2 == 0) {p = (p*p) % mo; e /= 2;}
    else {a = (a*p) % mo; e--;}
  }
  return a;
}
// END CUT