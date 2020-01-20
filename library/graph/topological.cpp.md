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


# :warning: graph/topological.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/topological.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 04:35:05+09:00




## Required by

* :warning: <a href="../test/GRL4B.memo.cpp.html">test/GRL4B.memo.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// ans[i] = (i番目の頂点v, swapできる頂点をまとめたときにvが何番目か)
vector<PII> tsort(vector<vector<ll>> g) {
    const int n = g.size();
    vector<ll> h(n, 0);
    REP(i, n) for(int j: g[i]) h[j]++;

    stack<PII> st;
    REP(i, n) if(h[i] == 0) st.push({i, 0});

    vector<PII> ans;
    while(st.size()) {
        PII p = st.top(); st.pop();
        ans.push_back(p);
        for(auto& j: g[p.first]) {
            h[j]--;
            if(h[j] == 0) st.push({j, p.second+1});
        }
    }

    return ans;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/topological.cpp"
// ans[i] = (i番目の頂点v, swapできる頂点をまとめたときにvが何番目か)
vector<PII> tsort(vector<vector<ll>> g) {
    const int n = g.size();
    vector<ll> h(n, 0);
    REP(i, n) for(int j: g[i]) h[j]++;

    stack<PII> st;
    REP(i, n) if(h[i] == 0) st.push({i, 0});

    vector<PII> ans;
    while(st.size()) {
        PII p = st.top(); st.pop();
        ans.push_back(p);
        for(auto& j: g[p.first]) {
            h[j]--;
            if(h[j] == 0) st.push({j, p.second+1});
        }
    }

    return ans;
}
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

