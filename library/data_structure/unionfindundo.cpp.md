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


# :x: data_structure/unionfindundo.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/unionfindundo.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 21:46:34+09:00




## Verified with

* :x: <a href="../../verify/test/aoj2235.test.cpp.html">test/aoj2235.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct UnionFindUndo {
    vector<int> data;
    stack<PII> st;

    UnionFindUndo(int sz) : data(sz, -1) {}

    int find(int k) {
        if(data[k] < 0) return (k);
        return (find(data[k]));
    }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        st.emplace(x, data[x]);
        st.emplace(y, data[y]);
        if(x == y) return;
        if(data[x] > data[y]) swap(x, y);
        data[x] += data[y];
        data[y] = x;
    }
    void undo() {
        data[st.top().first] = st.top().second;
        st.pop();
        data[st.top().first] = st.top().second;
        st.pop();
    }
    bool same(int x, int y) { return find(x) == find(y); }
    int size(int k) { return (-data[find(k)]); }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/unionfindundo.cpp"
struct UnionFindUndo {
    vector<int> data;
    stack<PII> st;

    UnionFindUndo(int sz) : data(sz, -1) {}

    int find(int k) {
        if(data[k] < 0) return (k);
        return (find(data[k]));
    }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        st.emplace(x, data[x]);
        st.emplace(y, data[y]);
        if(x == y) return;
        if(data[x] > data[y]) swap(x, y);
        data[x] += data[y];
        data[y] = x;
    }
    void undo() {
        data[st.top().first] = st.top().second;
        st.pop();
        data[st.top().first] = st.top().second;
        st.pop();
    }
    bool same(int x, int y) { return find(x) == find(y); }
    int size(int k) { return (-data[find(k)]); }
};
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

