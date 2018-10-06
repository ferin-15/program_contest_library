template<unsigned MOD>
class ModInt {
public:
  unsigned x;
  ModInt(): x(0) { }
  ModInt(signed sig) { if((x = sig % MOD + MOD) >= MOD) x -= MOD; }
  unsigned get() const { return x; }

  // 累乗
  ModInt binpow(ModInt y, ModInt e) {
    ModInt a = 1, p = y;
    while(e>0) {
      if(e%2 == 0) {p = (p*p) % MOD; e /= 2;}
      else {a = (a*p) % MOD; --e;}
    }
    a %= MOD; x = a.get();
    return a;
  }
  ModInt binpow(ll y, ll e) {
    ModInt a = 1, p = y;
    while(e>0) {
      if(e%2 == 0) {p = (p*p) % MOD; e /= 2;}
      else {a = (a*p) % MOD; --e;}
    }
    a %= MOD; x = a.get();
    return a;
  }

  // Comparators
  bool operator <(ModInt b) { return x < b.x; }
  bool operator >(ModInt b) { return x > b.x; }
  bool operator<=(ModInt b) { return x <= b.x; }
  bool operator>=(ModInt b) { return x >= b.x; }
  bool operator!=(ModInt b) { return x != b.x; }
  bool operator==(ModInt b) { return x == b.x; }

  // 代入
  void operator=(ll b) { x = b; }
  // increment, decrement
  ModInt operator++() { x++; return *this; }
  ModInt operator++(int) {ModInt a = *this; x++; return a;}
  ModInt operator--() { x--; return *this; }
  ModInt operator--(int) {ModInt a = *this; x--; return a;}

  // Basic Operations
  // ModInt and ModInt
  ModInt &operator+=(ModInt that) {
    x = ((unsigned long long)x+that.x)%MOD;
    return *this;
  }
  ModInt &operator-=(ModInt that) {
    x = ((((unsigned long long)x-that.x)%MOD)+MOD)%MOD;
    return *this;
  }
  ModInt &operator*=(ModInt that) {
    x = (unsigned long long)x * that.x % MOD;
    return *this;
  }
  // O(log(mod))かかるので注意
  ModInt &operator/=(ModInt that) {
    x = (unsigned long long)x * (binpow(that.x, MOD-2)) % MOD;
    return *this;
  }
  ModInt &operator%=(ModInt that) {
    x = (unsigned long long)x % that.x;
    return *this;
  }
  // ModInt and long long
  ModInt &operator+=(ll that) {
    x = ((unsigned long long)x+that)%MOD;
    return *this;
  }
  ModInt &operator-=(ll that) {
    x = ((((unsigned long long)x-that)%MOD)+MOD)%MOD;
    return *this;
  }
  ModInt &operator*=(ll that) {
    x = (unsigned long long)x * that % MOD;
    return *this;
  }
  // O(log(mod))かかるので注意
  ModInt &operator/=(ll that) {
    x = (unsigned long long)x * (binpow(that, MOD-2)) % MOD;
    return *this;
  }
  ModInt &operator%=(ll that) {
    x = (unsigned long long)x % that;
    return *this;
  }
  // ModInt and ModInt
  ModInt operator+(ModInt that)const{return ModInt(*this) += that;}
  ModInt operator-(ModInt that)const{return ModInt(*this) -= that;}
  ModInt operator*(ModInt that)const{return ModInt(*this) *= that;}
  ModInt operator/(ModInt that)const{return ModInt(*this) /= that;}
  ModInt operator%(ModInt that)const{return ModInt(*this) %= that;}
  // ModInt and ll
  ModInt operator+(ll that)const{return ModInt(*this) += that;}
  ModInt operator-(ll that)const{return ModInt(*this) -= that;}
  ModInt operator*(ll that)const{return ModInt(*this) *= that;}
  ModInt operator/(ll that)const{return ModInt(*this) /= that;}
  ModInt operator%(ll that)const{return ModInt(*this) %= that;}
};
typedef ModInt<998244353> mint;
// Input/Output
ostream &operator<<(ostream& os, mint a) {
  os << a.x;
  return os;
}
istream &operator>>(istream& is, mint &a) {
  is >> a.x;
  return is;
}
