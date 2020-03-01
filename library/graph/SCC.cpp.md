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


# :heavy_check_mark: graph/SCC.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/SCC.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00




## Required by

* :warning: <a href="../test/aoj2991.memo.cpp.html">test/aoj2991.memo.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/GRL3C.test.cpp.html">test/GRL3C.test.cpp</a>
* :x: <a href="../../verify/test/yosupo-2SAT.test.cpp.html">test/yosupo-2SAT.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
struct SCC {
    int V, K;
    vector<vector<int>> G;
    vector<vector<int>> rG;
    vector<int> vs;
    vector<int> used;
    vector<int> cmp;

    void dfs(int v) {
        used[v]=true;
        for(int nx: G[v]) if(!used[nx]) dfs(nx);
        vs.push_back(v);
    }
    void rdfs(int v,int k) {
        used[v]=true; cmp[v]=k;
        for(int nx: rG[v]) if(!used[nx]) rdfs(nx,k);
    }

    SCC() { V=K=-1; }
    SCC(int V_): V(V_), G(V_), rG(V_), used(V_), cmp(V_) {}

    void add_edge(int from,int to) {
        G[from].push_back(to);
        rG[to].push_back(from);
    }
    int scc() {
        used.assign(V,0); vs.clear();
        for(int v=0;v<V;v++) if(!used[v]) dfs(v);
        used.assign(V,0);
        int k=0;
        for(int i=(int)vs.size()-1;i>=0;i--) if(!used[vs[i]]) {
            rdfs(vs[i],k++);
        }
        return K=k;
    }
    // O(ElogE)
    // SCCしたあとのグラフはトポロジカル順になってる
    vector<vector<int>> getDAG() {
        vector<vector<int>> res(K);
        for(int from=0;from<V;from++) {
            for(int to:G[from]) if(cmp[from]!=cmp[to]) {
                res[cmp[from]].push_back(cmp[to]);
            }
        }
        for(int i=0;i<K;i++){
            sort(ALL(res[i]));
            res[i].erase(unique(ALL(res[i])),res[i].end());
        }
        return res;
    }
};
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/SCC.cpp"
// BEGIN CUT
struct SCC {
    int V, K;
    vector<vector<int>> G;
    vector<vector<int>> rG;
    vector<int> vs;
    vector<int> used;
    vector<int> cmp;

    void dfs(int v) {
        used[v]=true;
        for(int nx: G[v]) if(!used[nx]) dfs(nx);
        vs.push_back(v);
    }
    void rdfs(int v,int k) {
        used[v]=true; cmp[v]=k;
        for(int nx: rG[v]) if(!used[nx]) rdfs(nx,k);
    }

    SCC() { V=K=-1; }
    SCC(int V_): V(V_), G(V_), rG(V_), used(V_), cmp(V_) {}

    void add_edge(int from,int to) {
        G[from].push_back(to);
        rG[to].push_back(from);
    }
    int scc() {
        used.assign(V,0); vs.clear();
        for(int v=0;v<V;v++) if(!used[v]) dfs(v);
        used.assign(V,0);
        int k=0;
        for(int i=(int)vs.size()-1;i>=0;i--) if(!used[vs[i]]) {
            rdfs(vs[i],k++);
        }
        return K=k;
    }
    // O(ElogE)
    // SCCしたあとのグラフはトポロジカル順になってる
    vector<vector<int>> getDAG() {
        vector<vector<int>> res(K);
        for(int from=0;from<V;from++) {
            for(int to:G[from]) if(cmp[from]!=cmp[to]) {
                res[cmp[from]].push_back(cmp[to]);
            }
        }
        for(int i=0;i<K;i++){
            sort(ALL(res[i]));
            res[i].erase(unique(ALL(res[i])),res[i].end());
        }
        return res;
    }
};
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

