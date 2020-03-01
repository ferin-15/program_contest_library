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


# :heavy_check_mark: test/DPL3B.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/DPL3B.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-22 00:44:24+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/3/DPL_3_B">https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/3/DPL_3_B</a>


## Depends on

* :heavy_check_mark: <a href="../../library/DP/largest_Rectangle.cpp.html">DP/largest_Rectangle.cpp</a>
* :heavy_check_mark: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/3/DPL_3_B"
#include "../memo/macro.hpp"
#include "../DP/largest_Rectangle.cpp"

signed main(void) {
    ll h, w;
    cin >> h >> w;
    vector<vector<ll>> c(h, vector<ll>(w));
    REP(i, h) REP(j, w) cin >> c[i][j];

    cout << largeest_rectangle(c) << endl;

    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/DPL3B.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/3/DPL_3_B"
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
#line 1 "test/../DP/largest_Rectangle.cpp"
// i番目の高さがh[i]のヒストグラム中で最大の長方形の面積
ll largest_rectangle_histogram(vector<ll> h) {
    const ll n = h.size();

    // iを固定して高さがh[i]となる長方形を考えるとl,rは一意に定まる
    // l[i], r[i] をstackを使って求める

    // l[i] = (j<=iかつh[j-1]<h[i]となる最大のj)
    vector<ll> l(n);
    stack<ll> st1;
    REP(i, n) {
        while(st1.size() && h[st1.top()] >= h[i]) st1.pop();
        l[i] = st1.empty() ? 0 : (st1.top()+1);
        st1.push(i);
    }
    // r[i] = (j>iかつh[j]<h[i]となる最小のj)
    vector<ll> r(n);
    stack<ll> st2;
    for(ll i=n-1; i>=0; --i) {
        while(st2.size() && h[st2.top()] >= h[i]) st2.pop();
        r[i] = st2.empty() ? n : st2.top();
        st2.push(i);
    }
    ll ret = 0;
    REP(i, n) ret = max(ret, h[i]*(r[i]-l[i]));
    return ret;
}

// c[i][j] = 0 のマスだけを使って構成できる最大の長方形の面積を返す
ll largeest_rectangle(vector<vector<ll>> c) {
    const int h = c.size(), w = c[0].size();
    vector<vector<ll>> con(h, vector<ll>(w));

    REP(i, w) {
        int cnt = 1;
        REP(j, h) {
            if(!c[j][i]) {
                con[j][i] = cnt;
                cnt++;
            } else {
                con[j][i] = 0;
                cnt = 1;
            }
        }
    }

    ll ret = 0;
    REP(i, h) chmax(ret, largest_rectangle_histogram(con[i]));
    return ret;
}
#line 4 "test/DPL3B.test.cpp"

signed main(void) {
    ll h, w;
    cin >> h >> w;
    vector<vector<ll>> c(h, vector<ll>(w));
    REP(i, h) REP(j, w) cin >> c[i][j];

    cout << largeest_rectangle(c) << endl;

    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

