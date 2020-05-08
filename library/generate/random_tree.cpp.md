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


# :warning: generate/random_tree.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#15117b282328146ac6afebaa8acd80e7">generate</a>
* <a href="{{ site.github.repository_url }}/blob/master/generate/random_tree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 15:59:02+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
vector<pair<int,int>> random_tree(int n, unsigned seed1 = 1, unsigned seed2 = 2) {
    random_set<int> t(seed1), g(seed2);

    vector<pair<int,int>> edges;
    for(int i=0; i<n; ++i) g.insert(i);
    t.insert(g.pop_random());
    for(int i=0; i<n-1; ++i) {
        int u = t.random();
        int v = g.pop_random();
        edges.emplace_back(u, v);
        t.insert(v);
    }

    return 
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "generate/random_tree.cpp"
vector<pair<int,int>> random_tree(int n, unsigned seed1 = 1, unsigned seed2 = 2) {
    random_set<int> t(seed1), g(seed2);

    vector<pair<int,int>> edges;
    for(int i=0; i<n; ++i) g.insert(i);
    t.insert(g.pop_random());
    for(int i=0; i<n-1; ++i) {
        int u = t.random();
        int v = g.pop_random();
        edges.emplace_back(u, v);
        t.insert(v);
    }

    return 
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

