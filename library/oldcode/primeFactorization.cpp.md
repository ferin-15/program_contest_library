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


# :warning: oldcode/primeFactorization.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#bf50ccff88ac9b2562bee63cf804278c">oldcode</a>
* <a href="{{ site.github.repository_url }}/blob/master/oldcode/primeFactorization.cpp">View this file on GitHub</a>
    - Last commit date: 2019-10-03 22:20:29+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// mの素因数分解をする O(sqrt(m) + loglog(m))
vector<PII> primeFactorization(ll m) {
    vector<PII> ret;
    for(ll i=2; i*i<=m; ++i) {
        ll cnt = 0;
        while(m%i==0) {
            m /= i;
            cnt++;
        }
        if(cnt) ret.emplace_back(i, cnt);
    }
    if(m > 1) ret.emplace_back(1, m);
    return ret;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "oldcode/primeFactorization.cpp"
// mの素因数分解をする O(sqrt(m) + loglog(m))
vector<PII> primeFactorization(ll m) {
    vector<PII> ret;
    for(ll i=2; i*i<=m; ++i) {
        ll cnt = 0;
        while(m%i==0) {
            m /= i;
            cnt++;
        }
        if(cnt) ret.emplace_back(i, cnt);
    }
    if(m > 1) ret.emplace_back(1, m);
    return ret;
}
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

