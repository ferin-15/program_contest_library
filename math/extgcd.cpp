// ax + by = gcd(a, b) となる {x, y, gcd(a, b)} を返す
// O(log(min(a, b)))
ll extgcd(ll a, ll b, ll &x, ll &y) {
  ll g = a; x = 1, y = 0;
  if(b != 0) g = extgcd(b, a%b, y, x), y -= (a/b) * x;
  return g;
}

// a^-1 mod n を返す　存在しなければ-1
// O(log(n))
ll inv(ll a, ll n) {
  ll s, t;
  extgcd(a, n, s, t);
  return (n+s) % n;
}
