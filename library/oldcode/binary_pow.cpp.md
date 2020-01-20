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


# :warning: oldcode/binary_pow.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#bf50ccff88ac9b2562bee63cf804278c">oldcode</a>
* <a href="{{ site.github.repository_url }}/blob/master/oldcode/binary_pow.cpp">View this file on GitHub</a>
    - Last commit date: 2019-10-03 22:20:29+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
ll binpow(ll x, ll e) {
  ll ret = 1, p = x;
  while(e > 0) {
    if(e&1) {(ret *= p) %= MOD; e--;}
    else {(p *= p) %= MOD; e /= 2;} 
  }
  return ret;
}

// ダブリング O(funcの計算量*log(e))
template<typename T=ll, typename F=function<T(T,T)>>
T binpow(T x, ll e, F func=[](T a, T b){return a*b%MOD;}, T d=1) {
  T ret = d, p = x;
  while(e > 0) {
    if(e&1) {ret = func(ret, p); e--;}
    else {p = func(p, p); e /= 2;} 
  }
  return ret;
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "oldcode/binary_pow.cpp"
ll binpow(ll x, ll e) {
  ll ret = 1, p = x;
  while(e > 0) {
    if(e&1) {(ret *= p) %= MOD; e--;}
    else {(p *= p) %= MOD; e /= 2;} 
  }
  return ret;
}

// ダブリング O(funcの計算量*log(e))
template<typename T=ll, typename F=function<T(T,T)>>
T binpow(T x, ll e, F func=[](T a, T b){return a*b%MOD;}, T d=1) {
  T ret = d, p = x;
  while(e > 0) {
    if(e&1) {ret = func(ret, p); e--;}
    else {p = func(p, p); e /= 2;} 
  }
  return ret;
};
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

