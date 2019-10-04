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

ll MOD;
struct mint {
    ll x;
    mint(): x(0) {}
    mint(ll y) : x(y>=0 ? y%MOD : y%MOD+MOD) {}
    // e乗
    mint pow(ll e) {
        ll a = 1, p = x;
        while(e > 0) {
            if(e%2 == 0) {p = (p*p) % MOD; e /= 2;}
            else {a = (a*p) % MOD; e--;}
        }
        return mint(a);
    }
    mint inv() const {
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
    bool operator!=(mint b) { return x != b.x; }
    bool operator==(mint b) { return x == b.x; }
    // Basic Operations
    mint operator+(mint r) const { return mint(*this) += r; }
    mint operator-(mint r) const { return mint(*this) -= r; }
    mint operator*(mint r) const { return mint(*this) *= r; }
    mint operator/(mint r) const { return mint(*this) /= r; }
    mint &operator+=(mint r) {
        if((x += r.x) >= MOD) x -= MOD;
        return *this;
    }
    mint &operator-=(mint r) {
        if((x -= r.x) < 0) x += MOD;
        return *this;
    }
    mint &operator*=(mint r) {
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
    mint &operator/=(mint r) { return *this *= r.inv(); }
    // 平方剰余のうち一つを返す なければ-1
    friend ll sqrt(mint a) {
        if(a == 0) return 0;
        ll q = MOD-1, s = 0;
        while((q&1)==0) q>>=1, s++;
        mint z=2;
        while(1) {
            if(z.pow((MOD-1)/2) == MOD-1) break;
            z++;
        }
        mint c = z.pow(q), r = a.pow((q+1)/2), t = a.pow(q);
        ll m = s;
        while(t.x>1) {
            mint tp=t;
            ll k=-1;
            FOR(i, 1, m) {
                tp *= tp;
                if(tp == 1) { k=i; break; }
            }
            if(k==-1) return -1;
            mint cp=c;
            REP(i, m-k-1) cp *= cp;
            c = cp*cp, t = c*t, r = cp*r, m = k;
        }
        return r.x;
    }
    template<class T> friend
    mint operator*(T l, mint r) { return mint(l) *= r; }
    template<class T> friend
    mint operator+(T l, mint r) { return mint(l) += r; }
    template<class T> friend
    mint operator-(T l, mint r) { return mint(l) -= r; }
    template<class T> friend
    mint operator/(T l, mint r) { return mint(l) /= r; }
    template<class T> friend
    bool operator==(T l, mint r) { return mint(l) == r; }
    template<class T> friend
    bool operator!=(T l, mint r) { return mint(l) != r; }
    // increment, decrement
    mint operator++() { x++; return *this; }
    mint operator++(signed) { mint t = *this; x++; return t; }
    mint operator--() { x--; return *this; }
    mint operator--(signed) { mint t = *this; x--; return t; }
    // Input/Output
    friend ostream &operator<<(ostream& os, mint a) { return os << a.x; }
    friend istream &operator>>(istream& is, mint &a) { return is >> a.x; }
    friend string to_frac(mint v) {
        static map<ll, PII> mp;
        if(mp.empty()) {
            mp[0] = mp[MOD] = {0, 1};
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
};

namespace librarychecker_sqrtmod {
    void solve() {
        ll t;
        cin >> t;
        while(t--) {
            ll a;
            cin >> a >> MOD;
            cout << sqrt(mint(a)) << endl;
        }
    }
}