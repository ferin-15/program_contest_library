#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1501"
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
    modint &operator*=(modint r) {
    #if !defined(_WIN32) || defined(_WIN64)
        x = x * r.x % MOD; return *this;
    #endif
        unsigned long long y = x * r.x;
        unsigned xh = (unsigned) (y >> 32), xl = (unsigned) y, d, m;
        asm(
            "divl %4; \n\t"
            : "=a" (d), "=d" (m)
            : "d" (xh), "a" (xl), "r" (MOD)
        );
        x = m;
        return *this;
    }
    modint &operator/=(modint r) { return *this *= r.inv(); }
    // increment, decrement
    modint operator++() { x++; return *this; }
    modint operator++(signed) { modint t = *this; x++; return t; }
    modint operator--() { x--; return *this; }
    modint operator--(signed) { modint t = *this; x--; return t; }

    template<class T>
    friend modint operator*(T l, modint r) { return modint(l) *= r; }
    template<class T>
    friend modint operator+(T l, modint r) { return modint(l) += r; }
    template<class T>
    friend modint operator-(T l, modint r) { return modint(l) -= r; }
    template<class T>
    friend modint operator/(T l, modint r) { return modint(l) /= r; }
    template<class T>
    friend bool operator==(T l, modint r) { return modint(l) == r; }
    template<class T>
    friend bool operator!=(T l, modint r) { return modint(l) != r; }
    // Input/Output
    friend ostream &operator<<(ostream& os, modint a) { return os << a.x; }
    friend istream &operator>>(istream& is, modint &a) { return is >> a.x; }
    friend string to_frac(modint v) {
        static map<ll, PII> mp;
        if(mp.empty()) {
            mp[0] = mp[MOD] = {0, 1};
            FOR(i, 2, 1001) FOR(j, 1, i) if(__gcd(i, j) == 1) {
                mp[(modint(i) / j).x] = {i, j};
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
};
using mint = modint<100000007>;

#include "../math/combination.cpp"

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll h, w, ax, ay, bx, by;
    cin >> h >> w >> ay >> ax >> by >> bx;

    mint ans = 0;
    ll mi = LLINF;
    auto func = [&](ll gx, ll gy) {
        if(abs(ax-gx)+abs(ay-gy) < mi) {
            mi = abs(ax-gx) + abs(ay-gy);
            ans = combi(abs(ax-gx)+abs(ay-gy), abs(ax-gx));
        } else if(abs(ax-gx)+abs(ay-gy) == mi) {
            ans += combi(abs(ax-gx)+abs(ay-gy), abs(ax-gx));
        }
    };

    func(bx-w, by-h);
    func(bx-w, by);
    func(bx-w, by+h);
    func(bx, by-h);
    func(bx, by);
    func(bx, by+h);
    func(bx+w, by-h);
    func(bx+w, by);
    func(bx+w, by+h);

    cout << ans << endl;

    return 0;
}

