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


# :warning: DP/squared_tree_dp.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e2fca8135c2fadca093abd79a6b1c0d2">DP</a>
* <a href="{{ site.github.repository_url }}/blob/master/DP/squared_tree_dp.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 20:24:27+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// 2乗の木DPの雛形
vector<ll> sz(n);
vector<vector<mint>> dp(n);
auto dfs = [&](auto &&self, ll v, ll p) -> void {
    sz[v] = 1;
    dp[v].resize(sz[v]+1);
    dp[v][1] = 1;
    for(auto to: g[v]) if(to!=p) {
        self(self, to, v);
        vector<mint> merged(2*(sz[v]+sz[to])+1);
        REP(i, sz[v]*2+1) REP(j, sz[to]*2+1) {
            merged[i+j] += dp[v][i] * dp[to][j];
        }
        sz[v] += sz[to];
        dp[v] = move(merged);
    }
    dp[v][0] = 1;
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "DP/squared_tree_dp.cpp"
// 2乗の木DPの雛形
vector<ll> sz(n);
vector<vector<mint>> dp(n);
auto dfs = [&](auto &&self, ll v, ll p) -> void {
    sz[v] = 1;
    dp[v].resize(sz[v]+1);
    dp[v][1] = 1;
    for(auto to: g[v]) if(to!=p) {
        self(self, to, v);
        vector<mint> merged(2*(sz[v]+sz[to])+1);
        REP(i, sz[v]*2+1) REP(j, sz[to]*2+1) {
            merged[i+j] += dp[v][i] * dp[to][j];
        }
        sz[v] += sz[to];
        dp[v] = move(merged);
    }
    dp[v][0] = 1;
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

