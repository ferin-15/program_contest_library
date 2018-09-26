ll combi(ll N_, ll C_, ll mo=MOD) {
  const int NUM_=1e5+10;
  static ll fact[NUM_+1]={},factr[NUM_+1]={},inv[NUM_+1]={};
  auto binpow = [&](ll x, ll e) -> ll{
    ll a = 1, p = x;
    while(e > 0) {
      if(e%2 == 0) {p = (p*p) % mo; e /= 2;}
      else {a = (a*p) % mo; e--;}
    }
    return a;
  };
  if (fact[0]==0) {
    fact[0] = factr[0] = inv[0] = 1;
    FOR(i, 1, NUM_+1) fact[i] = fact[i-1] * i % MOD;
    factr[NUM_] = binpow(fact[NUM_], mo-2);
    for(int i=NUM_-1; i>=0; --i) factr[i] = factr[i+1] * (i+1) % MOD;
    // fact[i] = fact[i-1] * i;
    // inv[i] = binpow(i, MOD-2);
    // factr[i] = factr[i-1] * inv[i];
  }
  if(C_<0 || C_>N_) return 0;
  // 前計算 O(max(N,K)) クエリ O(1)
  return factr[C_]*fact[N_]%MOD*factr[N_-C_]%MOD;
  // 前計算 O(max(N,K)log(mod)) クエリ O(K)
  // ll ret = 1;
  // for(;C_>0;N_--,C_--) (ret *= N_%MOD) %= MOD, (ret *= inv[C_]) %= MOD;
  // return ret;
}
