// 数列の初項k項aと漸化式の係数dが与えられる
// a_nをO(K^2logN)で求める
vector<ll> dfs(vector<ll> a, vector<ll> d, ll n) {
  ll k = d.size();
  if(n == k) return d;
  vector<ll> ret(k);
  if(n&1 || n<k*2) {
    auto v = dfs(a, d, n-1);
    ret[0] = v[k-1] * a[0] % MOD;
    FOR(i, 1, k) ret[i] = (v[i-1] + v[k-1] * a[i] % MOD) % MOD;
  } else {
    auto v = dfs(a, d, n/2);
    vector<vector<ll>> f(k, vector<ll>(k));
    f[0] = v;
    FOR(i, 1, k) {
      f[i][0] = f[i-1][k-1] * a[0] % MOD;
      FOR(j, 1, k) f[i][j] = (f[i-1][j-1] + f[i-1][k-1] * a[j] % MOD) % MOD;
    }
    REP(i, k) REP(j, k) (ret[i] += v[j] * f[j][i] % MOD) %= MOD;
  }
  return ret;
}
ll kitamasa(vector<ll> a, vector<ll> d, ll n) {
  auto ret = dfs(a, d, n);
  ll ans = 0;
  REP(i, d.size()) (ans += d[i] * ret[i]) %= MOD;
  return ans;
}