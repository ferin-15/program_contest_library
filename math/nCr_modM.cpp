// C(n,r) % mod を求める
// O(mod) くらい (多分もっと長いけど大体そんなもん)
ll func(ll n, ll r, ll mod) {
  ll x = mod;
  vector<ll> a, m;
  FOR(i, 2, mod+1) if(x%i == 0) {
    ll cnt=0, pr=1;
    while(x%i==0) x/=i, cnt++, pr*=i;
    makeFac(i, cnt);
    a.PB(C(n, r, i, cnt));
    m.PB(pr);
  }

  return crt(a, m).first;
}
