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


# :heavy_check_mark: test/GRL3A.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/GRL3A.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-22 00:44:24+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A&lang=jp">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A&lang=jp</a>


## Depends on

* :heavy_check_mark: <a href="../../library/graph/articulation.cpp.html">graph/articulation.cpp</a>
* :heavy_check_mark: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A&lang=jp"
#include "../memo/macro.hpp"
#include "../graph/articulation.cpp"

int main() {
    ll n, m;
    cin >> n >> m;
    articulation graph(n);
    REP(i, m) {
        ll s, t;
        cin >> s >> t;
        graph.add_edge(s, t);
    }
    auto ret = graph.build();
    sort(ALL(ret));
    for(auto i: ret) cout << i << "\n";
    cout << flush;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/GRL3A.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A&lang=jp"
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
#line 1 "test/../graph/articulation.cpp"
class articulation {
private:
    void dfs(ll v, ll p, ll &k, vector<ll> &ret) {
        ord[v] = k++;
        low[v] = ord[v];
        ll cnt = 0;
        bool is_articulation = false;
        for(auto to: g[v]) {
            if(ord[to]==-1) {
                dfs(to, v, k, ret);
                chmin(low[v], low[to]);
                ++cnt;
                is_articulation |= p!=-1 && low[to] >= ord[v]; 
            } else if(to != p) {
                chmin(low[v], ord[to]);
            }
        }
        is_articulation |= p==-1 && cnt>1;
        if(is_articulation) ret.push_back(v);
    }
public:
    vector<vector<ll>> g;
    vector<ll> ord, low, cmp;

    articulation() {}
    articulation(ll n) : g(n), ord(n, -1), low(n) {}

    void add_edge(ll u, ll v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<ll> build() {
        ll k = 0;
        vector<ll> ret;
        REP(i, g.size()) if(ord[i]==-1) dfs(i, -1, k, ret);
        return ret;
    }
};
#line 4 "test/GRL3A.test.cpp"

int main() {
    ll n, m;
    cin >> n >> m;
    articulation graph(n);
    REP(i, m) {
        ll s, t;
        cin >> s >> t;
        graph.add_edge(s, t);
    }
    auto ret = graph.build();
    sort(ALL(ret));
    for(auto i: ret) cout << i << "\n";
    cout << flush;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

