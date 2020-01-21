---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: test/ALDS1_10_A.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/ALDS1_10_A.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-22 01:08:39+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_A&lang=jp">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_A&lang=jp</a>


## Depends on

* :heavy_check_mark: <a href="../../library/math/finite_field_matrix.cpp.html">math/finite_field_matrix.cpp</a>
* :heavy_check_mark: <a href="../../library/math/runtime_modint.cpp.html">math/runtime_modint.cpp</a>
* :heavy_check_mark: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_A&lang=jp"
#include "../memo/macro.hpp"
#include "../math/runtime_modint.cpp"
#include "../math/finite_field_matrix.cpp"

signed main(void) {
    MOD = (1LL<<61)-1;
    ll n;
    cin >> n;

    matrix mat(2, 2);
    mat.get(0, 0) = 1, mat.get(0, 1) = 1;
    mat.get(1, 0) = 1, mat.get(1, 1) = 0;
    mat = pow(mat, n); 

    cout << mat.get(0, 0) << endl;

    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/ALDS1_10_A.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_A&lang=jp"
#line 1 "test/../memo/macro.hpp"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PII = pair<ll, ll>;
#define FOR(i, a, n) for (ll i = (ll)a; i < (ll)n; ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(x) x.begin(), x.end()
template<typename T> void chmin(T &a, const T &b) { a = min(a, b); }
template<typename T> void chmax(T &a, const T &b) { a = max(a, b); }
struct FastIO {FastIO() { cin.tie(0); ios::sync_with_stdio(0); }}fastiofastio;
const ll INF = 1LL<<60;#line 1 "test/../math/runtime_modint.cpp"
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
};#line 1 "test/../math/finite_field_matrix.cpp"
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
        Y.get(0,0) = mint(10).pow(g), Y.get(0,1) = 1;
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
#line 5 "test/ALDS1_10_A.test.cpp"

signed main(void) {
    MOD = (1LL<<61)-1;
    ll n;
    cin >> n;

    matrix mat(2, 2);
    mat.get(0, 0) = 1, mat.get(0, 1) = 1;
    mat.get(1, 0) = 1, mat.get(1, 1) = 0;
    mat = pow(mat, n); 

    cout << mat.get(0, 0) << endl;

    return 0;
}
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

