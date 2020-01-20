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


# :warning: oldcode/num_limit_knapsack.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#bf50ccff88ac9b2562bee63cf804278c">oldcode</a>
* <a href="{{ site.github.repository_url }}/blob/master/oldcode/num_limit_knapsack.cpp">View this file on GitHub</a>
    - Last commit date: 2019-10-03 22:20:29+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// 重さX[i]、価値Y[i]、個数上限Z[i] としたときの個数制限付きナップザック
// O(N^2maxy^2logN)
// ARC096-F でverify

const int maxy = 50;
// dp[i] = (価値がiのときの最小の重さ)
VI dp(maxy*maxy*maxy+5, INF);
// i番目のアイテムについて重さと価値がそれぞれ(X[i],Y[i])(2X[i],Y[i])…(2^kX[i],2^kY[i])が一つずつ存在すると考える
dp[0] = 0;
REP(i, n) {
  int num = min(maxy, Z[idx[i]]);
  for(int k=1; num; k<<=1) {
    int mul = min(k, num);
    for(int j=maxy*maxy*maxy; j>=0; --j) {
      if(j+mul*Y[idx[i]] <= maxy*maxy*maxy) {
        chmin(dp[j+mul*Y[idx[i]]], dp[j] + mul*X[idx[i]]);
      }
    }
    num -= mul;
  }
}

int ans = 0;
REP(i, maxy*maxy*maxy+1) {
  // 価値iとして残りをgreedyに決める
  if(dp[i]>x) continue;
  int ret=i, w = x-dp[i];
  REP(j, n) {
    // cnt個取る
    int cnt = Z[idx[j]] - min(maxy, Z[idx[j]]);
    chmin(cnt, w/X[idx[j]]);
    ret += cnt*Y[idx[j]];
    w -= cnt*X[idx[j]];
  }
  chmax(ans, ret);
}
cout << ans << endl;

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "oldcode/num_limit_knapsack.cpp"
// 重さX[i]、価値Y[i]、個数上限Z[i] としたときの個数制限付きナップザック
// O(N^2maxy^2logN)
// ARC096-F でverify

const int maxy = 50;
// dp[i] = (価値がiのときの最小の重さ)
VI dp(maxy*maxy*maxy+5, INF);
// i番目のアイテムについて重さと価値がそれぞれ(X[i],Y[i])(2X[i],Y[i])…(2^kX[i],2^kY[i])が一つずつ存在すると考える
dp[0] = 0;
REP(i, n) {
  int num = min(maxy, Z[idx[i]]);
  for(int k=1; num; k<<=1) {
    int mul = min(k, num);
    for(int j=maxy*maxy*maxy; j>=0; --j) {
      if(j+mul*Y[idx[i]] <= maxy*maxy*maxy) {
        chmin(dp[j+mul*Y[idx[i]]], dp[j] + mul*X[idx[i]]);
      }
    }
    num -= mul;
  }
}

int ans = 0;
REP(i, maxy*maxy*maxy+1) {
  // 価値iとして残りをgreedyに決める
  if(dp[i]>x) continue;
  int ret=i, w = x-dp[i];
  REP(j, n) {
    // cnt個取る
    int cnt = Z[idx[j]] - min(maxy, Z[idx[j]]);
    chmin(cnt, w/X[idx[j]]);
    ret += cnt*Y[idx[j]];
    w -= cnt*X[idx[j]];
  }
  chmax(ans, ret);
}
cout << ans << endl;

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

