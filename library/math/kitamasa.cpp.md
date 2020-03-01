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


# :warning: math/kitamasa.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/kitamasa.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
// 数列の初項k項aと漸化式の係数dが与えられる
// a_nをO(K^2logN)で求める
vector<ll> dfs(vector<ll> a, vector<ll> d, ll n) {
    ll k = d.size();
    if(n == k) return d;
    vector<ll> ret(k);
    if(n&1 || n<k*2) {
        auto v = dfs(a, d, n-1);
        ret[0] = v[k-1] * a[0] % MOD;
        FOR(i, 1, k) ret[i] = (v[i-1] + v[k-1] * a[i] % MOD) % MOD;
    } else {
        auto v = dfs(a, d, n/2);
        vector<vector<ll>> f(k, vector<ll>(k));
        f[0] = v;
        FOR(i, 1, k) {
            f[i][0] = f[i-1][k-1] * a[0] % MOD;
            FOR(j, 1, k) f[i][j] = (f[i-1][j-1] + f[i-1][k-1] * a[j] % MOD) % MOD;
        }
        REP(i, k) REP(j, k) (ret[i] += v[j] * f[j][i] % MOD) %= MOD;
    }
    return ret;
}
ll kitamasa(vector<ll> a, vector<ll> d, ll n) {
    auto ret = dfs(a, d, n);
    ll ans = 0;
    REP(i, d.size()) (ans += d[i] * ret[i]) %= MOD;
    return ans;
}
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/kitamasa.cpp"
// BEGIN CUT
// 数列の初項k項aと漸化式の係数dが与えられる
// a_nをO(K^2logN)で求める
vector<ll> dfs(vector<ll> a, vector<ll> d, ll n) {
    ll k = d.size();
    if(n == k) return d;
    vector<ll> ret(k);
    if(n&1 || n<k*2) {
        auto v = dfs(a, d, n-1);
        ret[0] = v[k-1] * a[0] % MOD;
        FOR(i, 1, k) ret[i] = (v[i-1] + v[k-1] * a[i] % MOD) % MOD;
    } else {
        auto v = dfs(a, d, n/2);
        vector<vector<ll>> f(k, vector<ll>(k));
        f[0] = v;
        FOR(i, 1, k) {
            f[i][0] = f[i-1][k-1] * a[0] % MOD;
            FOR(j, 1, k) f[i][j] = (f[i-1][j-1] + f[i-1][k-1] * a[j] % MOD) % MOD;
        }
        REP(i, k) REP(j, k) (ret[i] += v[j] * f[j][i] % MOD) %= MOD;
    }
    return ret;
}
ll kitamasa(vector<ll> a, vector<ll> d, ll n) {
    auto ret = dfs(a, d, n);
    ll ans = 0;
    REP(i, d.size()) (ans += d[i] * ret[i]) %= MOD;
    return ans;
}
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

