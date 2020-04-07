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


# :x: math/sum_of_powers.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/sum_of_powers.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00




## Verified with

* :x: <a href="../../verify/test/aoj2987.test.cpp.html">test/aoj2987.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
// \sum_{i=0}^{n-1} i^k O(k^2)
// kが固定でクエリがいっぱいならベルヌーイ数を前計算で高速化
mint sum_of_powers(ll n, ll k) {
    vector<mint> b(k+1), po(k+2);
    b[0] = po[0] = 1;
    FOR(i, 1, k+2) po[i] = po[i-1] * n;
    FOR(i, 1, k+1) {
        REP(j, i) b[i] += combi(i+1, j) * b[j];
        b[i] /= -(i+1);
    }
    mint sum = 0;
    REP(i, k+1) sum += combi(k+1, i) * b[i] * po[k+1-i];
    return sum / (k+1);
}
// END CUT

// FPSとかでベルヌーイ数をklogkとかあるっぽい…？
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/sum_of_powers.cpp"
// BEGIN CUT
// \sum_{i=0}^{n-1} i^k O(k^2)
// kが固定でクエリがいっぱいならベルヌーイ数を前計算で高速化
mint sum_of_powers(ll n, ll k) {
    vector<mint> b(k+1), po(k+2);
    b[0] = po[0] = 1;
    FOR(i, 1, k+2) po[i] = po[i-1] * n;
    FOR(i, 1, k+1) {
        REP(j, i) b[i] += combi(i+1, j) * b[j];
        b[i] /= -(i+1);
    }
    mint sum = 0;
    REP(i, k+1) sum += combi(k+1, i) * b[i] * po[k+1-i];
    return sum / (k+1);
}
// END CUT

// FPSとかでベルヌーイ数をklogkとかあるっぽい…？

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

