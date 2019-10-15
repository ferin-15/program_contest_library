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
    // 平方剰余のうち一つを返す なければ-1
    friend modint sqrt(modint a) {
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
    friend istream &operator>>(istream& is, modint &a) { 
        is >> a.x;
        a.x = ((a.x%MOD)+MOD)%MOD;
        return is;
    }
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
using mint = modint<998244353>;

template<typename T>
struct formalPowerSeries {
    using Poly = vector<T>;
    using Conv = function<poly(poly,poly)>;
    Conv conv;
    formalPowerSeries(Conv conv) : conv(conv) {}

    // a mod x^deg を求める
    Poly pre(const Poly &a, int deg) {
        return Poly(a.begin(), a.begin()+min(a.size(),deg));
    }
    // 加減算 O(n)
    Poly add(Poly a, Poly b) {
        const int sz = max(a.size(), b.size());
        Poly c(sz, T(0));
        REP(i, a.size()) c[i] += a[i];
        REP(i, b.size()) c[i] += b[i];
        return c;
    }
    Poly sub(Poly a, Poly b) {
        const int sz = max(a.size(), b.size());
        Poly c(sz, T(0));
        REP(i, a.size()) c[i] += a[i];
        REP(i, b.size()) c[i] -= b[i];
        return c;
    }
    // 畳み込み O(nlogn)
    Poly mul(Poly a, Poly b) { return conv(a, b); }
    Poly mul(Poly a, T b) {
        REP(i, a.size()) a[i] *= b;
        return a;
    }
    // 1/a を求める O(nlogn)
    // 定数項が非0であること
    Poly inv(Poly a, int deg) {
        assert(a[0] != T(0));
        Poly ret({T(1)/as[0]});
        for(int i=1; i<deg; i<<=1) {
            ret = pre(sub(add(ret, ret), mul(mul(ret, ret), pre(a, i<<1))), i<<1);
        }
        return ret;
    }
    // a!=0 && b!=0
    Poly div(Poly a, Poly b) {
        while(a.back() == t(0)) a.pop_back();
        while(b.back() == t(0)) b.pop_back();
        if(b.size() > a.size()) return Poly();
        reverse(ALL(a)); reverse(ALL(b));
        int n = a.size()-b.size()+1;
        Poly ret = pre(mul(as, inv(bs, n)), n);
        reverse(ALL(ret));
        return ret;
    }
    // 定数項が1であること
    Poly sqrt(Poly a, int deg) {
        assert(a[0]==T(1));
        T inv2 = T(1)/2;
        Poly s({T(1)});
        for(int i=1; i<deg; i<<=1) {
            s = pre(add(ss, mul(pre(a, i<<1), inv(s, i<<1))), i<<1);
            for(auto &j: s) j *= inv2;
        }
    }
    // 微分 O(n)
    Poly diff(Poly a) {
        const int n = a.size();
        Poly r(n-1);
        FOR(i, 1, n) rs[i-1] = a[i] * T(i);
        return r;
    }
    // 積分 O(n) 定数項は0とする
    Poly integral(Poly a) {
        const int n = a.size();
        Poly ret(n+1);
        ret[0] = T(0);
        REP(i, n) ret[i+1] = ret[i] / T(i+1);
        return ret;
    }
    // 定数項は1であること
    Poly log(Poly a, int deg) {
        assert(a[0]==1);
        return pre(integral(mul(diff(a), inv(a, deg))), deg);
    }
    // 定数項が0であること
    Poly exp(Poly a, int deg) {
        assert(a[0]==0);
        Poly f({T(1)});
        a[0] += T(1);
        for(int i=1; i<deg; i<<=1) {
            f = pre(mul(f, sub(pre(a, i<<1), log(f, i<<1))), i<<1);
        }
        return f;
    }
};

template<class T, int primitive_root>
struct NTT {
    void ntt(vector<T>& a, int sign) {
        const int n = a.size();
        assert((n^(n&-n)) == 0);
        T g = 3; //g is primitive root of mod
        const ll mod = T::mod();
        T h = g.pow((mod-1)/n); // h^n = 1
        if(sign == -1) h = h.inv(); //h = h^-1 % mod
        //bit reverse
        int i = 0;
        for (int j = 1; j < n - 1; ++j) {
            for (int k = n >> 1; k >(i ^= k); k >>= 1);
            if (j < i) swap(a[i], a[j]);
        }
        for (int m = 1; m < n; m *= 2) {
            const int m2 = 2 * m;
            const T base = h.pow(n/m2);
            T w = 1;
            for(int x=0; x<m; ++x) {
                for (int s = x; s < n; s += m2) {
                    T u = a[s];
                    T d = a[s + m] * w;
                    a[s] = u + d;
                    a[s + m] = u - d;
                }
                w *= base;
            }
        }
    }
    void ntt(vector<T>& input) { ntt(input, 1); }
    void inv_ntt(vector<T>& input) {
        ntt(input, -1);
        const T n_inv = T((int)input.size()).inv();
        for(auto &x: input) x *= n_inv;
    }
    vector<T> convolution(const vector<T>& a, const vector<T>& b) {
        int sz = 1;
        while(sz < (int)a.size() + (int)b.size()) sz *= 2;
        vector<T> a2(a), b2(b);
        a2.resize(sz); b2.resize(sz);
        ntt(a2); ntt(b2);
        for(int i=0; i<sz; ++i) a2[i] *= b2[i];
        inv_ntt(a2);
        return a2;
    }
};

signed main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n, m;
    cin >> n >> m;

    NTT<mint, 3> ntt;
    auto conv = [&](auto a, auto b) { return ntt.convolution(a, b); };
    formalPowerSeries<mint> fps(conv);

    return 0;
}
