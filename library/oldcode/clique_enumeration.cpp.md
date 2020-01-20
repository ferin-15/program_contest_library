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


# :warning: oldcode/clique_enumeration.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#bf50ccff88ac9b2562bee63cf804278c">oldcode</a>
* <a href="{{ site.github.repository_url }}/blob/master/oldcode/clique_enumeration.cpp">View this file on GitHub</a>
    - Last commit date: 2019-10-03 22:20:29+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// AOJ 2306 Rabbit Party
// クリーク全列挙
int n, m, ans;
int g[105][105];

void dfs(VI &v) {
  if(v.size() >= 2) {
    int tmp = 0;
    REP(i, v.size()) {
      int t = INF;
      REP(j, v.size()) if(i != j) {
        chmin(t, g[v[i]][v[j]]);
      }
      tmp += t;
    }
    chmax(ans, tmp);
  }

  int last = v.back();
  FOR(i, last+1, n) {
    bool ok = true;
    for(int j: v) {
      if(g[i][j] == 0) {
        ok = false;
        break;
      }
    }
    if(ok) {
      v.PB(i);
      dfs(v);
      v.pop_back();
    }
  }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "oldcode/clique_enumeration.cpp"
// AOJ 2306 Rabbit Party
// クリーク全列挙
int n, m, ans;
int g[105][105];

void dfs(VI &v) {
  if(v.size() >= 2) {
    int tmp = 0;
    REP(i, v.size()) {
      int t = INF;
      REP(j, v.size()) if(i != j) {
        chmin(t, g[v[i]][v[j]]);
      }
      tmp += t;
    }
    chmax(ans, tmp);
  }

  int last = v.back();
  FOR(i, last+1, n) {
    bool ok = true;
    for(int j: v) {
      if(g[i][j] == 0) {
        ok = false;
        break;
      }
    }
    if(ok) {
      v.PB(i);
      dfs(v);
      v.pop_back();
    }
  }
}
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

