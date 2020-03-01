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


# :heavy_check_mark: data_structure/partial_persistent_uf.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/partial_persistent_uf.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj0575_0.test.cpp.html">test/aoj0575_0.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
// find:O(logN) unite:O(logN)
struct partialPersistentUF {
    const static int MAX_N = 100010;
    unordered_map<int, int> par[MAX_N];
    int rank[MAX_N];
    int fin[MAX_N];
    int idx;
    partialPersistentUF() { init(); }
    partialPersistentUF(int n) { init(n); }
    void init(int n=MAX_N) {
        idx = 0;
        REP(i, n) par[i][0] = i, rank[i] = 1, fin[i] = 0;
    }
    // t(1-indexed)回目までのuniteでのxの親
    int find(int x, int t) {
        if(t >= fin[x] && par[x][fin[x]] != x) return find(par[x][fin[x]], t);
        return x;
    }
    void unite(int x, int y) {
        x = find(x, idx);
        y = find(y, idx);
        idx++;
        if(x == y) return;
        if(rank[x] < rank[y]) par[x][idx] = y, fin[x] = idx;
        else {
          par[y][idx] = x, fin[y] = idx;
          if(rank[x] == rank[y]) rank[x]++;
        }
    }
    bool same(int x, int y, int t) { return find(x, t) == find(y, t); }
};
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/partial_persistent_uf.cpp"
// BEGIN CUT
// find:O(logN) unite:O(logN)
struct partialPersistentUF {
    const static int MAX_N = 100010;
    unordered_map<int, int> par[MAX_N];
    int rank[MAX_N];
    int fin[MAX_N];
    int idx;
    partialPersistentUF() { init(); }
    partialPersistentUF(int n) { init(n); }
    void init(int n=MAX_N) {
        idx = 0;
        REP(i, n) par[i][0] = i, rank[i] = 1, fin[i] = 0;
    }
    // t(1-indexed)回目までのuniteでのxの親
    int find(int x, int t) {
        if(t >= fin[x] && par[x][fin[x]] != x) return find(par[x][fin[x]], t);
        return x;
    }
    void unite(int x, int y) {
        x = find(x, idx);
        y = find(y, idx);
        idx++;
        if(x == y) return;
        if(rank[x] < rank[y]) par[x][idx] = y, fin[x] = idx;
        else {
          par[y][idx] = x, fin[y] = idx;
          if(rank[x] == rank[y]) rank[x]++;
        }
    }
    bool same(int x, int y, int t) { return find(x, t) == find(y, t); }
};
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

