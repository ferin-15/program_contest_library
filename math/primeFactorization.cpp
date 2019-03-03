// mの素因数分解をする O(sqrt(m) + loglog(m))
vector<pair<ll,ll>> primeFactorization(ll m) {
  bool is_prime = true;
  for(ll i=2; i*i<=m; ++i) {
    if(m%i==0) {
      is_prime = false;
      break;
    }
  }
  if(is_prime) return {{m, 1LL}};
  vector<pair<ll,ll>> v;
  for(ll i=2; i<=m; ++i) {
    ll t = 0;
    while(m%i==0) {
      m /= i;
      t++;
    }
    if(t) v.push_back({i, t});
    if(m == 1) break;
  }
  return v;
}