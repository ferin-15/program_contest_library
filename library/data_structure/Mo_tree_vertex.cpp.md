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


# :heavy_check_mark: data_structure/Mo_tree_vertex.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/Mo_tree_vertex.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-08 17:56:23+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj2270.test.cpp.html">test/aoj2270.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
// 頂点クエリのMo
// HL分解で頂点クエリするときに下の辺に下ろすみたいなのをする
// add_edgeとinsertをした後buildをしてprocessを進めていく
struct Mo_Tree_Vertex {
    vector<vector<int>> g, parent;
    vector<int> vs, in;

    vector<int> left, right, order, lca, dep;
    vector<bool> v;
    int width;
    int nl, nr, ptr;

    using F = function<void(int)>;
    F add, del;

    void dfs(int idx, int depth, int par) {
        in[idx] = (int) vs.size();
        dep[idx] = depth;
        parent[0][idx] = par;
        vs.push_back(idx);
        for(auto &to : g[idx]) {
            if(to == par) continue;
            dfs(to, depth + 1, idx);
            vs.push_back(to);
        }
    }

    int getlca(int u, int v) {
        if(dep[u] > dep[v]) swap(u, v);
        for(int k = 0; k < (int)parent.size(); k++) {
            if(((dep[v] - dep[u]) >> k) & 1) {
                v = parent[k][v];
            }
        }
        if(u == v) return (u);
        for(int k = (int)parent.size()-1; k >= 0; k--) {
            if(parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return (parent[0][u]);
    }

    inline void distribute(int vertex) {
        v[vertex].flip();
        if(v[vertex]) add(vertex);
        else del(vertex);
    }

    Mo_Tree_Vertex(int n, F a, F d) : g(n), in(n), dep(n), v(n), width((int)sqrt(2*n-1)), nl(0), nr(0), ptr(0), add(a), del(d) {
        const auto lg = (int) (log2(n) + 1);
        parent.resize(lg, vector<int>(n));
        vs.reserve(2*n-1);
    }

    void add_edge(int x, int y) {
        g[x].push_back(y);
        g[y].push_back(x);
    }
    void prepare() {
        dfs(0, 0, -1);
        for(int k = 0; k+1 < (int)parent.size(); k++) {
            for(int i = 0; i < (int)parent[k].size(); i++) {
                if(parent[k][i] == -1) parent[k + 1][i] = -1;
                else parent[k + 1][i] = parent[k][parent[k][i]];
            }
        }
    }
    // パスx,yのクエリ
    void insert(int x, int y) {
        if(in[x] > in[y]) swap(x, y);
        left.push_back(in[x] + 1);
        right.push_back(in[y] + 1);
        lca.push_back(getlca(x, y));
    }
    void build() {
        order.resize(left.size());
        iota(begin(order), end(order), 0);
        sort(begin(order), end(order), [&](int a, int b) {
            if(left[a] / width != left[b] / width) return left[a] < left[b];
            return bool((right[a] < right[b]) ^ (left[a] / width % 2));
        });
    }

    int process() {
        if(ptr == (int)order.size()) return (-1);
        if(ptr > 0) distribute(lca[order[ptr - 1]]); // 前のクエリで追加したLCAを削除
        const auto id = order[ptr];
        while(nl > left[id]) distribute(vs[--nl]);
        while(nr < right[id]) distribute(vs[nr++]);
        while(nl < left[id]) distribute(vs[nl++]);
        while(nr > right[id]) distribute(vs[--nr]);
        distribute(lca[id]); // LCA の頂点を例外として追加する
        return (order[ptr++]);
    }
};
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/Mo_tree_vertex.cpp"
// BEGIN CUT
// 頂点クエリのMo
// HL分解で頂点クエリするときに下の辺に下ろすみたいなのをする
// add_edgeとinsertをした後buildをしてprocessを進めていく
struct Mo_Tree_Vertex {
    vector<vector<int>> g, parent;
    vector<int> vs, in;

    vector<int> left, right, order, lca, dep;
    vector<bool> v;
    int width;
    int nl, nr, ptr;

    using F = function<void(int)>;
    F add, del;

    void dfs(int idx, int depth, int par) {
        in[idx] = (int) vs.size();
        dep[idx] = depth;
        parent[0][idx] = par;
        vs.push_back(idx);
        for(auto &to : g[idx]) {
            if(to == par) continue;
            dfs(to, depth + 1, idx);
            vs.push_back(to);
        }
    }

    int getlca(int u, int v) {
        if(dep[u] > dep[v]) swap(u, v);
        for(int k = 0; k < (int)parent.size(); k++) {
            if(((dep[v] - dep[u]) >> k) & 1) {
                v = parent[k][v];
            }
        }
        if(u == v) return (u);
        for(int k = (int)parent.size()-1; k >= 0; k--) {
            if(parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return (parent[0][u]);
    }

    inline void distribute(int vertex) {
        v[vertex].flip();
        if(v[vertex]) add(vertex);
        else del(vertex);
    }

    Mo_Tree_Vertex(int n, F a, F d) : g(n), in(n), dep(n), v(n), width((int)sqrt(2*n-1)), nl(0), nr(0), ptr(0), add(a), del(d) {
        const auto lg = (int) (log2(n) + 1);
        parent.resize(lg, vector<int>(n));
        vs.reserve(2*n-1);
    }

    void add_edge(int x, int y) {
        g[x].push_back(y);
        g[y].push_back(x);
    }
    void prepare() {
        dfs(0, 0, -1);
        for(int k = 0; k+1 < (int)parent.size(); k++) {
            for(int i = 0; i < (int)parent[k].size(); i++) {
                if(parent[k][i] == -1) parent[k + 1][i] = -1;
                else parent[k + 1][i] = parent[k][parent[k][i]];
            }
        }
    }
    // パスx,yのクエリ
    void insert(int x, int y) {
        if(in[x] > in[y]) swap(x, y);
        left.push_back(in[x] + 1);
        right.push_back(in[y] + 1);
        lca.push_back(getlca(x, y));
    }
    void build() {
        order.resize(left.size());
        iota(begin(order), end(order), 0);
        sort(begin(order), end(order), [&](int a, int b) {
            if(left[a] / width != left[b] / width) return left[a] < left[b];
            return bool((right[a] < right[b]) ^ (left[a] / width % 2));
        });
    }

    int process() {
        if(ptr == (int)order.size()) return (-1);
        if(ptr > 0) distribute(lca[order[ptr - 1]]); // 前のクエリで追加したLCAを削除
        const auto id = order[ptr];
        while(nl > left[id]) distribute(vs[--nl]);
        while(nr < right[id]) distribute(vs[nr++]);
        while(nl < left[id]) distribute(vs[nl++]);
        while(nr > right[id]) distribute(vs[--nr]);
        distribute(lca[id]); // LCA の頂点を例外として追加する
        return (order[ptr++]);
    }
};
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

