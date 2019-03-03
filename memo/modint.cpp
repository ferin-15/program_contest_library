struct mint {
  ll x;
  mint(): x(0) { }
  mint(ll y) : x(y>=0 ? y%MOD : y%MOD+MOD) {}
  ll get() const { return x; }
  // e乗
  mint pow(ll e) {
    ll a = 1, p = x;
    while(e > 0) {
      if(e%2 == 0) {p = (p*p) % MOD; e /= 2;}
      else {a = (a*p) % MOD; e--;}
    }
    return mint(a);
  }
  // Comparators
  bool operator <(mint b) { return x < b.x; }
  bool operator >(mint b) { return x > b.x; }
  bool operator<=(mint b) { return x <= b.x; }
  bool operator>=(mint b) { return x >= b.x; }
  bool operator!=(mint b) { return x != b.x; }
  bool operator==(mint b) { return x == b.x; }
  // increment, decrement
  mint operator++() { x++; return *this; }
  mint operator++(signed) { mint t = *this; x++; return t; }
  mint operator--() { x--; return *this; }
  mint operator--(signed) { mint t = *this; x--; return t; }
  // Basic Operations
  mint &operator+=(mint that) {
    x += that.x;
    if(x >= MOD) x -= MOD;
    return *this;
  }
  mint &operator-=(mint that) {
    x -= that.x;
    if(x < 0) x += MOD;
    return *this;
  }
  mint &operator*=(mint that) {
    x = (ll)x * that.x % MOD;
    return *this;
  }
  mint &operator/=(mint that) {
    x = (ll)x * that.pow(MOD-2).x % MOD;
    return *this;
  }
  mint &operator%=(mint that) {
    x = (ll)x % that.x;
    return *this;
  }
  mint operator+(mint that) const { return mint(*this) += that; }
  mint operator-(mint that) const { return mint(*this) -= that; }
  mint operator*(mint that) const { return mint(*this) *= that; }
  mint operator/(mint that) const { return mint(*this) /= that; }
  mint operator%(mint that) const { return mint(*this) %= that; }
};
// Input/Output
ostream &operator<<(ostream& os, mint a) { return os << a.x; }
istream &operator>>(istream& is, mint &a) { return is >> a.x; }