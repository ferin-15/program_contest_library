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


# :warning: math/baby_step_giant_step.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/baby_step_giant_step.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 23:46:01+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
// x^k = y (mod m) となるkを求める O(sqrt(m))
ll baby_step_giant_step(ll x, ll y, ll m) {
    // Baby-step
    // mp[x^i] = i
    unordered_map<ll,ll> mp;
    mp[1] = 0;
    ll z = 1;
    const ll m_sqrt = sqrt(m)+1;
    REP(i, m_sqrt) {
        (z *= x) %= m;
        mp[z] = i+1;
    }
    if(mp.find(y) != mp.end()) return mp[y];

    // Giant-step 
    ll r = modpow(z, m-2, m);   // x^(-m_sqrt)
    FOR(i, 1, m_sqrt+1) {
        (y *= r) %= m;
        if(mp.find(y) != mp.end()) return mp[y] + i*m_sqrt;
    }

    return -1;
}
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/baby_step_giant_step.cpp"
// BEGIN CUT
// x^k = y (mod m) となるkを求める O(sqrt(m))
ll baby_step_giant_step(ll x, ll y, ll m) {
    // Baby-step
    // mp[x^i] = i
    unordered_map<ll,ll> mp;
    mp[1] = 0;
    ll z = 1;
    const ll m_sqrt = sqrt(m)+1;
    REP(i, m_sqrt) {
        (z *= x) %= m;
        mp[z] = i+1;
    }
    if(mp.find(y) != mp.end()) return mp[y];

    // Giant-step 
    ll r = modpow(z, m-2, m);   // x^(-m_sqrt)
    FOR(i, 1, m_sqrt+1) {
        (y *= r) %= m;
        if(mp.find(y) != mp.end()) return mp[y] + i*m_sqrt;
    }

    return -1;
}
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

