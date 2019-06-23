// 分数ライブラリ
// 常に約分されているとする
// 負のときは常にaを負にする
struct fraction {
    ll a, b;
    fraction(ll x=0, ll y=1) : a(x), b(y) {
        ll g = __gcd(a, b);
        a /= g, b /= g;
        if(b < 0) a *= -1, b *= -1;
    }
    // comparator
    bool operator<(fraction r) const { return a*r.b < b*r.a; }
    bool operator>(fraction r) const { return a*r.b > b*r.a; }
    bool operator<=(fraction r) const { return a*r.b <= b*r.a; }
    bool operator>=(fraction r) const { return a*r.b >= b*r.a; }
    bool operator==(fraction r) const { return a*r.b == b*r.a; }
    bool operator!=(fraction r) const { return a*r.b != b*r.a; }
    // Basic Operations
    fraction operator+(fraction r) const { return fraction(*this) += r; }
    fraction operator-(fraction r) const { return fraction(*this) -= r; }
    fraction operator*(fraction r) const { return fraction(*this) *= r; }
    fraction operator/(fraction r) const { return fraction(*this) /= r; }
    fraction &operator+=(fraction r) {
        ll g = __gcd(abs(a*r.b+b*r.a), b*r.b);
        ll na = (a*r.b+b*r.a)/g, nb = (b*r.b)/g;
        a = na, b = nb;
        return *this;
    }
    fraction &operator-=(fraction r) {
        ll g = __gcd(abs(a*r.b-b*r.a), b*r.b);
        ll na = (a*r.b-b*r.a)/g, nb = (b*r.b)/g;
        a = na, b = nb;
        return *this;
    }
    fraction &operator*=(fraction r) {
        ll g1 = __gcd(a, r.a), g2 = __gcd(b, r.b);
        a = a/g1*r.a, b = b/g2*r.b;
        return *this;
    }
    fraction &operator/=(fraction r) {
        ll g1 = __gcd(a, r.b), g2 = __gcd(b, r.a);
        a = a/g1*r.b, b = b/g2*r.a;
        if(b < 0) a *= -1, b *= -1;
        return *this;
    }
    friend fraction abs(fraction a) {
        a.a = abs(a.a);
        return a;
    }
    // output
    friend ostream &operator<<(ostream& os, fraction a) {
        return os << a.a << "/" << a.b;
    }
};
