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


# :warning: math/fraction.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/fraction.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
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
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/fraction.cpp"
// BEGIN CUT
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
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

