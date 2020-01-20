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


# :warning: oldcode/ext_lucas.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#bf50ccff88ac9b2562bee63cf804278c">oldcode</a>
* <a href="{{ site.github.repository_url }}/blob/master/oldcode/ext_lucas.cpp">View this file on GitHub</a>
    - Last commit date: 2019-10-03 22:20:29+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
ll fact[1000010], ifact[1000010];
void makeFac(ll p, ll q) {
  ll pr = 1;
  REP(i, q) pr *= p;
  fact[0] = ifact[0] = 1;
  FOR(i, 1, pr+1) {
    if(i%p == 0) {
      fact[i] = fact[i-1];
    } else {
      fact[i] = fact[i-1] * i % pr;
    }
    ifact[i] = inv(fact[i], pr);
  }
}

ll C(ll n, ll r, ll p, ll q) {
  if(n < 0 || r < 0 || r > n) return 0;
  // pr = p^q
  int pr = 1;
  REP(i, q) pr *= p;

  ll z = n-r;
  int e0 = 0;
  for(ll u=n/p;u;u/=p) e0 += u;
  for(ll u=r/p;u;u/=p) e0 -= u;
  for(ll u=z/p;u;u/=p) e0 -= u;
  int em = 0;
  for(ll u=n/pr;u;u/=p) em += u;
  for(ll u=r/pr;u;u/=p) em -= u;
  for(ll u=z/pr;u;u/=p) em -= u;

  ll ret = 1;
  while(n > 0) {
    ret = ret*fact[n%pr]%pr*ifact[r%pr]%pr*ifact[z%pr]%pr;
    n /= p; r /= p; z /= p;
  }
  (ret *= binpow(p, e0, pr)) %= pr;
  if(!(p==2 && q >= 3) && em%2) ret = (pr-ret) % pr;
  return ret;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "oldcode/ext_lucas.cpp"
ll fact[1000010], ifact[1000010];
void makeFac(ll p, ll q) {
  ll pr = 1;
  REP(i, q) pr *= p;
  fact[0] = ifact[0] = 1;
  FOR(i, 1, pr+1) {
    if(i%p == 0) {
      fact[i] = fact[i-1];
    } else {
      fact[i] = fact[i-1] * i % pr;
    }
    ifact[i] = inv(fact[i], pr);
  }
}

ll C(ll n, ll r, ll p, ll q) {
  if(n < 0 || r < 0 || r > n) return 0;
  // pr = p^q
  int pr = 1;
  REP(i, q) pr *= p;

  ll z = n-r;
  int e0 = 0;
  for(ll u=n/p;u;u/=p) e0 += u;
  for(ll u=r/p;u;u/=p) e0 -= u;
  for(ll u=z/p;u;u/=p) e0 -= u;
  int em = 0;
  for(ll u=n/pr;u;u/=p) em += u;
  for(ll u=r/pr;u;u/=p) em -= u;
  for(ll u=z/pr;u;u/=p) em -= u;

  ll ret = 1;
  while(n > 0) {
    ret = ret*fact[n%pr]%pr*ifact[r%pr]%pr*ifact[z%pr]%pr;
    n /= p; r /= p; z /= p;
  }
  (ret *= binpow(p, e0, pr)) %= pr;
  if(!(p==2 && q >= 3) && em%2) ret = (pr-ret) % pr;
  return ret;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

