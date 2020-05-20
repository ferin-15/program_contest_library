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


# :warning: math/gcd_conv.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/gcd_conv.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-20 15:31:47+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
// g(x) = \sum_{yはxの倍数} f(y)
template<class T>
void fzt_div_upper(vector<T> &a) {
    const ll n = a.size();
    FOR(i, 1, n) {
        for(ll j=2*i; j<n; j+=i) {
            a[i] += a[j];
        }
    }
}
// f(y) = \sum_{yはxの倍数} g(x)
template<class T>
void fmt_div_upper(vector<T> &a) {
    const ll n = a.size();
    for(ll i=n-1; i>=1; --i) {
        for(ll j=2*i; j<n; j+=i) {
            a[i] -= a[j];
        }
    }
}
// c(z) = \sum_{gcd(x,y)=z} a(x)a(y)
template<class T>
void conv_gcd(vector<T> &a) {
    fzt_div_upper(a);
    REP(i, a.size()) a[i] *= a[i];
    fmt_div_upper(a);
}
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/gcd_conv.cpp"
// BEGIN CUT
// g(x) = \sum_{yはxの倍数} f(y)
template<class T>
void fzt_div_upper(vector<T> &a) {
    const ll n = a.size();
    FOR(i, 1, n) {
        for(ll j=2*i; j<n; j+=i) {
            a[i] += a[j];
        }
    }
}
// f(y) = \sum_{yはxの倍数} g(x)
template<class T>
void fmt_div_upper(vector<T> &a) {
    const ll n = a.size();
    for(ll i=n-1; i>=1; --i) {
        for(ll j=2*i; j<n; j+=i) {
            a[i] -= a[j];
        }
    }
}
// c(z) = \sum_{gcd(x,y)=z} a(x)a(y)
template<class T>
void conv_gcd(vector<T> &a) {
    fzt_div_upper(a);
    REP(i, a.size()) a[i] *= a[i];
    fmt_div_upper(a);
}
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

