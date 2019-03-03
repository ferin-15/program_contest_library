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

// O(a.size*logM)
// 連立線形合同式 a[i] * x ≡ b[i] (mod m[i]) を解く
// オーバーフローには注意
pair<ll, ll> crt(const vector<ll>& a, const vector<ll>& b, const vector<ll>& m) {
  // (答えx, mod)
  pair<ll, ll> ret(0, 1);
  REP(i, a.size()) {
    ll s = a[i] * ret.second;
    ll t = b[i] - a[i] * ret.first;
    ll d = __gcd(m[i], s);
    if(t % d != 0) return make_pair(-1, -1);
    ll u = t / d * inv(s / d, m[i] / d) % (m[i] / d);
    ret.first += ret.second * u;
    ret.second *= m[i] / d;
    ret.first = (ret.first % ret.second + ret.second) % ret.second;
  }
  return ret;
}