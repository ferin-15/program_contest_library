// x = a1 mod m1, x2 = a2 mod m2 を解く オーバーフローには注意
// O(log(min(m1, m2)))
pair<ll, ll> crt(ll a1, ll a2, ll m1, ll m2) {
  auto normal = [](ll x, ll m) { return x>=-x ? x%m : m-(-x)%m; };
  auto modmul = [&normal](ll a, ll b, ll m) { return normal(a, m)*normal(b, m)%m; };
  ll k1, k2;
  ll g = extgcd(m1, m2, k1, k2);
  if(normal(a1, g) != normal(a2, g)) return {-1, -1};
  ll l = m1 / g * m2;
  ll x = a1 + modmul(modmul((a2-a1)/g, k1, l), m1, l);
  return {x, l};
}

pair<ll, ll> crt(vector<ll> a, vector<ll> m) {
  ll mod = 1, ans = 0;
  int n = a.size();
  REP(i, n) {
    tie(ans, mod) = crt(ans, a[i], mod, m[i]);
    if(ans == -1) return {-1, -1};
  }
  return {ans, mod};
}
