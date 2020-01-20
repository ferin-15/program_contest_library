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


# :heavy_check_mark: graph/LCA_sparsetable.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/LCA_sparsetable.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 07:11:31+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/GRL5C_2.test.cpp.html">test/GRL5C_2.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
class LCA {
private:
    const int n = 0;
    const int log2_n = 0;
    vector<vector<int>> par;
    vector<vector<int>> g;
    vector<int> depth;     // 頂点iの深さ
    vector<int> vs;        // 頂点を訪問順に並べたもの
    vector<int> depth_seq; // depth_seq[i] = (頂点vs[i]の深さ)
    vector<int> id;        // 頂点が初めてvsに登場するインデックス
    struct minimum_st {
        using T = PII;
        static T op(const T& a, const T& b) { return min(a, b); }
    }; 
    sparseTable<minimum_st> st;
    void dfs(int v, int p, int d, int &k) {
        id[v] = k; vs[k] = v; depth_seq[k++] = d; depth[v] = d;
        for(auto to: g[v]) if(to != p) {
            dfs(to, v, d+1, k);
            vs[k] = v; depth_seq[k++] = d;
        }
    }
public:
    LCA(int n_=1e5) : n(n_), g(n), depth(n), vs(2*n-1), depth_seq(2*n-1), id(n) {}
    // u-vに辺を張る
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    // rootを根として初期化
    void build(int root = 0) {
        int k = 0;
        dfs(root, -1, 0, k);
        vector<PII> v(2*n-1);
        REP(i, 2*n-1) v[i] = {depth_seq[i], i};
        st.construct(2*n-1);
        st.init(v);
    }
    // uとvのlcaを返す O(1)
    int get(int u, int v) {
        if(id[u] > id[v]) swap(u, v);
        return vs[st.query(id[u], id[v]).second];
    }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/LCA_sparsetable.cpp"
class LCA {
private:
    const int n = 0;
    const int log2_n = 0;
    vector<vector<int>> par;
    vector<vector<int>> g;
    vector<int> depth;     // 頂点iの深さ
    vector<int> vs;        // 頂点を訪問順に並べたもの
    vector<int> depth_seq; // depth_seq[i] = (頂点vs[i]の深さ)
    vector<int> id;        // 頂点が初めてvsに登場するインデックス
    struct minimum_st {
        using T = PII;
        static T op(const T& a, const T& b) { return min(a, b); }
    }; 
    sparseTable<minimum_st> st;
    void dfs(int v, int p, int d, int &k) {
        id[v] = k; vs[k] = v; depth_seq[k++] = d; depth[v] = d;
        for(auto to: g[v]) if(to != p) {
            dfs(to, v, d+1, k);
            vs[k] = v; depth_seq[k++] = d;
        }
    }
public:
    LCA(int n_=1e5) : n(n_), g(n), depth(n), vs(2*n-1), depth_seq(2*n-1), id(n) {}
    // u-vに辺を張る
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    // rootを根として初期化
    void build(int root = 0) {
        int k = 0;
        dfs(root, -1, 0, k);
        vector<PII> v(2*n-1);
        REP(i, 2*n-1) v[i] = {depth_seq[i], i};
        st.construct(2*n-1);
        st.init(v);
    }
    // uとvのlcaを返す O(1)
    int get(int u, int v) {
        if(id[u] > id[v]) swap(u, v);
        return vs[st.query(id[u], id[v]).second];
    }
};
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

