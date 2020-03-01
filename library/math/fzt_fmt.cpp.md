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


# :warning: math/fzt_fmt.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/fzt_fmt.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 10:06:25+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// a.size() は2べき
// upper: g(S) = \sum_{S \subseteq T} f(T)
// lower: g(S) = \sum_{T \subseteq S} f(T)
template<bool upper>
vector<ll> fzt(vector<ll> a) {
    const int n = log2(a.size());
    REP(i, n) REP(j, 1LL<<n) {
        if(upper && !(j&1LL<<i)) a[j] += a[j|(1LL<<i)];
        else if(!upper && (j&1LL<<i)) a[j] += a[j^(1LL<<i)];
    }
    return a;
}
// a.size() は2べき
// upper: f(S) = \sum_{S \subseteq T} (-1)^(|T\S|) g(T)
// lower: f(S) = \sum_{T \subseteq S} (-1)^(|T\S|) g(T)
template<bool upper>
vector<ll> fmt(vector<ll> a) {
    const int n = log2(a.size());
    REP(i, n) REP(j, 1LL<<n) {
        if(upper && !(j&1LL<<i)) a[j] -= a[j|(1LL<<i)];
        else if(!upper && (j&1LL<<i)) a[j] -= a[j^(1LL<<i)];
    }
    return a;
}

// a.size(),b.size() は2べき
// c_k = \sum_{k = i & j} a_ib_j
vector<ll> convAND(vector<ll> a, vector<ll> b) {
    a = fzt<true>(a);
    b = fzt<true>(b);
    REP(i, a.size()) a[i] *= b[i];
    return fmt<true>(a);
}
// a.size(),b.size() は2べき
// c_k = \sum_{k = i | j} a_ib_j
vector<ll> convOR(vector<ll> a, vector<ll> b) {
    a = fzt<false>(a);
    b = fzt<false>(b);
    REP(i, a.size()) a[i] *= b[i];
    return fmt<false>(a);
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/fzt_fmt.cpp"
// a.size() は2べき
// upper: g(S) = \sum_{S \subseteq T} f(T)
// lower: g(S) = \sum_{T \subseteq S} f(T)
template<bool upper>
vector<ll> fzt(vector<ll> a) {
    const int n = log2(a.size());
    REP(i, n) REP(j, 1LL<<n) {
        if(upper && !(j&1LL<<i)) a[j] += a[j|(1LL<<i)];
        else if(!upper && (j&1LL<<i)) a[j] += a[j^(1LL<<i)];
    }
    return a;
}
// a.size() は2べき
// upper: f(S) = \sum_{S \subseteq T} (-1)^(|T\S|) g(T)
// lower: f(S) = \sum_{T \subseteq S} (-1)^(|T\S|) g(T)
template<bool upper>
vector<ll> fmt(vector<ll> a) {
    const int n = log2(a.size());
    REP(i, n) REP(j, 1LL<<n) {
        if(upper && !(j&1LL<<i)) a[j] -= a[j|(1LL<<i)];
        else if(!upper && (j&1LL<<i)) a[j] -= a[j^(1LL<<i)];
    }
    return a;
}

// a.size(),b.size() は2べき
// c_k = \sum_{k = i & j} a_ib_j
vector<ll> convAND(vector<ll> a, vector<ll> b) {
    a = fzt<true>(a);
    b = fzt<true>(b);
    REP(i, a.size()) a[i] *= b[i];
    return fmt<true>(a);
}
// a.size(),b.size() は2べき
// c_k = \sum_{k = i | j} a_ib_j
vector<ll> convOR(vector<ll> a, vector<ll> b) {
    a = fzt<false>(a);
    b = fzt<false>(b);
    REP(i, a.size()) a[i] *= b[i];
    return fmt<false>(a);
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

