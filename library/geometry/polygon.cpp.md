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


# :warning: geometry/polygon.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed7daeb157cd9b31e53896ad3c771a26">geometry</a>
* <a href="{{ site.github.repository_url }}/blob/master/geometry/polygon.cpp">View this file on GitHub</a>
    - Last commit date: 2019-05-14 17:50:56+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// 面積 頂点が反時計回りに並んでいること
R area(const G& pol) {
    R ret = 0.0;
    REP(i, pol.size()) ret += det(pol[i], pol[(i+1)%pol.size()]);
    return (ret/2.0);
}

// 凸性の判定
bool isConvex(const G& pol) {
    REP(i, pol.size()) {
        if(sgn(det(pol[(i+1)%pol.size()]-pol[i], pol[(i+2)%pol.size()]-pol[i])) < 0) {
            return false;
        }
    }
    return true;
}

// 多角形と点の内包
// 2→in 1→on 0→out
int inPolygon(const G& pol, const P& p) {
    bool in = false;
    for (int i = 0; i < pol.size(); ++i) {
        P a = pol[i] - p, b = pol[(i+1)%pol.size()] - p;
        if (imag(a) > imag(b)) swap(a, b);
        if (imag(a) <= 0 && 0 < imag(b) && sgn(det(a, b)) < 0) {
            in = !in;
        }
        if (sgn(det(a, b)) == 0 && sgn(dot(a, b)) <= 0) return 1;
    }
    return in ? 2 : 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "geometry/polygon.cpp"
// 面積 頂点が反時計回りに並んでいること
R area(const G& pol) {
    R ret = 0.0;
    REP(i, pol.size()) ret += det(pol[i], pol[(i+1)%pol.size()]);
    return (ret/2.0);
}

// 凸性の判定
bool isConvex(const G& pol) {
    REP(i, pol.size()) {
        if(sgn(det(pol[(i+1)%pol.size()]-pol[i], pol[(i+2)%pol.size()]-pol[i])) < 0) {
            return false;
        }
    }
    return true;
}

// 多角形と点の内包
// 2→in 1→on 0→out
int inPolygon(const G& pol, const P& p) {
    bool in = false;
    for (int i = 0; i < pol.size(); ++i) {
        P a = pol[i] - p, b = pol[(i+1)%pol.size()] - p;
        if (imag(a) > imag(b)) swap(a, b);
        if (imag(a) <= 0 && 0 < imag(b) && sgn(det(a, b)) < 0) {
            in = !in;
        }
        if (sgn(det(a, b)) == 0 && sgn(dot(a, b)) <= 0) return 1;
    }
    return in ? 2 : 0;
}
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

