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


# :warning: oldcode/stirling.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#bf50ccff88ac9b2562bee63cf804278c">oldcode</a>
* <a href="{{ site.github.repository_url }}/blob/master/oldcode/stirling.cpp">View this file on GitHub</a>
    - Last commit date: 2019-10-03 22:20:29+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// dp[i][j] = i個をj個のdisjointで全てを覆うようなグループに分割するパターン数
VVI dp(n+1, VI(n+1));
REP(i, n+1) {
  dp[i][0] = 1;
  FOR(j, 1, i+1) {
    dp[i][j] = (dp[i-1][j]*j + dp[i-1][j-1]) % MOD;
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "oldcode/stirling.cpp"
// dp[i][j] = i個をj個のdisjointで全てを覆うようなグループに分割するパターン数
VVI dp(n+1, VI(n+1));
REP(i, n+1) {
  dp[i][0] = 1;
  FOR(j, 1, i+1) {
    dp[i][j] = (dp[i-1][j]*j + dp[i-1][j-1]) % MOD;
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

