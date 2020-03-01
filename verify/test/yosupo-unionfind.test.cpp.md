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


# :heavy_check_mark: test/yosupo-unionfind.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo-unionfind.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 10:25:01+09:00


* see: <a href="https://judge.yosupo.jp/problem/unionfind">https://judge.yosupo.jp/problem/unionfind</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/unionfind.cpp.html">data_structure/unionfind.cpp</a>
* :heavy_check_mark: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include "../memo/macro.hpp"
#include "../data_structure/unionfind.cpp"

int main() {
    ll n, q;
    cin >> n >> q;
    UnionFind uf(n);
    REP(i, q) {
        ll t, u, v;
        cin >> t >> u >> v;
        if(t == 0) uf.unite(u, v);
        else cout << uf.same(u, v) << "\n";
    }
    cout << flush;

    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo-unionfind.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
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
#line 1 "test/../data_structure/unionfind.cpp"
struct UnionFind {
    vector<ll> par, s;
    UnionFind(ll n) : par(n), s(n, 1) { iota(ALL(par), 0); }
    ll find(ll x) {
        if(par[x] == x) return x;
        return par[x] = find(par[x]);
    }
    void unite(ll x, ll y) {
        x = find(x), y = find(y);
        if(x == y) return;
        if(s[x] < s[y]) par[x] = y, s[y] += s[x];
        else par[y] = x, s[x] += s[y];
    }
    bool same(int x, int y) { return find(x) == find(y); }
    ll size(int x) { return s[find(x)]; }
};
#line 4 "test/yosupo-unionfind.test.cpp"

int main() {
    ll n, q;
    cin >> n >> q;
    UnionFind uf(n);
    REP(i, q) {
        ll t, u, v;
        cin >> t >> u >> v;
        if(t == 0) uf.unite(u, v);
        else cout << uf.same(u, v) << "\n";
    }
    cout << flush;

    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

