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


# :heavy_check_mark: data_structure/BIT.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/BIT.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 06:20:03+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/DSL2B_0.test.cpp.html">test/DSL2B_0.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj2270.test.cpp.html">test/aoj2270.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <typename T>
struct BIT {
    int n;
    vector<T> bit;
    BIT(int n_ = 1e5) { init(n_); }
    void init(int sz) { 
        n=1; while(n < sz) n*=2;
        bit.assign(n+1, 0); 
    }
    void update(int i, T w) {
        for(int x=i+1; x<(int)bit.size(); x += x&-x) bit[x] += w;
    }
    // [0,i]
    T query(int i) {
        T ret = 0;
        for(int x=i+1; x>0; x -= x&-x) ret += bit[x];
        return ret;
    }
    // 合計がw以上の最小の位置
    int lower_bound(T w) {
        int x = 0;
        for(int k=n; k>0; k>>=1) {
            if(x+k <= n && bit[x+k] < w) {
                w -= bit[x+k];
                x += k;
            }
        }
        return x;
    }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/BIT.cpp"
template <typename T>
struct BIT {
    int n;
    vector<T> bit;
    BIT(int n_ = 1e5) { init(n_); }
    void init(int sz) { 
        n=1; while(n < sz) n*=2;
        bit.assign(n+1, 0); 
    }
    void update(int i, T w) {
        for(int x=i+1; x<(int)bit.size(); x += x&-x) bit[x] += w;
    }
    // [0,i]
    T query(int i) {
        T ret = 0;
        for(int x=i+1; x>0; x -= x&-x) ret += bit[x];
        return ret;
    }
    // 合計がw以上の最小の位置
    int lower_bound(T w) {
        int x = 0;
        for(int k=n; k>0; k>>=1) {
            if(x+k <= n && bit[x+k] < w) {
                w -= bit[x+k];
                x += k;
            }
        }
        return x;
    }
};
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

