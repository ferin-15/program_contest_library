ll fact[1000010], ifact[1000010];
void makeFac(ll p, ll q) {
  ll pr = 1;
  REP(i, q) pr *= p;
  fact[0] = ifact[0] = 1;
  FOR(i, 1, pr+1) {
    if(i%p == 0) {
      fact[i] = fact[i-1];
    } else {
      fact[i] = fact[i-1] * i % pr;
    }
    ifact[i] = inv(fact[i], pr);
  }
}

ll C(ll n, ll r, ll p, ll q) {
  if(n < 0 || r < 0 || r > n) return 0;
  // pr = p^q
  int pr = 1;
  REP(i, q) pr *= p;

  ll z = n-r;
  int e0 = 0;
  for(ll u=n/p;u;u/=p) e0 += u;
  for(ll u=r/p;u;u/=p) e0 -= u;
  for(ll u=z/p;u;u/=p) e0 -= u;
  int em = 0;
  for(ll u=n/pr;u;u/=p) em += u;
  for(ll u=r/pr;u;u/=p) em -= u;
  for(ll u=z/pr;u;u/=p) em -= u;

  ll ret = 1;
  while(n > 0) {
    ret = ret*fact[n%pr]%pr*ifact[r%pr]%pr*ifact[z%pr]%pr;
    n /= p; r /= p; z /= p;
  }
  (ret *= binpow(p, e0, pr)) %= pr;
  if(!(p==2 && q >= 3) && em%2) ret = (pr-ret) % pr;
  return ret;
}
