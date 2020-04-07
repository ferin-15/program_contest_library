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


# :heavy_check_mark: test/yuki998.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yuki998.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-07 21:51:26+09:00


* see: <a href="https://yukicoder.me/problems/no/998">https://yukicoder.me/problems/no/998</a>


## Depends on

* :question: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://yukicoder.me/problems/no/998"
#include "../memo/macro.hpp"

signed main(void) {
    vector<ll> v(4);
    REP(i, 4) cin >> v[i];
    sort(ALL(v));

    bool flag = true;
    FOR(i, 1, 4) if(v[i] != v[i-1]+1) flag = false;
    if(flag) cout << "Yes" << endl;
    else cout << "No" << endl;

    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yuki998.test.cpp"
#define PROBLEM "https://yukicoder.me/problems/no/998"
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
#line 3 "test/yuki998.test.cpp"

signed main(void) {
    vector<ll> v(4);
    REP(i, 4) cin >> v[i];
    sort(ALL(v));

    bool flag = true;
    FOR(i, 1, 4) if(v[i] != v[i-1]+1) flag = false;
    if(flag) cout << "Yes" << endl;
    else cout << "No" << endl;

    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

