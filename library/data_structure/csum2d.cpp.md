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


# :warning: data_structure/csum2d.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/csum2d.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-16 19:37:32+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
template<class T>
class csum2d {
    ll h, w;
    vector<vector<T>> rui;
public:
    csum2d(vector<vector<T>> v) : h(v.size()), w(v[0].size()), rui(v) {
        REP(i, h) REP(j, w) {
            if(!i && !j) {}
            else if(!i) rui[i][j] += rui[i][j-1];
            else if(!j) rui[i][j] += rui[i-1][j];
            else rui[i][j] += rui[i-1][j]+rui[i][j-1]-rui[i-1][j-1];
        }
    }
    T get(ll sx, ll sy, ll gx, ll gy) {
        if(!sx && !sy) return rui[gy][gx];
        if(!sx) return rui[gy][gx]-rui[sy-1][gx];
        if(!sy) return rui[gy][gx]-rui[gy][sx-1];
        return rui[gy][gx]-rui[sy-1][gx]-rui[gy][sx-1]+rui[sy-1][sx-1];
    };
};
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/csum2d.cpp"
// BEGIN CUT
template<class T>
class csum2d {
    ll h, w;
    vector<vector<T>> rui;
public:
    csum2d(vector<vector<T>> v) : h(v.size()), w(v[0].size()), rui(v) {
        REP(i, h) REP(j, w) {
            if(!i && !j) {}
            else if(!i) rui[i][j] += rui[i][j-1];
            else if(!j) rui[i][j] += rui[i-1][j];
            else rui[i][j] += rui[i-1][j]+rui[i][j-1]-rui[i-1][j-1];
        }
    }
    T get(ll sx, ll sy, ll gx, ll gy) {
        if(!sx && !sy) return rui[gy][gx];
        if(!sx) return rui[gy][gx]-rui[sy-1][gx];
        if(!sy) return rui[gy][gx]-rui[gy][sx-1];
        return rui[gy][gx]-rui[sy-1][gx]-rui[gy][sx-1]+rui[sy-1][sx-1];
    };
};
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

