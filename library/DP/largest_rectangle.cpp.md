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


# :heavy_check_mark: DP/largest_rectangle.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e2fca8135c2fadca093abd79a6b1c0d2">DP</a>
* <a href="{{ site.github.repository_url }}/blob/master/DP/largest_rectangle.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-08 18:07:26+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/DPL3B.test.cpp.html">test/DPL3B.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DPL3C.test.cpp.html">test/DPL3C.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
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
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "DP/largest_rectangle.cpp"
// BEGIN CUT
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
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

