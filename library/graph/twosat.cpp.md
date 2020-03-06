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


# :heavy_check_mark: graph/twosat.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/twosat.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00




## Required by

* :warning: <a href="../test/aoj2991.memo.cpp.html">test/aoj2991.memo.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/yosupo-2SAT.test.cpp.html">test/yosupo-2SAT.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
struct twoSAT {
    ll n;
    SCC graph;
    vector<bool> ans;
    twoSAT(ll n) : n(n), graph(n*2), ans(n) {}
    // not なら false
    void add(pair<ll,bool> a0, pair<ll,bool> b0) {
        ll a = a0.first, ar = (a0.first+n)%(2*n);
        ll b = b0.first, br = (b0.first+n)%(2*n);
        if(!a0.second) swap(a, ar);
        if(!b0.second) swap(b, br);
        graph.add_edge(ar, b);
        graph.add_edge(br, a);
    }
    bool solve() {
        graph.scc();
        REP(i, n) if(graph.cmp[i] == graph.cmp[n+i]) return false;
        REP(i, n) ans[i] = graph.cmp[i] > graph.cmp[n+i];
        return true;
    }
};
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/twosat.cpp"
// BEGIN CUT
struct twoSAT {
    ll n;
    SCC graph;
    vector<bool> ans;
    twoSAT(ll n) : n(n), graph(n*2), ans(n) {}
    // not なら false
    void add(pair<ll,bool> a0, pair<ll,bool> b0) {
        ll a = a0.first, ar = (a0.first+n)%(2*n);
        ll b = b0.first, br = (b0.first+n)%(2*n);
        if(!a0.second) swap(a, ar);
        if(!b0.second) swap(b, br);
        graph.add_edge(ar, b);
        graph.add_edge(br, a);
    }
    bool solve() {
        graph.scc();
        REP(i, n) if(graph.cmp[i] == graph.cmp[n+i]) return false;
        REP(i, n) ans[i] = graph.cmp[i] > graph.cmp[n+i];
        return true;
    }
};
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

