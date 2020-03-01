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


# :heavy_check_mark: data_structure/sliding_window_aggregation.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/sliding_window_aggregation.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-17 15:38:10+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/DSL3D_1.test.cpp.html">test/DSL3D_1.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class T, class S, class F>
struct SWAG {
    // using F = function<S(S,T)>;
    F f; S id;
    stack<T> lt, rt;
    stack<S> ls, rs;
    SWAG(F f, S d) : f(f), id(d) {
        ls.push(id);
        rs.push(id);
    }
    void push_back(T x) { 
        rt.push(x);
        rs.push(f(rs.top(), x));
    }
    void pop_front() {
        if(lt.empty()) {
            while(rt.size()) {
                T x = rt.top(); rt.pop(); rs.pop();
                lt.push(x);
                ls.push(f(ls.top(), x));
            }
        }
        lt.pop();
        ls.pop();
    }
    template<class Q>
    void fold(Q q) { q(ls.top(), rs.top()); }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/sliding_window_aggregation.cpp"
template<class T, class S, class F>
struct SWAG {
    // using F = function<S(S,T)>;
    F f; S id;
    stack<T> lt, rt;
    stack<S> ls, rs;
    SWAG(F f, S d) : f(f), id(d) {
        ls.push(id);
        rs.push(id);
    }
    void push_back(T x) { 
        rt.push(x);
        rs.push(f(rs.top(), x));
    }
    void pop_front() {
        if(lt.empty()) {
            while(rt.size()) {
                T x = rt.top(); rt.pop(); rs.pop();
                lt.push(x);
                ls.push(f(ls.top(), x));
            }
        }
        lt.pop();
        ls.pop();
    }
    template<class Q>
    void fold(Q q) { q(ls.top(), rs.top()); }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

