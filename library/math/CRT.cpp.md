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


# :x: math/CRT.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/CRT.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00




## Verified with

* :x: <a href="../../verify/test/aoj2659.test.cpp.html">test/aoj2659.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
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
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/CRT.cpp"
// BEGIN CUT
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
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

