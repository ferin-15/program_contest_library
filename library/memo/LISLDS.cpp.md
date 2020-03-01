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


# :warning: memo/LISLDS.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d504a5ea65b088497578bdd812714d51">memo</a>
* <a href="{{ site.github.repository_url }}/blob/master/memo/LISLDS.cpp">View this file on GitHub</a>
    - Last commit date: 2019-03-03 19:42:23+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// LIS and LDS
// LISがA、LDSがBとなるような順列を構築しろ
// A + B <= N+1, AB >= N が構築できる必要十分条件
vector<ll> LISLDS(ll N, ll A, ll B) {
  vector<ll> res;
  for (ll i = B-1; i >= 0; --i) res.push_back(i);
  
  if (A == 1) return res;
  
  ll rem = N - B;
  ll p = rem / (A-1);
  ll r = rem % (A-1);
  
  ll b = r;
  ll c = A-1-r;
  
  for (ll i = 0; i < b; ++i) {
    ll size = res.size();
    for (ll j = 0; j < p+1; ++j) {
      res.push_back(size + p - j);
    }
  }
  for (ll i = 0; i < c; ++i) {
    ll size = res.size();
    for (ll j = 0; j < p; ++j) {
      res.push_back(size + p-1 - j);
    }
  }
  
  return res;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "memo/LISLDS.cpp"
// LIS and LDS
// LISがA、LDSがBとなるような順列を構築しろ
// A + B <= N+1, AB >= N が構築できる必要十分条件
vector<ll> LISLDS(ll N, ll A, ll B) {
  vector<ll> res;
  for (ll i = B-1; i >= 0; --i) res.push_back(i);
  
  if (A == 1) return res;
  
  ll rem = N - B;
  ll p = rem / (A-1);
  ll r = rem % (A-1);
  
  ll b = r;
  ll c = A-1-r;
  
  for (ll i = 0; i < b; ++i) {
    ll size = res.size();
    for (ll j = 0; j < p+1; ++j) {
      res.push_back(size + p - j);
    }
  }
  for (ll i = 0; i < c; ++i) {
    ll size = res.size();
    for (ll j = 0; j < p; ++j) {
      res.push_back(size + p-1 - j);
    }
  }
  
  return res;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

