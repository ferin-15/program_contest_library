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


# :warning: DP/zenhoui.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e2fca8135c2fadca093abd79a6b1c0d2">DP</a>
* <a href="{{ site.github.repository_url }}/blob/master/DP/zenhoui.cpp">View this file on GitHub</a>
    - Last commit date: 2019-07-14 12:12:28+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
vector<ll> dp(n);
function<void(ll,ll)> dfs1 = [&](ll v, ll p) {
    for(auto i: g[v]) if(i != p) {
        dfs1(i, v);
        chmax(dp[v], dp[i] + 1);
    }
};
dfs1(0, -1);

vector<ll> ans(n);
function<void(ll,ll,ll)> dfs2 = [&](ll v, ll d_par, ll p) {
    vector<PII> d_child;
    d_child.push_back({0, -1});
    for(auto i: g[v]) {
        if(i == p) d_child.push_back({d_par+1, i});
        else d_child.push_back({dist[i]+1, i});
    }
    sort(ALL(d_child), greater<>());
    ans[v] = d_child[0].first;
    for(auto i: g[v]) if(i != p) {
        dfs2(i, d_child[d_child[0].second == i].first, v);
    }
};
dfs2(0, 0, -1);

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "DP/zenhoui.cpp"
vector<ll> dp(n);
function<void(ll,ll)> dfs1 = [&](ll v, ll p) {
    for(auto i: g[v]) if(i != p) {
        dfs1(i, v);
        chmax(dp[v], dp[i] + 1);
    }
};
dfs1(0, -1);

vector<ll> ans(n);
function<void(ll,ll,ll)> dfs2 = [&](ll v, ll d_par, ll p) {
    vector<PII> d_child;
    d_child.push_back({0, -1});
    for(auto i: g[v]) {
        if(i == p) d_child.push_back({d_par+1, i});
        else d_child.push_back({dist[i]+1, i});
    }
    sort(ALL(d_child), greater<>());
    ans[v] = d_child[0].first;
    for(auto i: g[v]) if(i != p) {
        dfs2(i, d_child[d_child[0].second == i].first, v);
    }
};
dfs2(0, 0, -1);

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

