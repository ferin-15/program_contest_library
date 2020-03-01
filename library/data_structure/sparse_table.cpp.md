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


# :heavy_check_mark: data_structure/sparse_table.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/sparse_table.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/DSL3D.test.cpp.html">test/DSL3D.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/GRL5C_2.test.cpp.html">test/GRL5C_2.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
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
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/sparse_table.cpp"
// BEGIN CUT
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
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

