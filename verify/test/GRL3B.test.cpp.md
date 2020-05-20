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


# :heavy_check_mark: test/GRL3B.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/GRL3B.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_B">https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_B</a>


## Depends on

* :heavy_check_mark: <a href="../../library/graph/BCC.cpp.html">graph/BCC.cpp</a>
* :heavy_check_mark: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_B"
#include "../memo/macro.hpp"
#include "../graph/BCC.cpp"

signed main(void) {
    ll n, m;
    cin >> n >> m;
    twoEdgeComponent graph(n);
    REP(i, m) {
        ll a, b;
        cin >> a >> b;
        graph.add_edge(a, b);
    }
    graph.build();

    for(auto &e: graph.bridge) if(e.first > e.second) swap(e.first, e.second);
    sort(ALL(graph.bridge));
    for(auto e: graph.bridge) cout << e.first << " " << e.second << endl;

    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/GRL3B.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_B"
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
#line 4 "test/GRL3B.test.cpp"

signed main(void) {
    ll n, m;
    cin >> n >> m;
    twoEdgeComponent graph(n);
    REP(i, m) {
        ll a, b;
        cin >> a >> b;
        graph.add_edge(a, b);
    }
    graph.build();

    for(auto &e: graph.bridge) if(e.first > e.second) swap(e.first, e.second);
    sort(ALL(graph.bridge));
    for(auto e: graph.bridge) cout << e.first << " " << e.second << endl;

    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

