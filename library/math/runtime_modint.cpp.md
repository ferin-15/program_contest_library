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


# :heavy_check_mark: math/runtime_modint.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/runtime_modint.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 05:17:03+09:00




## Required by

* :warning: <a href="../test/sqrt_mod.memo.cpp.html">test/sqrt_mod.memo.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/ALDS1_10_A.test.cpp.html">test/ALDS1_10_A.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj1501.test.cpp.html">test/aoj1501.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj2983.test.cpp.html">test/aoj2983.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/runtime_modint.cpp"
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

