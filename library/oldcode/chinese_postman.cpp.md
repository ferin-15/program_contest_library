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


# :warning: oldcode/chinese_postman.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#bf50ccff88ac9b2562bee63cf804278c">oldcode</a>
* <a href="{{ site.github.repository_url }}/blob/master/oldcode/chinese_postman.cpp">View this file on GitHub</a>
    - Last commit date: 2019-10-03 22:20:29+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
int d[17][17], f[17];
signed main(void)
{
  int v, e, tot = 0;
  cin >> v >> e;
  REP(i, v) REP(j, v) d[i][j] = INF;
  REP(i, e) {
    int a, b, c;
    cin >> a >> b >> c;
    d[a][b] = min(d[a][b], c); d[b][a] = min(d[b][a], c);
    f[a]++; f[b]++;
    tot += c;
  }
  VI o;
  REP(i, v) if(f[i]%2) o.push_back(i);
  REP(k, v) REP(i, v) REP(j, v) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
  int dp[1<<16], os = o.size();
  fill(dp, dp+(1<<os), INF);
  dp[0] = 0;
  REP(s, 1<<os) REP(i, os) if(~s>>i&1) REP(j, i) if(~s>>j&1) {
    dp[s|1<<i|1<<j] = min(dp[s|1<<i|1<<j], dp[s] + d[o[i]][o[j]]);
  }
  cout << tot + dp[(1<<os)-1] << endl;
  return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "oldcode/chinese_postman.cpp"
int d[17][17], f[17];
signed main(void)
{
  int v, e, tot = 0;
  cin >> v >> e;
  REP(i, v) REP(j, v) d[i][j] = INF;
  REP(i, e) {
    int a, b, c;
    cin >> a >> b >> c;
    d[a][b] = min(d[a][b], c); d[b][a] = min(d[b][a], c);
    f[a]++; f[b]++;
    tot += c;
  }
  VI o;
  REP(i, v) if(f[i]%2) o.push_back(i);
  REP(k, v) REP(i, v) REP(j, v) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
  int dp[1<<16], os = o.size();
  fill(dp, dp+(1<<os), INF);
  dp[0] = 0;
  REP(s, 1<<os) REP(i, os) if(~s>>i&1) REP(j, i) if(~s>>j&1) {
    dp[s|1<<i|1<<j] = min(dp[s|1<<i|1<<j], dp[s] + d[o[i]][o[j]]);
  }
  cout << tot + dp[(1<<os)-1] << endl;
  return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

