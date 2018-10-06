//二分累乗法 xのe乗
ll binpow(ll x, ll e) {
  ll a = 1, p = x;
  while(e > 0) {
    if(e%2 == 0) {p = (p*p) % MOD; e /= 2;}
    else {a = (a*p) % MOD; e--;}
  }
  return a % MOD;
}
