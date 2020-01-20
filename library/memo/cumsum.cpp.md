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


# :warning: memo/cumsum.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d504a5ea65b088497578bdd812714d51">memo</a>
* <a href="{{ site.github.repository_url }}/blob/master/memo/cumsum.cpp">View this file on GitHub</a>
    - Last commit date: 2018-09-27 01:44:20+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
const int maxh = 35, maxw = 35;
int csum[maxh][maxw];
void init(VVI vec) {
  assert(vec.size());
  REP(i, vec.size()) REP(j, vec[0].size()) {
    if(!i && !j) csum[i][j] = vec[i][j];
    else if(!i) csum[i][j] = csum[i][j-1] + vec[i][j];
    else if(!j) csum[i][j] = csum[i-1][j] + vec[i][j];
    else csum[i][j] = csum[i-1][j] + csum[i][j-1] - csum[i-1][j-1] + vec[i][j];
  }
}
// 閉区間, 0-indexedで矩形範囲の合計
int cumsum(int sx, int sy, int gx, int gy) {
  if(!sx && !sy) return csum[gy][gx];
  if(!sx) return csum[gy][gx] - csum[sy-1][gx];
  if(!sy) return csum[gy][gx] - csum[gy][sx-1];
  return csum[gy][gx] - csum[gy][sx-1] - csum[sy-1][gx] + csum[sy-1][sx-1];
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "memo/cumsum.cpp"
const int maxh = 35, maxw = 35;
int csum[maxh][maxw];
void init(VVI vec) {
  assert(vec.size());
  REP(i, vec.size()) REP(j, vec[0].size()) {
    if(!i && !j) csum[i][j] = vec[i][j];
    else if(!i) csum[i][j] = csum[i][j-1] + vec[i][j];
    else if(!j) csum[i][j] = csum[i-1][j] + vec[i][j];
    else csum[i][j] = csum[i-1][j] + csum[i][j-1] - csum[i-1][j-1] + vec[i][j];
  }
}
// 閉区間, 0-indexedで矩形範囲の合計
int cumsum(int sx, int sy, int gx, int gy) {
  if(!sx && !sy) return csum[gy][gx];
  if(!sx) return csum[gy][gx] - csum[sy-1][gx];
  if(!sy) return csum[gy][gx] - csum[gy][sx-1];
  return csum[gy][gx] - csum[gy][sx-1] - csum[sy-1][gx] + csum[sy-1][sx-1];
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

