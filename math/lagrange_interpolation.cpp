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
ostream &operator <<(ostream& out,const pair<S,T>& a) {
    out<<'('<<a.first<<','<<a.second<<')'; return out;
}
template<class T>
ostream &operator <<(ostream& out,const vector<T>& a){
    out<<'[';
    for(const T &i: a) out<<i<<',';
    out<<']';
    return out;
}
template<class T>
ostream &operator <<(ostream& out, const set<T>& a) {
    out<<'{';
    for(const T &i: a) out<<i<<',';
    out<<'}';
    return out;
}
template<class T, class S>
ostream &operator <<(ostream& out, const map<T,S>& a) {
    out<<'{';
    for(auto &i: a) out<<i<<',';
    out<<'}';
    return out;
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
using mint = modint<1000000007>;

// verify: https://atcoder.jp/contests/arc033/submissions/6839946
// x座標が相異なるn+1点(x_i,y_i)を通るn次以下の多項式f(T)の値を返す
// x_i = a + i*d 0<=i<=n (等差数列)
// 0割りを起こさないようにTが小さいときに注意
// O(nlog(MOD))
mint lagrange_interpolation_arithmetic(mint a, mint d, vector<mint> y, mint T) {
    const ll n = y.size() - 1;
    mint ret = 0, ft = 1;
    REP(i, n+1) ft *= T-(a+d*i);
    // f_0(x_0)
    mint f = 1;
    FOR(i, 1, n+1) f *= -1*i*d;
    ret += y[0] / f * ft / (T-a);
    // f_i(x_i) → f_{i+1}(x_{i+1})
    REP(i, n) {
        f *= d*(i+1) / (d*(i-n));
        ret += y[i+1] / f * ft / (T-a-d*(i+1));
    }
    return ret;
}

// verify: https://atcoder.jp/contests/arc033/submissions/6839930
// x座標が相異なるn+1点(x_i,y_i)を通るn次以下の多項式f(T)の値を返す
// O(n^2)
mint lagrange_interpolation(vector<mint> x, vector<mint> y, mint T) {
    const ll n = x.size() - 1;
    mint ret = 0;
    REP(i, n+1) {
        mint t = 1;
        REP(j, n+1) {
            if(i == j) continue;
            t *= T-x[j];
            t /= x[i]-x[j];
        }
        ret += t * y[i];
    }
    return ret;
}

// verify: https://atcoder.jp/contests/abc137/submissions/6839902
// x座標が相異なるn+1点(x_i,y_i)を通るn次以下の多項式f(x)を返す
// O(n^2) 定数倍がかなり重い
vector<mint> lagrange_interpolation(vector<mint> x, vector<mint> y) {
    const ll n = x.size() - 1;
    REP(i, n+1) {
        mint t = 1;
        REP(j, n+1) if(i != j) t *= x[i]-x[j];
        y[i] /= t;
    }
    ll cur = 0, nxt = 1;
    vector<vector<mint>> dp(2, vector<mint>(n+2));
    dp[0][0] = -1 * x[0], dp[0][1] = 1;
    FOR(i, 1, n+1) {
        REP(j, n+2) {
            dp[nxt][j] = dp[cur][j] * -1 * x[i];
            if(j >= 1) dp[nxt][j] += dp[cur][j-1];
        }
        swap(nxt, cur);
    }
    REP(i, n+1) x[i] = x[i].inv();
    vector<mint> ret(n+1);  // f(x)
    REP(i, n+1) {
        if(y[i]==0) continue;
        // 0割り対策の場合分け
        if(x[i] == 0) {
            REP(j, n+1) ret[j] += dp[cur][j+1] * y[i];
        } else {
            ret[0] -= dp[cur][0] * x[i] * y[i];
            mint pre = -1 * dp[cur][0] * x[i];
            FOR(j, 1, n+1) {
                ret[j] -= (dp[cur][j] - pre) * x[i] * y[i];
                pre = -1 * (dp[cur][j] - pre) * x[i];
            }
        }
    }
    return ret;
}