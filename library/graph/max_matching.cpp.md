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


# :heavy_check_mark: graph/max_matching.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/max_matching.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj2983.test.cpp.html">test/aoj2983.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
ll max_matching(ll n, vector<PII> edges) {
    mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<ll> dist(1, MOD-1);

    matrix mat(n, n);
    for(auto e: edges) {
        ll r = dist(mt);
        mat.get(e.first, e.second) = r;
        mat.get(e.second, e.first) = MOD-r;
    }
    return (gauss_jordan(mat)+1)/2;
}
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/max_matching.cpp"
// BEGIN CUT
ll max_matching(ll n, vector<PII> edges) {
    mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<ll> dist(1, MOD-1);

    matrix mat(n, n);
    for(auto e: edges) {
        ll r = dist(mt);
        mat.get(e.first, e.second) = r;
        mat.get(e.second, e.first) = MOD-r;
    }
    return (gauss_jordan(mat)+1)/2;
}
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

