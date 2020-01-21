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


# :heavy_check_mark: graph/HLDecomposition.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/HLDecomposition.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 05:17:03+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/GRL5C_0.test.cpp.html">test/GRL5C_0.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/GRL5D.test.cpp.html">test/GRL5D.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/GRL5E.test.cpp.html">test/GRL5E.test.cpp</a>
* :x: <a href="../../verify/test/aoj2667.test.cpp.html">test/aoj2667.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
class HLDecomposition {
    void dfs1(ll v, ll p) {
        if(g[v].size() && g[v][0]==p) swap(g[v][0], g[v].back());
        for(auto &to: g[v]) {
            if(to == p) continue;
            dfs1(to, v);
            sz[v] += sz[to];
            if(sz[to] > sz[g[v][0]]) swap(to, g[v][0]);
        }
    }
    void dfs2(ll v, ll p, ll &k) {
        par[v] = p; vid[v] = k++;
        for(auto to: g[v]) {
            if(to == p) continue;
            head[to] = (to == g[v][0] ? head[v] : to);
            dfs2(to, v, k);
        }
    }

public:
    int n;
    vector<vector<ll>> g;
    vector<ll> vid, head, sz, par;

    HLDecomposition(){}
    HLDecomposition(ll sz): n(sz), g(n), vid(n,-1), head(n), sz(n,1), par(n) {}

    void add_edge(ll u, ll v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void build(vector<ll> rs=vector<ll>(1,0)) {
        ll k = 0;
        for(ll r: rs) {
            dfs1(r, -1);
            head[r] = r;
            dfs2(r, -1, k);
        }
    }

    // パスu-vの頂点属性クエリ
    void for_each(ll u, ll v, const function<void(ll,ll)>& f) {
        while(1){
            if(vid[u]>vid[v]) swap(u,v);
            f(max(vid[head[v]], vid[u]), vid[v]); // 開区間!!!
            if(head[u]!=head[v]) v = par[head[v]];
            else break;
        }
    }
    // パスu-vの辺属性クエリ
    void for_each_edge(ll u, ll v, const function<void(ll,ll)>& f) {
        while(1) {
            if(vid[u]>vid[v]) swap(u,v);
            if(head[u]!=head[v]) {
                f(vid[head[v]], vid[v]); // 開区間!!!
                v = par[head[v]];
            } else {
                if(u!=v) f(vid[u]+1, vid[v]); // 開区間!!!
                break;
            }
        }
    }
    ll lca(ll u, ll v) {
        while(1) {
            if(vid[u]>vid[v]) swap(u,v);
            if(head[u]==head[v]) return u;
            v = par[head[v]];
        }
    }
};
// 部分木 頂点クエリ → 区間[hld.vid[u]+1, hld.vid[u] + hld.sub[u])
// 部分木 辺クエリ → 区間[hld.vid[u]+1, hld.vid[u] + hld.sub[u])
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/HLDecomposition.cpp"
class HLDecomposition {
    void dfs1(ll v, ll p) {
        if(g[v].size() && g[v][0]==p) swap(g[v][0], g[v].back());
        for(auto &to: g[v]) {
            if(to == p) continue;
            dfs1(to, v);
            sz[v] += sz[to];
            if(sz[to] > sz[g[v][0]]) swap(to, g[v][0]);
        }
    }
    void dfs2(ll v, ll p, ll &k) {
        par[v] = p; vid[v] = k++;
        for(auto to: g[v]) {
            if(to == p) continue;
            head[to] = (to == g[v][0] ? head[v] : to);
            dfs2(to, v, k);
        }
    }

public:
    int n;
    vector<vector<ll>> g;
    vector<ll> vid, head, sz, par;

    HLDecomposition(){}
    HLDecomposition(ll sz): n(sz), g(n), vid(n,-1), head(n), sz(n,1), par(n) {}

    void add_edge(ll u, ll v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void build(vector<ll> rs=vector<ll>(1,0)) {
        ll k = 0;
        for(ll r: rs) {
            dfs1(r, -1);
            head[r] = r;
            dfs2(r, -1, k);
        }
    }

    // パスu-vの頂点属性クエリ
    void for_each(ll u, ll v, const function<void(ll,ll)>& f) {
        while(1){
            if(vid[u]>vid[v]) swap(u,v);
            f(max(vid[head[v]], vid[u]), vid[v]); // 開区間!!!
            if(head[u]!=head[v]) v = par[head[v]];
            else break;
        }
    }
    // パスu-vの辺属性クエリ
    void for_each_edge(ll u, ll v, const function<void(ll,ll)>& f) {
        while(1) {
            if(vid[u]>vid[v]) swap(u,v);
            if(head[u]!=head[v]) {
                f(vid[head[v]], vid[v]); // 開区間!!!
                v = par[head[v]];
            } else {
                if(u!=v) f(vid[u]+1, vid[v]); // 開区間!!!
                break;
            }
        }
    }
    ll lca(ll u, ll v) {
        while(1) {
            if(vid[u]>vid[v]) swap(u,v);
            if(head[u]==head[v]) return u;
            v = par[head[v]];
        }
    }
};
// 部分木 頂点クエリ → 区間[hld.vid[u]+1, hld.vid[u] + hld.sub[u])
// 部分木 辺クエリ → 区間[hld.vid[u]+1, hld.vid[u] + hld.sub[u])
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

