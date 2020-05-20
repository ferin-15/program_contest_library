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


# :heavy_check_mark: test/DSL3D_1.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/DSL3D_1.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/sliding_window_aggregation.cpp.html">data_structure/sliding_window_aggregation.cpp</a>
* :heavy_check_mark: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D&lang=ja"
#include "../memo/macro.hpp"
#include "../data_structure/sliding_window_aggregation.cpp"

int main() {
    ll n, l;
    cin >> n >> l;
    vector<ll> a(n);
    REP(i, n) cin >> a[i];

    auto f = [&](ll x, ll y) { return min(x, y); };
    SWAG<ll,ll,decltype(f)> swag(f, INF);

    REP(i, l-1) swag.push_back(a[i]);
    FOR(i, l-1, n) {
        swag.push_back(a[i]);
        ll ret;
        auto ask = [&](ll x, ll y) { ret = min(x, y); };
        swag.fold(ask);
        cout << ret << (i==n-1?'\n':' ');
        swag.pop_front();
    }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/DSL3D_1.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D&lang=ja"
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
#line 1 "data_structure/sliding_window_aggregation.cpp"
// BEGIN CUT
template<class T, class S, class F>
struct SWAG {
    // using F = function<S(S,T)>;
    F f; S id;
    stack<T> lt, rt;
    stack<S> ls, rs;
    SWAG(F f, S d) : f(f), id(d) {
        ls.push(id);
        rs.push(id);
    }
    void push_back(T x) { 
        rt.push(x);
        rs.push(f(rs.top(), x));
    }
    void pop_front() {
        if(lt.empty()) {
            while(rt.size()) {
                T x = rt.top(); rt.pop(); rs.pop();
                lt.push(x);
                ls.push(f(ls.top(), x));
            }
        }
        lt.pop();
        ls.pop();
    }
    template<class Q>
    void fold(Q q) { q(ls.top(), rs.top()); }
};
// END CUT
#line 4 "test/DSL3D_1.test.cpp"

int main() {
    ll n, l;
    cin >> n >> l;
    vector<ll> a(n);
    REP(i, n) cin >> a[i];

    auto f = [&](ll x, ll y) { return min(x, y); };
    SWAG<ll,ll,decltype(f)> swag(f, INF);

    REP(i, l-1) swag.push_back(a[i]);
    FOR(i, l-1, n) {
        swag.push_back(a[i]);
        ll ret;
        auto ask = [&](ll x, ll y) { ret = min(x, y); };
        swag.fold(ask);
        cout << ret << (i==n-1?'\n':' ');
        swag.pop_front();
    }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

