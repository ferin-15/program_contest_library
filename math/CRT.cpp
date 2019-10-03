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
