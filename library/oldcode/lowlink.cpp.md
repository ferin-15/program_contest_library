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


# :warning: oldcode/lowlink.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#bf50ccff88ac9b2562bee63cf804278c">oldcode</a>
* <a href="{{ site.github.repository_url }}/blob/master/oldcode/lowlink.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 04:35:05+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// hecさんの写経 自分ではverifyしてない
// n頂点のグラフgについてlow_linkを求める
VI ord(n, -1), low(n, -1), par(n, -1);
vector<bool> root(n, false);
auto low_link = [&]() {
  int k = 0;

  function<void(int,int,int&)> dfs = [&](int v, int p, int &k) {
    ord[v] = k++, low[v] = ord[v], par[v] = p;
    for(auto e: g[v]) {
      if(e.first == p) continue;
      if(ord[e.first] == -1) {
        dfs(e.first, v, k);
        chmin(low[v], low[e.first]);
      } else {
        chmin(low[v], low[e.first]);
      }
    }
  };

  REP(i, n) if(ord[i] == -1) dfs(i, -1, k), root[i] = true;
};
low_link();
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "oldcode/lowlink.cpp"
// hecさんの写経 自分ではverifyしてない
// n頂点のグラフgについてlow_linkを求める
VI ord(n, -1), low(n, -1), par(n, -1);
vector<bool> root(n, false);
auto low_link = [&]() {
  int k = 0;

  function<void(int,int,int&)> dfs = [&](int v, int p, int &k) {
    ord[v] = k++, low[v] = ord[v], par[v] = p;
    for(auto e: g[v]) {
      if(e.first == p) continue;
      if(ord[e.first] == -1) {
        dfs(e.first, v, k);
        chmin(low[v], low[e.first]);
      } else {
        chmin(low[v], low[e.first]);
      }
    }
  };

  REP(i, n) if(ord[i] == -1) dfs(i, -1, k), root[i] = true;
};
low_link();
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

