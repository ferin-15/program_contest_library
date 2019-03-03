template<bool type=true>
ll combi(ll N_, ll K_, ll mo=MOD) {
  const int NUM_=5e5;
  static ll fact[NUM_+1]={},factr[NUM_+1]={},inv[NUM_+1]={};
  auto binpow = [&](ll x, ll e) -> ll {
    ll a = 1, p = x;
    while(e > 0) {
      if(e%2 == 0) {p = (p*p) % mo; e /= 2;}
      else {a = (a*p) % mo; e--;}
    }
    return a;
  };
  if (fact[0]==0) {
    if(type) {
      fact[0] = factr[0] = inv[0] = 1;
      FOR(i, 1, NUM_+1) fact[i] = fact[i-1] * i % MOD;
      factr[NUM_] = binpow(fact[NUM_], mo-2);
      for(int i=NUM_-1; i>=0; --i) factr[i] = factr[i+1] * (i+1) % MOD;
    } else {
      FOR(i, 1, NUM_+1) fact[i] = fact[i-1] * i % MOD;
      REP(i, NUM_+1) inv[i] = binpow(i, MOD-2);
    }
  }
  if(K_<0 || K_>N_) return 0;
  // 前計算 O(max(N,K)) クエリ O(1)
  if(type) return factr[K_]*fact[N_]%MOD*factr[N_-K_]%MOD;
  // Nが大きいけどKが小さい場合に使う 前計算 O(Klog(mod)) クエリ O(K)
  ll ret = 1;
  for(;K_>0;N_--,K_--) (ret *= N_%MOD) %= MOD, (ret *= inv[K_]) %= MOD;
  return ret;
}