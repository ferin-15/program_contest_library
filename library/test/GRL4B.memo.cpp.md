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


# :warning: test/GRL4B.memo.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/GRL4B.memo.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-22 00:44:24+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/4/GRL_4_B">https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/4/GRL_4_B</a>


## Depends on

* :warning: <a href="../graph/topological.cpp.html">graph/topological.cpp</a>
* :heavy_check_mark: <a href="../memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/4/GRL_4_B"
#include "../memo/macro.hpp"
#include "../graph/topological.cpp"

// スペシャルジャッジだからだめ
signed main(void) {
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> g(n);
    REP(i, m) {
        ll u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    auto ans = tsort(g);
    for(auto p: ans) cout << p.first << endl;

    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/GRL4B.memo.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/4/GRL_4_B"
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
const ll INF = 1LL<<60;#line 1 "test/../graph/topological.cpp"
// ans[i] = (i番目の頂点v, swapできる頂点をまとめたときにvが何番目か)
vector<PII> tsort(vector<vector<ll>> g) {
    const int n = g.size();
    vector<ll> h(n);
    REP(i, n) for(int j: g[i]) h[j]++;

    stack<PII> st;
    REP(i, n) if(h[i] == 0) st.push({i, 0});

    vector<PII> ans;
    while(st.size()) {
        PII p = st.top(); st.pop();
        ans.push_back(p);
        for(auto& j: g[p.first]) {
            h[j]--;
            if(h[j] == 0) st.push({j, p.second+1});
        }
    }

    return ans;
}#line 4 "test/GRL4B.memo.cpp"

// スペシャルジャッジだからだめ
signed main(void) {
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> g(n);
    REP(i, m) {
        ll u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    auto ans = tsort(g);
    for(auto p: ans) cout << p.first << endl;

    return 0;
}
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

