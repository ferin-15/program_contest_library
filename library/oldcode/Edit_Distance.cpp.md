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


# :warning: oldcode/Edit_Distance.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#bf50ccff88ac9b2562bee63cf804278c">oldcode</a>
* <a href="{{ site.github.repository_url }}/blob/master/oldcode/Edit_Distance.cpp">View this file on GitHub</a>
    - Last commit date: 2019-10-03 22:20:29+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
int dp[1010][1010];
signed main(void)
{
  string s, t;
  cin >> t >> s;
  const int n = s.size(), m = t.size();
  REP(i, n+1) REP(j, m+1) {
    if(i == 0) dp[i][j] = j;
    else if(j == 0) dp[i][j] = i;
    else {
      if(s[i-1] == t[j-1]) {
        dp[i][j] = min({dp[i-1][j-1], dp[i-1][j]+1, dp[i][j-1]+1});
      } else {
        dp[i][j] = min({dp[i-1][j] + 1, dp[i][j-1] + 1, dp[i-1][j-1]+1});
      }
    }
  }
  cout << dp[n][m] << endl;
  return 0;
}
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "oldcode/Edit_Distance.cpp"
// BEGIN CUT
int dp[1010][1010];
signed main(void)
{
  string s, t;
  cin >> t >> s;
  const int n = s.size(), m = t.size();
  REP(i, n+1) REP(j, m+1) {
    if(i == 0) dp[i][j] = j;
    else if(j == 0) dp[i][j] = i;
    else {
      if(s[i-1] == t[j-1]) {
        dp[i][j] = min({dp[i-1][j-1], dp[i-1][j]+1, dp[i][j-1]+1});
      } else {
        dp[i][j] = min({dp[i-1][j] + 1, dp[i][j-1] + 1, dp[i-1][j-1]+1});
      }
    }
  }
  cout << dp[n][m] << endl;
  return 0;
}
// END CUT
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

