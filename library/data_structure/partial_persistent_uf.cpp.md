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


# :x: data_structure/partial_persistent_uf.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/partial_persistent_uf.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-20 15:31:47+09:00




## Verified with

* :x: <a href="../../verify/test/aoj0575_0.test.cpp.html">test/aoj0575_0.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
struct partial_persistent_uf {
    int now;
    vector<int> time, par, rank;
    vector<vector<PII>> sz;
    partial_persistent_uf(int n) : now(0), time(n, 1<<30), par(n, 1), sz(n, vector<PII>({{0,1}})) {}
    // t(1-indexed) 回目までuniteしたときのxの根
    int find(int x, int t) {
        if(time[x] > t) return x;
        return find(par[x], t);
    }
    int unite(int x, int y) {
        ++now;
        x = find(x, now), y = find(y, now);
        if(x == y) return now;
        if(par[x] < par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        time[y] = now;
        sz[x].emplace_back(now, par[x]);
        return now;
    }
    bool same(int x, int y, int t) { 
        return find(x, t) == find(y, t);
    }
    int size(int x, int t) { 
        x = find(x, t);
        return prev(upper_bound(ALL(sz[x]), PII(t, INF)))->second; 
    }
};
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/partial_persistent_uf.cpp"
// BEGIN CUT
struct partial_persistent_uf {
    int now;
    vector<int> time, par, rank;
    vector<vector<PII>> sz;
    partial_persistent_uf(int n) : now(0), time(n, 1<<30), par(n, 1), sz(n, vector<PII>({{0,1}})) {}
    // t(1-indexed) 回目までuniteしたときのxの根
    int find(int x, int t) {
        if(time[x] > t) return x;
        return find(par[x], t);
    }
    int unite(int x, int y) {
        ++now;
        x = find(x, now), y = find(y, now);
        if(x == y) return now;
        if(par[x] < par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        time[y] = now;
        sz[x].emplace_back(now, par[x]);
        return now;
    }
    bool same(int x, int y, int t) { 
        return find(x, t) == find(y, t);
    }
    int size(int x, int t) { 
        x = find(x, t);
        return prev(upper_bound(ALL(sz[x]), PII(t, INF)))->second; 
    }
};
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

