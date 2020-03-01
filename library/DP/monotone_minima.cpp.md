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


# :heavy_check_mark: DP/monotone_minima.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e2fca8135c2fadca093abd79a6b1c0d2">DP</a>
* <a href="{{ site.github.repository_url }}/blob/master/DP/monotone_minima.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj2603.test.cpp.html">test/aoj2603.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
// 各iについてf(i,*)のargminとminをペアで返す
template<typename T, typename Compare = less<T>>
vector<pair<ll,T>> monotone_minima(ll h, ll w, const function<T(ll,ll)> &f, const Compare &comp = Compare()) {
    vector<pair<ll,T>> dp(h);
    function<void(ll,ll,ll,ll)> dfs = [&](ll top, ll bottom, ll left, ll right) {
        if(top > bottom) return;
        ll line = (top + bottom) / 2;
        ll idx = left;
        T mi = f(line, left);
        for(ll i=left+1; i<=right; ++i) {
            T cost = f(line, i);
            if(comp(cost, mi)) {
                mi = cost;
                idx = i;
            }
        }
        dp[line] = make_pair(idx, mi);
        dfs(top, line-1, left, idx);
        dfs(line+1, bottom, idx, right);
    };
    dfs(0, h-1, 0, w-1);
    return dp;
}
// END CUT

// https://atcoder.jp/contests/colopl2018-final/tasks/colopl2018_final_c
namespace colocon2018finalC {
    void solve() {
        int n;
        cin >> n;
        vector<ll> a(n);
        REP(i, n) cin >> a[i];
        function<ll(ll,ll)> f = [&](ll i, ll j) {
            return a[j] + (j-i)*(j-i);
        };
        auto dp = monotone_minima(n, n, f);
        for(auto p: dp) cout << p.second << endl;
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "DP/monotone_minima.cpp"
// BEGIN CUT
// 各iについてf(i,*)のargminとminをペアで返す
template<typename T, typename Compare = less<T>>
vector<pair<ll,T>> monotone_minima(ll h, ll w, const function<T(ll,ll)> &f, const Compare &comp = Compare()) {
    vector<pair<ll,T>> dp(h);
    function<void(ll,ll,ll,ll)> dfs = [&](ll top, ll bottom, ll left, ll right) {
        if(top > bottom) return;
        ll line = (top + bottom) / 2;
        ll idx = left;
        T mi = f(line, left);
        for(ll i=left+1; i<=right; ++i) {
            T cost = f(line, i);
            if(comp(cost, mi)) {
                mi = cost;
                idx = i;
            }
        }
        dp[line] = make_pair(idx, mi);
        dfs(top, line-1, left, idx);
        dfs(line+1, bottom, idx, right);
    };
    dfs(0, h-1, 0, w-1);
    return dp;
}
// END CUT

// https://atcoder.jp/contests/colopl2018-final/tasks/colopl2018_final_c
namespace colocon2018finalC {
    void solve() {
        int n;
        cin >> n;
        vector<ll> a(n);
        REP(i, n) cin >> a[i];
        function<ll(ll,ll)> f = [&](ll i, ll j) {
            return a[j] + (j-i)*(j-i);
        };
        auto dp = monotone_minima(n, n, f);
        for(auto p: dp) cout << p.second << endl;
    }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

