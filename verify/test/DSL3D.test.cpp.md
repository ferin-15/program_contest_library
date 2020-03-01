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


# :heavy_check_mark: test/DSL3D.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/DSL3D.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-22 00:44:24+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/sparse_table.cpp.html">data_structure/sparse_table.cpp</a>
* :heavy_check_mark: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D&lang=ja"
#include "../memo/macro.hpp"
#include "../data_structure/sparse_table.cpp"

signed main(void) {
    ll n, l;
    cin >> n >> l;
    vector<ll> a(n);
    REP(i, n) cin >> a[i];

    sparseTable<minnimum> st(n);
    st.init(a);
    FOR(i, l-1, n) cout << st.query(i-l+1, i) << (i==n-1?'\n':' ');

    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/DSL3D.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D&lang=ja"
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
#line 1 "test/../data_structure/sparse_table.cpp"
template <typename S>
struct sparseTable {
    using T = typename S::T;
    int n;
    vector<int> log2;
    vector<vector<T>> t;

    sparseTable() {}
    sparseTable(int nn) { construct(nn); }
    void construct(int nn) {
        n = nn;
        log2.assign(n+1, 0);
        for(int i=2; i<=n; ++i) log2[i] = log2[i >> 1] + 1;
        t = vector<vector<T>>(log2[n]+1, vector<T>(n));
    }
    void init(vector<T> v) {
        for(int i=0; i<n; ++i) t[0][i] = v[i];
        for(int j=1; j<=log2[n]; ++j) {
            int w = 1LL<<(j-1);
            for (int i = 0; i+(w<<1) <= n; ++i) {
                t[j][i] = S::op(t[j-1][i], t[j-1][i+w]);
            }
        }
    }
    // [l, r]
    T query(int l, int r) {
        int j = log2[r - l];
        return S::op(t[j][l], t[j][r-(1 << j)+1]);
    }
};

// 集合T、結合則・可換・冪等律が成り立つ二項演算op
struct minnimum {
    using T = ll;
    static T op(const T& a, const T& b) { return min(a, b); }
};
struct maximum {
    using T = ll;
    static T op(const T& a, const T& b) { return max(a, b); }
};
struct gcd_op {
    using T = ll;
    static T op(const T& a, const T& b) { return __gcd(a, b); }
};
#line 4 "test/DSL3D.test.cpp"

signed main(void) {
    ll n, l;
    cin >> n >> l;
    vector<ll> a(n);
    REP(i, n) cin >> a[i];

    sparseTable<minnimum> st(n);
    st.init(a);
    FOR(i, l-1, n) cout << st.query(i-l+1, i) << (i==n-1?'\n':' ');

    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

