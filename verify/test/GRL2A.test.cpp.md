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


# :heavy_check_mark: test/GRL2A.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/GRL2A.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/unionfind.cpp.html">data_structure/unionfind.cpp</a>
* :heavy_check_mark: <a href="../../library/graph/boruvka.cpp.html">graph/boruvka.cpp</a>
* :heavy_check_mark: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=ja"
#include "../memo/macro.hpp"
#include "../data_structure/unionfind.cpp"
#include "../graph/boruvka.cpp"

signed main(void) {
    ll n, m;
    cin >> n >> m;
    vector<vector<PII>> g(n);
    REP(i, m) {
        ll a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }

    // O(fの計算量 * logV)
    // 各頂点から最小のコストの辺を求める
    // sz=連結成分数 belong[i]=i番目の頂点が属する連結成分
    function<vector<PII>(ll,vector<ll>)> f = [&](ll sz, vector<ll> belong) {
        // ret[i] = (連結成分iからコスト最小の辺の(コスト, i以外の端点の連結成分))
        // iがufの親以外ならsecondは-1として連結成分ごとに管理
        vector<PII> ret(sz, PII(INF, -1));

        REP(i, n) for(auto to: g[i]) {
            if(belong[i] == belong[to.first]) continue;
            chmin(ret[belong[i]], PII(to.second, belong[to.first]));
        }
        return ret;
    };
    cout << boruvka<ll, decltype(f)>(n, f) << endl;

    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/GRL2A.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=ja"
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
#line 1 "data_structure/unionfind.cpp"
// BEGIN CUT
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
// END CUT
#line 1 "graph/boruvka.cpp"
// BEGIN CUT
template< typename T, typename F >
T boruvka(ll n, F f) {
    vector<ll> rev(n), belong(n);
    UnionFind uf(n);
    T ret = T();
    while(uf.size(0) != n) {
        ll ptr = 0;
        REP(i, n) if(uf.find(i) == i) belong[i] = ptr++, rev[belong[i]] = i;
        REP(i, n) belong[i] = belong[uf.find(i)];
        vector<PII> v = f(ptr, belong);
        bool update = false;
        REP(i, ptr) {
            if(~v[i].second && !uf.same(rev[i], rev[v[i].second])) {
                uf.unite(rev[i], rev[v[i].second]);
                ret += v[i].first;
                update = true;
            }
        }
        if(!update) return -1; // notice!!
    }
    return ret;
}

/*
// O(fの計算量 * logV)
// 各頂点から最小のコストの辺を求める
// sz=連結成分数 belong[i]=i番目の頂点が属する連結成分
function<vector<PII>(ll,vector<ll>)> f = [&](ll sz, vector<ll> belong) {
    // ret[i] = (連結成分iからコスト最小の辺の(コスト, i以外の端点の連結成分))
    // iがufの親以外ならsecondは-1として連結成分ごとに管理
    vector<PII> ret(sz, PII(LLINF, -1));
    REP(i, n) for(auto to: g[i]) {
        if(belong[i] == belong[to.first]) continue;
        chmin(ret[belong[i]], PII(to.second, belong[to.first]));
    }
    return ret;
};
cout << boruvka<ll, decltype(f)>(n, f) << endl;
*/
// END CUT
#line 5 "test/GRL2A.test.cpp"

signed main(void) {
    ll n, m;
    cin >> n >> m;
    vector<vector<PII>> g(n);
    REP(i, m) {
        ll a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }

    // O(fの計算量 * logV)
    // 各頂点から最小のコストの辺を求める
    // sz=連結成分数 belong[i]=i番目の頂点が属する連結成分
    function<vector<PII>(ll,vector<ll>)> f = [&](ll sz, vector<ll> belong) {
        // ret[i] = (連結成分iからコスト最小の辺の(コスト, i以外の端点の連結成分))
        // iがufの親以外ならsecondは-1として連結成分ごとに管理
        vector<PII> ret(sz, PII(INF, -1));

        REP(i, n) for(auto to: g[i]) {
            if(belong[i] == belong[to.first]) continue;
            chmin(ret[belong[i]], PII(to.second, belong[to.first]));
        }
        return ret;
    };
    cout << boruvka<ll, decltype(f)>(n, f) << endl;

    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

