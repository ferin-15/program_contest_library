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


# :heavy_check_mark: test/GRL5C_3.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/GRL5C_3.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C">https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C</a>


## Depends on

* :heavy_check_mark: <a href="../../library/graph/LCA_tarjan_offline.cpp.html">graph/LCA_tarjan_offline.cpp</a>
* :question: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C"
#include "../memo/macro.hpp"
#include "../graph/LCA_tarjan_offline.cpp"

signed main(void) {
    ll n;
    cin >> n;
    vector<PII> edges;
    REP(i, n) {
        ll k;
        cin >> k;
        REP(j, k) {
            ll c;
            cin >> c;
            edges.emplace_back(i, c);
        }
    }
    ll q;
    cin >> q;

    tarjan_offline_lca graph(n, q);
    for(auto e: edges) graph.add_edge(e.first, e.second);
    REP(i, q) {
        ll u, v;
        cin >> u >> v;
        graph.add_query(u, v, i);
    }
    auto ret = graph.build();
    for(auto i: ret) cout << i << endl;

    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/GRL5C_3.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C"
#line 1 "memo/macro.hpp"
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
#line 1 "graph/LCA_tarjan_offline.cpp"
// BEGIN CUT
struct UnionFind {
    vector<int> par, s;
    UnionFind(int n=2e5) { init(n); }
    void init(int n) {
        s.assign(n, 1); par.resize(n);
        iota(par.begin(), par.end(), 0);
    }
    int find(int x) {
        if(par[x] == x) return x;
        return par[x] = find(par[x]);
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y) return;
        if(s[x] < s[y]) par[x] = y, s[y] = s[x] + s[y];
        else par[y] = x, s[x] = s[x] + s[y];
    }
    bool same(int x, int y) { return find(x) == find(y); }
    int size(int x) { return s[find(x)]; }
};

class tarjan_offline_lca {
private:
    ll n;
    UnionFind uf;
    vector<ll> anc, lca, visit, used;
    vector<vector<ll>> g;
    vector<vector<PII>> query;
    void dfs(ll v=0, ll p=-1) {
        anc[v] = v;
        for(auto to: g[v]) if(to != p) {
            dfs(to, v);
            uf.unite(to, v);
            anc[uf.find(v)] = v;
        }
        visit[v] = 1;
        for(auto i: query[v]) {
            if(visit[i.first] == 1 && used[i.second]++ == 0) {
                lca[i.second] = anc[uf.find(i.first)];
            }
        }
    }
public:
    tarjan_offline_lca() {}
    tarjan_offline_lca(ll n, ll q) : n(n), uf(n), anc(n), lca(q), visit(n), used(q), g(n), query(n) {}
    // 辺とクエリの追加
    void add_edge(ll a, ll b) {
        g[a].push_back(b);
        g[b].push_back(a);
    }
    // i番目のクエリは頂点aと頂点bのLCA
    void add_query(ll a, ll b, ll i) {
        query[a].push_back({b, i});
        query[b].push_back({a, i});
    }
    // lcaを求める
    vector<ll> build() { dfs(); return lca; }
};
// END CUT
#line 4 "test/GRL5C_3.test.cpp"

signed main(void) {
    ll n;
    cin >> n;
    vector<PII> edges;
    REP(i, n) {
        ll k;
        cin >> k;
        REP(j, k) {
            ll c;
            cin >> c;
            edges.emplace_back(i, c);
        }
    }
    ll q;
    cin >> q;

    tarjan_offline_lca graph(n, q);
    for(auto e: edges) graph.add_edge(e.first, e.second);
    REP(i, q) {
        ll u, v;
        cin >> u >> v;
        graph.add_query(u, v, i);
    }
    auto ret = graph.build();
    for(auto i: ret) cout << i << endl;

    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

