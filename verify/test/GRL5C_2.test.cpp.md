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


# :heavy_check_mark: test/GRL5C_2.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/GRL5C_2.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-22 00:44:24+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C">https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/sparse_table.cpp.html">data_structure/sparse_table.cpp</a>
* :heavy_check_mark: <a href="../../library/graph/LCA_sparsetable.cpp.html">graph/LCA_sparsetable.cpp</a>
* :heavy_check_mark: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C"
#include "../memo/macro.hpp"
#include "../data_structure/sparse_table.cpp"
#include "../graph/LCA_sparsetable.cpp"

signed main(void) {
    ll n;
    cin >> n;
    LCA graph(n);
    REP(i, n) {
        ll k;
        cin >> k;
        REP(j, k) {
            ll c;
            cin >> c;
            graph.add_edge(i, c);
        }
    }
    graph.build();

    ll q;
    cin >> q;
    while(q--) {
        ll u, v;
        cin >> u >> v;
        cout << graph.get(u, v) << endl;
    }

    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/GRL5C_2.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C"
#line 1 "test/../memo/macro.hpp"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PII = pair<ll, ll>;
#define FOR(i, a, n) for (ll i = (ll)a; i < (ll)n; ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(x) x.begin(), x.end()
template<typename T> void chmin(T &a, const T &b) { a = min(a, b); }
template<typename T> void chmax(T &a, const T &b) { a = max(a, b); }
struct FastIO {FastIO() { cin.tie(0); ios::sync_with_stdio(0); }}fastiofastio;
const ll INF = 1LL<<60;
#line 1 "test/../data_structure/sparse_table.cpp"
template <typename S>
struct sparseTable {
    using T = typename S::T;
    int n;
    vector<int> log2;
    vector<vector<T>> t;

    sparseTable() {}
    sparseTable(int nn) { construct(nn); }
    void construct(int nn) {
        n = nn;
        log2.assign(n+1, 0);
        for(int i=2; i<=n; ++i) log2[i] = log2[i >> 1] + 1;
        t = vector<vector<T>>(log2[n]+1, vector<T>(n));
    }
    void init(vector<T> v) {
        for(int i=0; i<n; ++i) t[0][i] = v[i];
        for(int j=1; j<=log2[n]; ++j) {
            int w = 1LL<<(j-1);
            for (int i = 0; i+(w<<1) <= n; ++i) {
                t[j][i] = S::op(t[j-1][i], t[j-1][i+w]);
            }
        }
    }
    // [l, r]
    T query(int l, int r) {
        int j = log2[r - l];
        return S::op(t[j][l], t[j][r-(1 << j)+1]);
    }
};

// 集合T、結合則・可換・冪等律が成り立つ二項演算op
struct minnimum {
    using T = ll;
    static T op(const T& a, const T& b) { return min(a, b); }
};
struct maximum {
    using T = ll;
    static T op(const T& a, const T& b) { return max(a, b); }
};
struct gcd_op {
    using T = ll;
    static T op(const T& a, const T& b) { return __gcd(a, b); }
};
#line 1 "test/../graph/LCA_sparsetable.cpp"
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
#line 5 "test/GRL5C_2.test.cpp"

signed main(void) {
    ll n;
    cin >> n;
    LCA graph(n);
    REP(i, n) {
        ll k;
        cin >> k;
        REP(j, k) {
            ll c;
            cin >> c;
            graph.add_edge(i, c);
        }
    }
    graph.build();

    ll q;
    cin >> q;
    while(q--) {
        ll u, v;
        cin >> u >> v;
        cout << graph.get(u, v) << endl;
    }

    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

