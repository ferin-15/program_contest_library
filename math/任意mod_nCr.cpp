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
