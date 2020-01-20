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


# :heavy_check_mark: math/combination.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/combination.cpp">View this file on GitHub</a>
    - Last commit date: 2019-05-14 17:50:56+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj1501.test.cpp.html">test/aoj1501.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// 前計算O(N) クエリO(1)
mint combi(ll N, ll K) {
    const int maxN=5e5; // !!!
    static mint fact[maxN+1]={},factr[maxN+1]={};
    if (fact[0]==0) {
        fact[0] = factr[0] = 1;
        FOR(i, 1, maxN+1) fact[i] = fact[i-1] * i;
        factr[maxN] = fact[maxN].inv();
        for(ll i=maxN-1; i>=0; --i) factr[i] = factr[i+1] * (i+1);
    }
    if(K<0 || K>N) return 0; // !!!
    return factr[K]*fact[N]*factr[N-K];
}

// 前計算O(Klog(mod)) クエリO(K)
mint combi_bigN(ll N, ll K) {
    const int maxN=5e5; // !!!
    static mint inv[maxN+1] = {};
    if(inv[0]==0) {
        inv[0] = 1;
        FOR(i, 1, maxN+1) inv[i] = mint(i).inv();
    }
    if(K<0 || K>N) return 0; // !!!
    mint ret = 1;
    for(;K>0;N--,K--) ret *= N, ret *= inv[K];
    return ret;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/combination.cpp"
// 前計算O(N) クエリO(1)
mint combi(ll N, ll K) {
    const int maxN=5e5; // !!!
    static mint fact[maxN+1]={},factr[maxN+1]={};
    if (fact[0]==0) {
        fact[0] = factr[0] = 1;
        FOR(i, 1, maxN+1) fact[i] = fact[i-1] * i;
        factr[maxN] = fact[maxN].inv();
        for(ll i=maxN-1; i>=0; --i) factr[i] = factr[i+1] * (i+1);
    }
    if(K<0 || K>N) return 0; // !!!
    return factr[K]*fact[N]*factr[N-K];
}

// 前計算O(Klog(mod)) クエリO(K)
mint combi_bigN(ll N, ll K) {
    const int maxN=5e5; // !!!
    static mint inv[maxN+1] = {};
    if(inv[0]==0) {
        inv[0] = 1;
        FOR(i, 1, maxN+1) inv[i] = mint(i).inv();
    }
    if(K<0 || K>N) return 0; // !!!
    mint ret = 1;
    for(;K>0;N--,K--) ret *= N, ret *= inv[K];
    return ret;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

