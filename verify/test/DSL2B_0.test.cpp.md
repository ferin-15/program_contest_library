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


# :heavy_check_mark: test/DSL2B_0.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/DSL2B_0.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-22 00:44:24+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=jp">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=jp</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/BIT.cpp.html">data_structure/BIT.cpp</a>
* :heavy_check_mark: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=jp"
#include "../memo/macro.hpp"
#include "../data_structure/BIT.cpp"

signed main(void) {
    ll n, q;
    cin >> n >> q;
    BIT<ll> bit(100010);
    while(q--) {
        ll t, x, y;
        cin >> t >> x >> y;
        if(t == 0) {
            bit.update(x, y);
        } else {
            cout << bit.query(y) - bit.query(x-1) << endl;
        }
    }

    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/DSL2B_0.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=jp"
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
const ll INF = 1LL<<60;#line 1 "test/../data_structure/BIT.cpp"
template <typename T>
struct BIT {
    int n;
    vector<T> bit;
    BIT(int n_ = 1e5) { init(n_); }
    void init(int sz) { 
        n=1; while(n < sz) n*=2;
        bit.assign(n+1, 0); 
    }
    void update(int i, T w) {
        for(int x=i+1; x<(int)bit.size(); x += x&-x) bit[x] += w;
    }
    // [0,i]
    T query(int i) {
        T ret = 0;
        for(int x=i+1; x>0; x -= x&-x) ret += bit[x];
        return ret;
    }
    // 合計がw以上の最小の位置
    int lower_bound(T w) {
        int x = 0;
        for(int k=n; k>0; k>>=1) {
            if(x+k <= n && bit[x+k] < w) {
                w -= bit[x+k];
                x += k;
            }
        }
        return x;
    }
};#line 4 "test/DSL2B_0.test.cpp"

signed main(void) {
    ll n, q;
    cin >> n >> q;
    BIT<ll> bit(100010);
    while(q--) {
        ll t, x, y;
        cin >> t >> x >> y;
        if(t == 0) {
            bit.update(x, y);
        } else {
            cout << bit.query(y) - bit.query(x-1) << endl;
        }
    }

    return 0;
}
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

