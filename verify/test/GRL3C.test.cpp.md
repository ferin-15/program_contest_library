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


# :heavy_check_mark: test/GRL3C.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/GRL3C.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_C">https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_C</a>


## Depends on

* :heavy_check_mark: <a href="../../library/graph/SCC.cpp.html">graph/SCC.cpp</a>
* :heavy_check_mark: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_C"
#include "../memo/macro.hpp"
#include "../graph/SCC.cpp"

signed main(void) {
    ll n, m;
    cin >> n >> m;
    SCC scc(n);
    REP(i, m) {
        ll u, v;
        cin >> u >> v;
        scc.add_edge(u, v);
    }
    scc.scc();
    ll q;
    cin >> q;
    REP(i, q) {
        ll u, v;
        cin >> u >> v;
        if(scc.cmp[u] == scc.cmp[v]) cout << 1 << endl;
        else cout << 0 << endl;
    }

    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/GRL3C.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_C"
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
#line 1 "test/../graph/SCC.cpp"
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
#line 4 "test/GRL3C.test.cpp"

signed main(void) {
    ll n, m;
    cin >> n >> m;
    SCC scc(n);
    REP(i, m) {
        ll u, v;
        cin >> u >> v;
        scc.add_edge(u, v);
    }
    scc.scc();
    ll q;
    cin >> q;
    REP(i, q) {
        ll u, v;
        cin >> u >> v;
        if(scc.cmp[u] == scc.cmp[v]) cout << 1 << endl;
        else cout << 0 << endl;
    }

    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

