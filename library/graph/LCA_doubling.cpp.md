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


# :heavy_check_mark: graph/LCA_doubling.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/LCA_doubling.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 05:17:03+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/GRL5C_1.test.cpp.html">test/GRL5C_1.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct LCA {
    const int n = 0;
    const int log2_n = 0;
    vector<vector<int>> g;
    vector<vector<int>> par;  // par[2^i上][頂点v]
    vector<int> dep;

    void dfs(int v, int p, int d) {
        par[0][v] = p;
        dep[v] = d;
        for(auto to: g[v]) {
            if(to == p) continue;
            dfs(to, v, d+1);
        }
    }

    LCA() {}
    LCA(int n) : n(n), log2_n(log2(n)+1), g(n),
        par(log2_n, vector<int>(n)), dep(n) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void build(ll root=0) {
        dfs(root, -1, 0);
        for(int i=0; i+1 < log2_n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(par[i][j] < 0) par[i+1][j] = -1;
                else par[i+1][j] = par[i][par[i][j]];
            }
        }
    }

    int get(int u, int v) {
        if(dep[u] > dep[v]) swap(u, v);
        REP(i, log2_n) {
            if((dep[v] - dep[u]) >> i & 1) {
                v = par[i][v];
            }
        }
        if(u == v) return u;
        for(int i=log2_n-1; i>=0; --i) {
            if(par[i][u] != par[i][v]) {
                u = par[i][u];
                v = par[i][v];
            }
        }
        return par[0][u];
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/LCA_doubling.cpp"
struct LCA {
    const int n = 0;
    const int log2_n = 0;
    vector<vector<int>> g;
    vector<vector<int>> par;  // par[2^i上][頂点v]
    vector<int> dep;

    void dfs(int v, int p, int d) {
        par[0][v] = p;
        dep[v] = d;
        for(auto to: g[v]) {
            if(to == p) continue;
            dfs(to, v, d+1);
        }
    }

    LCA() {}
    LCA(int n) : n(n), log2_n(log2(n)+1), g(n),
        par(log2_n, vector<int>(n)), dep(n) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void build(ll root=0) {
        dfs(root, -1, 0);
        for(int i=0; i+1 < log2_n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(par[i][j] < 0) par[i+1][j] = -1;
                else par[i+1][j] = par[i][par[i][j]];
            }
        }
    }

    int get(int u, int v) {
        if(dep[u] > dep[v]) swap(u, v);
        REP(i, log2_n) {
            if((dep[v] - dep[u]) >> i & 1) {
                v = par[i][v];
            }
        }
        if(u == v) return u;
        for(int i=log2_n-1; i>=0; --i) {
            if(par[i][u] != par[i][v]) {
                u = par[i][u];
                v = par[i][v];
            }
        }
        return par[0][u];
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

