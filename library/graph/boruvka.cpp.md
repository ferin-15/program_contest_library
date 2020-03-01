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


# :heavy_check_mark: graph/boruvka.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/boruvka.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 05:59:59+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/GRL2A.test.cpp.html">test/GRL2A.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template< typename T, typename F >
T boruvka(ll n, F f) {
    vector<ll> rev(n), belong(n);
    UnionFind uf(n);
    T ret = T();
    while(uf.size(0) != n) {
        ll ptr = 0;
        REP(i, n) if(uf.find(i) == i) belong[i] = ptr++, rev[belong[i]] = i;
        REP(i, n) belong[i] = belong[uf.find(i)];
        vector<PII> v = f(ptr, belong);
        bool update = false;
        REP(i, ptr) {
            if(~v[i].second && !uf.same(rev[i], rev[v[i].second])) {
                uf.unite(rev[i], rev[v[i].second]);
                ret += v[i].first;
                update = true;
            }
        }
        if(!update) return -1; // notice!!
    }
    return ret;
}

/*
// O(fの計算量 * logV)
// 各頂点から最小のコストの辺を求める
// sz=連結成分数 belong[i]=i番目の頂点が属する連結成分
function<vector<PII>(ll,vector<ll>)> f = [&](ll sz, vector<ll> belong) {
    // ret[i] = (連結成分iからコスト最小の辺の(コスト, i以外の端点の連結成分))
    // iがufの親以外ならsecondは-1として連結成分ごとに管理
    vector<PII> ret(sz, PII(LLINF, -1));
    REP(i, n) for(auto to: g[i]) {
        if(belong[i] == belong[to.first]) continue;
        chmin(ret[belong[i]], PII(to.second, belong[to.first]));
    }
    return ret;
};
cout << boruvka<ll, decltype(f)>(n, f) << endl;
*/
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/boruvka.cpp"
template< typename T, typename F >
T boruvka(ll n, F f) {
    vector<ll> rev(n), belong(n);
    UnionFind uf(n);
    T ret = T();
    while(uf.size(0) != n) {
        ll ptr = 0;
        REP(i, n) if(uf.find(i) == i) belong[i] = ptr++, rev[belong[i]] = i;
        REP(i, n) belong[i] = belong[uf.find(i)];
        vector<PII> v = f(ptr, belong);
        bool update = false;
        REP(i, ptr) {
            if(~v[i].second && !uf.same(rev[i], rev[v[i].second])) {
                uf.unite(rev[i], rev[v[i].second]);
                ret += v[i].first;
                update = true;
            }
        }
        if(!update) return -1; // notice!!
    }
    return ret;
}

/*
// O(fの計算量 * logV)
// 各頂点から最小のコストの辺を求める
// sz=連結成分数 belong[i]=i番目の頂点が属する連結成分
function<vector<PII>(ll,vector<ll>)> f = [&](ll sz, vector<ll> belong) {
    // ret[i] = (連結成分iからコスト最小の辺の(コスト, i以外の端点の連結成分))
    // iがufの親以外ならsecondは-1として連結成分ごとに管理
    vector<PII> ret(sz, PII(LLINF, -1));
    REP(i, n) for(auto to: g[i]) {
        if(belong[i] == belong[to.first]) continue;
        chmin(ret[belong[i]], PII(to.second, belong[to.first]));
    }
    return ret;
};
cout << boruvka<ll, decltype(f)>(n, f) << endl;
*/

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

