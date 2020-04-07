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


# :heavy_check_mark: memo/macro.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d504a5ea65b088497578bdd812714d51">memo</a>
* <a href="{{ site.github.repository_url }}/blob/master/memo/macro.hpp">View this file on GitHub</a>
    - Last commit date: 2020-01-22 00:44:24+09:00




## Required by

* :warning: <a href="../test/DSL2F.memo.cpp.html">test/DSL2F.memo.cpp</a>
* :warning: <a href="../test/GRL4B.memo.cpp.html">test/GRL4B.memo.cpp</a>
* :warning: <a href="../test/aoj2991.memo.cpp.html">test/aoj2991.memo.cpp</a>
* :warning: <a href="../test/sqrt_mod.memo.cpp.html">test/sqrt_mod.memo.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/ALDS1_10_A.test.cpp.html">test/ALDS1_10_A.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DPL3B.test.cpp.html">test/DPL3B.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DPL3C.test.cpp.html">test/DPL3C.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DSL1A.test.cpp.html">test/DSL1A.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DSL2A_0.test.cpp.html">test/DSL2A_0.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DSL2A_1.test.cpp.html">test/DSL2A_1.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DSL2B_0.test.cpp.html">test/DSL2B_0.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DSL2B_1.test.cpp.html">test/DSL2B_1.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DSL2B_2.test.cpp.html">test/DSL2B_2.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DSL2F.test.cpp.html">test/DSL2F.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DSL2G_0.test.cpp.html">test/DSL2G_0.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DSL2G_1.test.cpp.html">test/DSL2G_1.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DSL2H_0.test.cpp.html">test/DSL2H_0.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DSL2H_1.test.cpp.html">test/DSL2H_1.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DSL2I_0.test.cpp.html">test/DSL2I_0.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DSL2I_1.test.cpp.html">test/DSL2I_1.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DSL3D.test.cpp.html">test/DSL3D.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DSL3D_1.test.cpp.html">test/DSL3D_1.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/GRL2A.test.cpp.html">test/GRL2A.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/GRL3A.test.cpp.html">test/GRL3A.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/GRL3B.test.cpp.html">test/GRL3B.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/GRL3C.test.cpp.html">test/GRL3C.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/GRL5C_0.test.cpp.html">test/GRL5C_0.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/GRL5C_1.test.cpp.html">test/GRL5C_1.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/GRL5C_2.test.cpp.html">test/GRL5C_2.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/GRL5C_3.test.cpp.html">test/GRL5C_3.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/GRL5D.test.cpp.html">test/GRL5D.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/GRL5E.test.cpp.html">test/GRL5E.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/GRL6A_0.test.cpp.html">test/GRL6A_0.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/GRL6A_1.test.cpp.html">test/GRL6A_1.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/GRL6A_2.test.cpp.html">test/GRL6A_2.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/GRL6B.test.cpp.html">test/GRL6B.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj0425.test.cpp.html">test/aoj0425.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj0575_0.test.cpp.html">test/aoj0575_0.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj0575_1.test.cpp.html">test/aoj0575_1.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj1308.test.cpp.html">test/aoj1308.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj1501.test.cpp.html">test/aoj1501.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj1508.test.cpp.html">test/aoj1508.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj1549.test.cpp.html">test/aoj1549.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj1617.test.cpp.html">test/aoj1617.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj2235.test.cpp.html">test/aoj2235.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj2270.test.cpp.html">test/aoj2270.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj2444.test.cpp.html">test/aoj2444.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj2450.test.cpp.html">test/aoj2450.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj2580_0.test.cpp.html">test/aoj2580_0.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj2580_1.test.cpp.html">test/aoj2580_1.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj2603.test.cpp.html">test/aoj2603.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj2659.test.cpp.html">test/aoj2659.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj2667.test.cpp.html">test/aoj2667.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj2674.test.cpp.html">test/aoj2674.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj2674_1.test.cpp.html">test/aoj2674_1.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj2873.test.cpp.html">test/aoj2873.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj2983.test.cpp.html">test/aoj2983.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj2987.test.cpp.html">test/aoj2987.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj2987_2.test.cpp.html">test/aoj2987_2.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj2996.test.cpp.html">test/aoj2996.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj2996_0.test.cpp.html">test/aoj2996_0.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj2996_1.test.cpp.html">test/aoj2996_1.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo-2SAT.test.cpp.html">test/yosupo-2SAT.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo-maximumIndependentSet.test.cpp.html">test/yosupo-maximumIndependentSet.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo-unionfind.test.cpp.html">test/yosupo-unionfind.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo-vertexaddsubtreesum.test.cpp.html">test/yosupo-vertexaddsubtreesum.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yuki42_1.test.cpp.html">test/yuki42_1.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yuki42_2.test.cpp.html">test/yuki42_2.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yuki42_3.test.cpp.html">test/yuki42_3.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yuki599.test.cpp.html">test/yuki599.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yuki899.test.cpp.html">test/yuki899.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yuki983.test.cpp.html">test/yuki983.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yuki998.test.cpp.html">test/yuki998.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

