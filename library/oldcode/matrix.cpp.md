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


# :warning: oldcode/matrix.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#bf50ccff88ac9b2562bee63cf804278c">oldcode</a>
* <a href="{{ site.github.repository_url }}/blob/master/oldcode/matrix.cpp">View this file on GitHub</a>
    - Last commit date: 2019-10-03 22:20:29+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// 実数体じゃなくて有限体なら四則演算を切り替える
const double EPS = 1e-8;
using mat = vector<vector<double>>;
mat gauss_jordan(mat a) {
    const int h = a.size(), w = a[0].size();
    REP(i, min(w, h)) {
        int pivot = i;
        REP(j, h) if(abs(a[j][i]) > abs(a[pivot][i])) pivot = j;
        swap(a[i], a[pivot]);
        if(abs(a[i][i]) < EPS) continue;
        FOR(j, i+1, w) a[i][j] /= a[i][i];
        REP(j, h) {
            if(i == j) continue;
            FOR(k, i+1, w) a[j][k] -= a[j][i] * a[i][k];
        }
    }
    return a;
}

double determinant(mat a) {
    const int h = a.size(), w = a[0].size();
    assert(h==w);
    REP(i, h) if(abs(a[i][i]) < EPS) return 0;
    REP(i, h) FOR(j, i+1, h) FOR(k, i, w) {
        a[j][k] -= a[j][i] * a[i][k] / a[i][i];            
    }
    double ret = 1;
    REP(i, h) ret *= a[i][i];
    return ret;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "oldcode/matrix.cpp"
// 実数体じゃなくて有限体なら四則演算を切り替える
const double EPS = 1e-8;
using mat = vector<vector<double>>;
mat gauss_jordan(mat a) {
    const int h = a.size(), w = a[0].size();
    REP(i, min(w, h)) {
        int pivot = i;
        REP(j, h) if(abs(a[j][i]) > abs(a[pivot][i])) pivot = j;
        swap(a[i], a[pivot]);
        if(abs(a[i][i]) < EPS) continue;
        FOR(j, i+1, w) a[i][j] /= a[i][i];
        REP(j, h) {
            if(i == j) continue;
            FOR(k, i+1, w) a[j][k] -= a[j][i] * a[i][k];
        }
    }
    return a;
}

double determinant(mat a) {
    const int h = a.size(), w = a[0].size();
    assert(h==w);
    REP(i, h) if(abs(a[i][i]) < EPS) return 0;
    REP(i, h) FOR(j, i+1, h) FOR(k, i, w) {
        a[j][k] -= a[j][i] * a[i][k] / a[i][i];            
    }
    double ret = 1;
    REP(i, h) ret *= a[i][i];
    return ret;
}
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

