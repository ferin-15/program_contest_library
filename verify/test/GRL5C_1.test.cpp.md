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


# :heavy_check_mark: test/GRL5C_1.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/GRL5C_1.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-22 00:44:24+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C">https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C</a>


## Depends on

* :heavy_check_mark: <a href="../../library/graph/LCA_doubling.cpp.html">graph/LCA_doubling.cpp</a>
* :heavy_check_mark: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C"
#include "../memo/macro.hpp"
#include "../graph/LCA_doubling.cpp"

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
#line 1 "test/GRL5C_1.test.cpp"
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
#line 1 "test/../graph/LCA_doubling.cpp"
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
#line 4 "test/GRL5C_1.test.cpp"

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

