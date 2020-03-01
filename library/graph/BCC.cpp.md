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


# :heavy_check_mark: graph/BCC.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/BCC.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/GRL3B.test.cpp.html">test/GRL3B.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
class twoEdgeComponent {
private:
    void dfs(ll v, ll p, ll &k) {
        ord[v] = k++;
        low[v] = ord[v];
        for(auto to: g[v]) {
            if(ord[to]==-1) {
                dfs(to, v, k);
                chmin(low[v], low[to]);
                if(ord[v] < low[to]) bridge.emplace_back(v, to);
            } else if(to != p) {
                chmin(low[v], ord[to]);
            }
        }
    }
    void dfs2(ll v, ll p, ll &k) {
        if(~p && ord[p] >= low[v]) cmp[v] = cmp[p];
        else cmp[v] = k++;
        for(auto to: g[v]) if(cmp[to] == -1) dfs2(to, v, k);
    }
public:
    vector<vector<ll>> g;
    vector<ll> ord, low, cmp;
    vector<PII> bridge;

    twoEdgeComponent() {}
    twoEdgeComponent(ll n) : g(n), ord(n, -1), low(n), cmp(n, -1) {}

    void add_edge(ll u, ll v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<vector<ll>> build() {
        ll k = 0;
        REP(i, g.size()) if(ord[i]==-1) dfs(i, -1, k);
        k = 0;
        REP(i, g.size()) if(cmp[i]==-1) dfs2(i, -1, k);
        vector<vector<ll>> ret(k);
        for(auto e: bridge) {
            ll x = cmp[e.first], y = cmp[e.second];
            ret[x].push_back(y);
            ret[y].push_back(x);
        }
        return ret;
    }
};
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/BCC.cpp"
// BEGIN CUT
class twoEdgeComponent {
private:
    void dfs(ll v, ll p, ll &k) {
        ord[v] = k++;
        low[v] = ord[v];
        for(auto to: g[v]) {
            if(ord[to]==-1) {
                dfs(to, v, k);
                chmin(low[v], low[to]);
                if(ord[v] < low[to]) bridge.emplace_back(v, to);
            } else if(to != p) {
                chmin(low[v], ord[to]);
            }
        }
    }
    void dfs2(ll v, ll p, ll &k) {
        if(~p && ord[p] >= low[v]) cmp[v] = cmp[p];
        else cmp[v] = k++;
        for(auto to: g[v]) if(cmp[to] == -1) dfs2(to, v, k);
    }
public:
    vector<vector<ll>> g;
    vector<ll> ord, low, cmp;
    vector<PII> bridge;

    twoEdgeComponent() {}
    twoEdgeComponent(ll n) : g(n), ord(n, -1), low(n), cmp(n, -1) {}

    void add_edge(ll u, ll v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<vector<ll>> build() {
        ll k = 0;
        REP(i, g.size()) if(ord[i]==-1) dfs(i, -1, k);
        k = 0;
        REP(i, g.size()) if(cmp[i]==-1) dfs2(i, -1, k);
        vector<vector<ll>> ret(k);
        for(auto e: bridge) {
            ll x = cmp[e.first], y = cmp[e.second];
            ret[x].push_back(y);
            ret[y].push_back(x);
        }
        return ret;
    }
};
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

