#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
// #define int ll
using PII = pair<ll, ll>;
 
#define FOR(i, a, n) for (ll i = (ll)a; i < (ll)n; ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(x) x.begin(), x.end()
 
template<typename T> T &chmin(T &a, const T &b) { return a = min(a, b); }
template<typename T> T &chmax(T &a, const T &b) { return a = max(a, b); }
template<typename T> bool IN(T a, T b, T x) { return a<=x&&x<b; }
template<typename T> T ceil(T a, T b) { return a/b + !!(a%b); }

template<typename T> vector<T> make_v(size_t a) { return vector<T>(a); }
template<typename T,typename... Ts>
auto make_v(size_t a,Ts... ts) { 
    return vector<decltype(make_v<T>(ts...))>(a,make_v<T>(ts...));
}
template<typename T,typename V> typename enable_if<is_class<T>::value==0>::type
fill_v(T &t, const V &v) { t=v; }
template<typename T,typename V> typename enable_if<is_class<T>::value!=0>::type
fill_v(T &t, const V &v ) { for(auto &e:t) fill_v(e,v); }

template<class S,class T>
ostream &operator <<(ostream& out,const pair<S,T>& a){
    out<<'('<<a.first<<','<<a.second<<')'; return out;
}
template<class T>
ostream &operator <<(ostream& out,const vector<T>& a){
    out<<'['; for(T i: a) {out<<i<<',';} out<<']'; return out;
}

int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0}; // DRUL
const int INF = 1<<30;
const ll LLINF = 1LL<<60;
const ll MOD = 1000000007;

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
