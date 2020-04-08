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


# :heavy_check_mark: test/yuki983.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yuki983.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-08 00:27:03+09:00


* see: <a href="https://yukicoder.me/problems/no/983">https://yukicoder.me/problems/no/983</a>


## Depends on

* :heavy_check_mark: <a href="../../library/math/fzt_fmt.cpp.html">math/fzt_fmt.cpp</a>
* :question: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://yukicoder.me/problems/no/983"
#include "../memo/macro.hpp"
#include "../math/fzt_fmt.cpp"

int main(void) {
    ll n;
    cin >> n;
    vector<ll> a(n);
    REP(i, n) {
        cin >> a[i];
        if(a[i]==-1) a[i] = 0;
    }

    if(n <= 20) {
        auto v = convAND(a, a);
        ll g = 0;
        REP(i, n) g = gcd(g, v[i]);
        cout << (g==0 ? -1 : g) << endl;
    } else {
        ll g = 0;
        REP(i, n) g = gcd(g, a[i]);
        cout << (g==0 ? -1 : g*g) << endl;
    }

    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yuki983.test.cpp"
#define PROBLEM "https://yukicoder.me/problems/no/983"
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
#line 1 "math/fzt_fmt.cpp"
// BEGIN CUT
// a.size() は2べき
// upper: g(S) = \sum_{S \subseteq T} f(T)
// lower: g(S) = \sum_{T \subseteq S} f(T)
template<bool upper>
vector<ll> fzt(vector<ll> a) {
    const int n = log2(a.size());
    REP(i, n) REP(j, 1LL<<n) {
        if(upper && !(j&1LL<<i)) a[j] += a[j|(1LL<<i)];
        else if(!upper && (j&1LL<<i)) a[j] += a[j^(1LL<<i)];
    }
    return a;
}
// a.size() は2べき
// upper: f(S) = \sum_{S \subseteq T} (-1)^(|T\S|) g(T)
// lower: f(S) = \sum_{T \subseteq S} (-1)^(|T\S|) g(T)
template<bool upper>
vector<ll> fmt(vector<ll> a) {
    const int n = log2(a.size());
    REP(i, n) REP(j, 1LL<<n) {
        if(upper && !(j&1LL<<i)) a[j] -= a[j|(1LL<<i)];
        else if(!upper && (j&1LL<<i)) a[j] -= a[j^(1LL<<i)];
    }
    return a;
}

// a.size(),b.size() は2べき
// c_k = \sum_{k = i & j} a_ib_j
vector<ll> convAND(vector<ll> a, vector<ll> b) {
    a = fzt<true>(a);
    b = fzt<true>(b);
    REP(i, a.size()) a[i] *= b[i];
    return fmt<true>(a);
}
// a.size(),b.size() は2べき
// c_k = \sum_{k = i | j} a_ib_j
vector<ll> convOR(vector<ll> a, vector<ll> b) {
    a = fzt<false>(a);
    b = fzt<false>(b);
    REP(i, a.size()) a[i] *= b[i];
    return fmt<false>(a);
}
// END CUT
#line 4 "test/yuki983.test.cpp"

int main(void) {
    ll n;
    cin >> n;
    vector<ll> a(n);
    REP(i, n) {
        cin >> a[i];
        if(a[i]==-1) a[i] = 0;
    }

    if(n <= 20) {
        auto v = convAND(a, a);
        ll g = 0;
        REP(i, n) g = gcd(g, v[i]);
        cout << (g==0 ? -1 : g) << endl;
    } else {
        ll g = 0;
        REP(i, n) g = gcd(g, a[i]);
        cout << (g==0 ? -1 : g*g) << endl;
    }

    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

