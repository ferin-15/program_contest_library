template<ll MOD>
struct modint {
    ll x;
    modint(): x(0) {}
    modint(ll y) : x(y>=0 ? y%MOD : y%MOD+MOD) {}
    static constexpr ll mod() { return MOD; }
    // e乗
    modint pow(ll e) {
        ll a = 1, p = x;
        while(e > 0) {
            if(e%2 == 0) {p = (p*p) % MOD; e /= 2;}
            else {a = (a*p) % MOD; e--;}
        }
        return modint(a);
    }
    modint inv() const {
        ll a=x, b=MOD, u=1, y=1, v=0, z=0;
        while(a) {
            ll q = b/a;
            swap(z -= q*u, u);
            swap(y -= q*v, v);
            swap(b -= q*a, a);
        }
        return z;
    }
    // Comparators
    bool operator <(modint b) { return x < b.x; }
    bool operator >(modint b) { return x > b.x; }
    bool operator<=(modint b) { return x <= b.x; }
    bool operator>=(modint b) { return x >= b.x; }
    bool operator!=(modint b) { return x != b.x; }
    bool operator==(modint b) { return x == b.x; }
    // Basic Operations
    modint operator+(modint r) const { return modint(*this) += r; }
    modint operator-(modint r) const { return modint(*this) -= r; }
    modint operator*(modint r) const { return modint(*this) *= r; }
    modint operator/(modint r) const { return modint(*this) /= r; }
    modint &operator+=(modint r) {
        if((x += r.x) >= MOD) x -= MOD;
        return *this;
    }
    modint &operator-=(modint r) {
        if((x -= r.x) < 0) x += MOD;
        return *this;
    }
    modint &operator*=(modint r) { x = x * r.x % MOD; return *this; }
    modint &operator/=(modint r) { return *this *= r.inv(); }
    // increment, decrement
    modint operator++() { x++; return *this; }
    modint operator++(signed) { modint t = *this; x++; return t; }
    modint operator--() { x--; return *this; }
    modint operator--(signed) { modint t = *this; x--; return t; }
};
using mint = modint<1000000007>;
template<class T> mint operator*(T l, mint r) { return mint(l) *= r; }
template<class T> mint operator+(T l, mint r) { return mint(l) += r; }
template<class T> mint operator-(T l, mint r) { return mint(l) -= r; }
template<class T> mint operator/(T l, mint r) { return mint(l) /= r; }
template<class T> bool operator==(T l, mint r) { return mint(l) == r; }
template<class T> bool operator!=(T l, mint r) { return mint(l) != r; }
// Input/Output
ostream &operator<<(ostream& os, mint a) { return os << a.x; }
istream &operator>>(istream& is, mint &a) { return is >> a.x; }
string to_frac(mint v) {
    static map<ll, PII> mp;
    if(mp.empty()) {
        mp[0] = mp[mint::mod()] = {0, 1};
        FOR(i, 2, 1001) FOR(j, 1, i) if(__gcd(i, j) == 1) {
            mp[(mint(i) / j).x] = {i, j};
        }
    }
    auto itr = mp.lower_bound(v.x);
    if(itr != mp.begin() && v.x - prev(itr)->first < itr->first - v.x) --itr;
    string ret = to_string(itr->second.first + itr->second.second * ((int)v.x - itr->first));
    if(itr->second.second > 1) {
        ret += '/';
        ret += to_string(itr->second.second);
    }
    return ret;
}
