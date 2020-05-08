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


# :warning: generate/random_set.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#15117b282328146ac6afebaa8acd80e7">generate</a>
* <a href="{{ site.github.repository_url }}/blob/master/generate/random_set.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 15:59:02+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class T>
class random_set {
    struct Xor128 {
        unsigned x, y, z, w;
        Xor128(unsigned _w) { x = 123456789; y = 362436069; z = 521288629; w = _w; }
        unsigned nextUInt() {
            unsigned t = (x ^ (x << 11));
            x = y; y = z; z = w;
            return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
        }
    } rnd;
    unordered_set<T> st;
    vector<T> v;
public:
    random_set(unsigned seed = 88675123) : rnd(seed) {}
    auto begin() { return st.begin(); }
    auto end() { return st.end(); }
    bool empty() { return st.empty(); }
    size_t size() { return st.size(); }
    auto insert(T key) {
        auto ret = st.insert(key);
        if(ret.second == true) v.push_back(key);
        return ret;
    }
    T random() {
        unsigned idx = rnd.nextUInt() % size();
        return v[idx];
    }
    T pop_random() {
        unsigned idx = rnd.nextUInt() % size();
        T key = v[idx];
        swap(v[idx], v.back());
        st.erase(key);
        v.pop_back();
        return key;
    }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "generate/random_set.cpp"
template<class T>
class random_set {
    struct Xor128 {
        unsigned x, y, z, w;
        Xor128(unsigned _w) { x = 123456789; y = 362436069; z = 521288629; w = _w; }
        unsigned nextUInt() {
            unsigned t = (x ^ (x << 11));
            x = y; y = z; z = w;
            return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
        }
    } rnd;
    unordered_set<T> st;
    vector<T> v;
public:
    random_set(unsigned seed = 88675123) : rnd(seed) {}
    auto begin() { return st.begin(); }
    auto end() { return st.end(); }
    bool empty() { return st.empty(); }
    size_t size() { return st.size(); }
    auto insert(T key) {
        auto ret = st.insert(key);
        if(ret.second == true) v.push_back(key);
        return ret;
    }
    T random() {
        unsigned idx = rnd.nextUInt() % size();
        return v[idx];
    }
    T pop_random() {
        unsigned idx = rnd.nextUInt() % size();
        T key = v[idx];
        swap(v[idx], v.back());
        st.erase(key);
        v.pop_back();
        return key;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

