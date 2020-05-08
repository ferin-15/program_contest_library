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


# :warning: math/floyd_cycle_find.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/floyd_cycle_find.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 20:24:27+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// 初項s0でs_n=next(s_{n-1})となる数列
// s_i = s_{i+period} (i>=start) となるようなstart, periodを探索
// time: O(start+period) space: O(1)
template<class F>
PII floyd_cycle_find(const ll s0, F next) {
    ll t = 0, h = 1, st = s0, sh = next(s0);
    for(; st!=sh; t++, st=next(st), h+=2, sh=next(next(sh)));
    ll start = 0;
    sh = s0; 
    REP(i, h-t) sh = next(sh);
    for(st=s0; st!=sh; ++start, st=next(st), sh=next(sh));
    ll period = 1;
    for(sh=next(st); st!=sh; ++period, sh=next(sh));
    
    return make_pair(start, period);
}

/* 線形合同法などに使われるらしい
const ll s0 = 1611516670;
auto next = [](ll s) { 
    constexpr ll m = 1LL<<40;
    return (s + (s>>20) + 12345) & (m-1); 
};
auto [start, period] = floyd_cycle_find(s0, next); 
*/
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/floyd_cycle_find.cpp"
// 初項s0でs_n=next(s_{n-1})となる数列
// s_i = s_{i+period} (i>=start) となるようなstart, periodを探索
// time: O(start+period) space: O(1)
template<class F>
PII floyd_cycle_find(const ll s0, F next) {
    ll t = 0, h = 1, st = s0, sh = next(s0);
    for(; st!=sh; t++, st=next(st), h+=2, sh=next(next(sh)));
    ll start = 0;
    sh = s0; 
    REP(i, h-t) sh = next(sh);
    for(st=s0; st!=sh; ++start, st=next(st), sh=next(sh));
    ll period = 1;
    for(sh=next(st); st!=sh; ++period, sh=next(sh));
    
    return make_pair(start, period);
}

/* 線形合同法などに使われるらしい
const ll s0 = 1611516670;
auto next = [](ll s) { 
    constexpr ll m = 1LL<<40;
    return (s + (s>>20) + 12345) & (m-1); 
};
auto [start, period] = floyd_cycle_find(s0, next); 
*/

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

