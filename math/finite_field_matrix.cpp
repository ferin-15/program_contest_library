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

// 実行時にmodを決定するmodint
ll MOD;
struct mint {
    ll x;
    mint(): x(0) {}
    mint(ll y) : x(y>=0 ? y%MOD : y%MOD+MOD) {}
    // e乗
    friend mint pow(mint p, ll e) {
        mint a(1);
        while(e > 0) {
            if(e%2 == 0) {p = (p*p); e /= 2;}
            else {a = (a*p); e--;}
        }
        return a;
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

// 有限体の行列
struct matrix {
    int h, w;
    vector<mint> dat;
    matrix() {}
    matrix(int h, int w) : h(h), w(w), dat(h*w) {}
    mint& get(int y, int x) { return dat[y*w+x]; }
    mint get(int y, int x) const { return dat[y*w+x]; }

    matrix& operator+=(const matrix& r) {
        assert(h==r.h && w==r.w);
        REP(i, h*w) dat[i] += r.dat[i];
        return *this;
    }
    matrix& operator-=(const matrix& r) {
        assert(h==r.h && w==r.w);
        REP(i, h*w) dat[i] -= r.dat[i];
        return *this;
    }
    matrix& operator*=(const matrix& r) {
        assert(w==r.h);
        matrix ret(h, w);
        REP(i, h) REP(j, r.w) REP(k, w) {
            ret.dat[i*r.w+j] += dat[i*w+k] * r.dat[k*r.w+j];
        }
        return (*this) = ret;
    }
    matrix operator+(const matrix& r) { return matrix(*this) += r; }
    matrix operator-(const matrix& r) { return matrix(*this) -= r; }
    matrix operator*(const matrix& r) { return matrix(*this) *= r; }
    bool operator==(const matrix& a) { return dat==a.dat; }
    bool operator!=(const matrix& a) { return dat!=a.dat; }

    friend matrix pow(matrix p, ll n) {
        matrix ret(p.h, p.w);
        REP(i, p.h) ret.get(i, i) = 1;
        while(n > 0) {
            if(n&1) {ret *= p; n--;}
            else {p *= p; n >>= 1;}
        }
        return ret;
    }
    // 階段行列を求める O(HW^2)
    friend int gauss_jordan(matrix& a) {
        int rank = 0;
        REP(i, a.w) {
            int pivot = -1;
            FOR(j, rank, a.h) if(a.get(j,i) != 0) { pivot = j; break; }
            if(pivot == -1) continue;
            REP(j, a.w) swap(a.get(rank,j), a.get(pivot,j));
            const mint inv = a.get(rank,i).inv();
            REP(j, a.w) a.get(rank,j) *= inv;
            REP(j, a.h) if(j != rank && a.get(j,i) != 0) {
                const mint num = a.get(j,i);
                REP(k, a.w) a.get(j,k) -= a.get(rank,k) * num;
            }
            rank++;
        }
        return rank;
    }

    friend ostream &operator<<(ostream& os, matrix a) {
        REP(i, a.h) {
            REP(j, a.w) os << a.get(i,j) << " ";
            os << endl;
        }
        return os;
    }
};

// 任意mod(<=1e9)で行列累乗
namespace ARC050C {
    void solve() {
        ll a, b;
        cin >> a >> b >> MOD;

        ll g = __gcd(a, b);

        matrix X(2, 2);
        X.get(0,0) = 10, X.get(0,1) = 1;
        X.get(1,1) = 1;
        matrix ret = pow(X, a-1);
        mint ans = ret.get(0,0) + ret.get(0,1);

        matrix Y(2, 2);
        Y.get(0,0) = pow(mint(10), g), Y.get(0,1) = 1;
        Y.get(1,1) = 1;
        ret = pow(Y, b/g-1);
        ans *= ret.get(0,0) + ret.get(0,1);

        cout << ans << endl;
    }
}

// mod 2 でgauss jordanをする
namespace codeflyer_D {
    void solve() {
        ll n;
        cin >> n;
        vector<ll> a(n), b(n);
        REP(i, n) cin >> a[i];
        REP(i, n) cin >> b[i];

        MOD = 2;
        matrix mata(n, 61), matb(n, 61);
        REP(i, n) {
            REP(j, 61) {
                mata.get(i,j) = !!(a[i]&1LL<<j);
                matb.get(i,j) = !!(b[i]&1LL<<j);
            }
        }

        gauss_jordan(mata), gauss_jordan(matb);
        if(mata == matb) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
}

// mod 2 で行列式を求める
namespace ARC054C {
    void solve() {
        MOD = 2;

        ll n;
        cin >> n;
        vector<string> s(n);
        REP(i, n) cin >> s[i];
        matrix mat(n, n);
        REP(i, n) REP(j, n) mat.get(i,j) = s[i][j]-'0';

        gauss_jordan(mat);
        mint ret = 1;
        REP(i, n) ret *= mat.get(i,i);
        cout << (ret==1 ? "Odd" : "Even") << endl;
    }
}
