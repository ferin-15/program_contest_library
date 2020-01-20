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


# :warning: geometry/convex_polygon.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed7daeb157cd9b31e53896ad3c771a26">geometry</a>
* <a href="{{ site.github.repository_url }}/blob/master/geometry/convex_polygon.cpp">View this file on GitHub</a>
    - Last commit date: 2019-07-14 12:12:28+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// 凸包 3点が一直線上に並ぶときに注意
// 凸包のうち一番左にある頂点の中で一番下の頂点から時計回り
G convex_hull(G ps) {
    int n = ps.size(), k = 0;
    sort(ps.begin(), ps.end());
    G r(2*n);
    for(int i=0; i<n; i++){
        while(k>1 && sgn(det(r[k-1]-r[k-2], ps[i]-r[k-2])) < 0) k--;
        r[k++] = ps[i];
    }
    for(int i=n-2,t=k; i>=0; i--){
        while(k>t && sgn(det(r[k-1]-r[k-2], ps[i]-r[k-2])) < 0) k--;
        r[k++] = ps[i];
    }
    r.resize(k-1);
    return r;
}
// 凸多角形polを直線lで切断して左側の多角形を返す
G convex_cut(const G& pol, const L& l) {
    G res;
    REP(i, pol.size()) {
        P a = pol[i], b = pol[(i + 1)%pol.size()];
        int da = sgn(det(l.first-a, l.second-a)), db = sgn(det(l.first-b, l.second-b));
        // 点aが直線lの左側
        if (da >= 0) res.emplace_back(a);
        // 辺(a,b)と直線lが交わる
        if (da * db < 0) res.emplace_back(crosspoint(L{a, b}, l));
    }
    return res;
}

// 1直線上に3点が並んでるような部分を消去 O(p.size())
G normalize_poligon(G p) {
    int n = p.size();
    REP(i, p.size()) {
        if(ccw(p[(i+n-1)%n], p[i], p[(i+1)%n]) == ON_SEG) {
            p.erase(p.begin() + i);
            i--;
        }
    }
    return p;
}
// 点a,bの垂直二等分線 O(1)
L bisector(P a, P b) {
    const P mid = (a + b) / P(2, 0);
    return L{mid, mid + (b - a)*P(0, 1)};
}
// 多角形polと点集合vについてボロノイ図を計算
// 点v[s]が属する部分を返す O(pol.size * v.size())
G voronoi_cell(G pol, G v, int s) {
    pol = normalize_poligon(pol);
    REP(i, v.size()) if(i != s) {
        pol = convex_cut(pol, bisector(v[s], v[i]));
    }
    return pol;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "geometry/convex_polygon.cpp"
// 凸包 3点が一直線上に並ぶときに注意
// 凸包のうち一番左にある頂点の中で一番下の頂点から時計回り
G convex_hull(G ps) {
    int n = ps.size(), k = 0;
    sort(ps.begin(), ps.end());
    G r(2*n);
    for(int i=0; i<n; i++){
        while(k>1 && sgn(det(r[k-1]-r[k-2], ps[i]-r[k-2])) < 0) k--;
        r[k++] = ps[i];
    }
    for(int i=n-2,t=k; i>=0; i--){
        while(k>t && sgn(det(r[k-1]-r[k-2], ps[i]-r[k-2])) < 0) k--;
        r[k++] = ps[i];
    }
    r.resize(k-1);
    return r;
}
// 凸多角形polを直線lで切断して左側の多角形を返す
G convex_cut(const G& pol, const L& l) {
    G res;
    REP(i, pol.size()) {
        P a = pol[i], b = pol[(i + 1)%pol.size()];
        int da = sgn(det(l.first-a, l.second-a)), db = sgn(det(l.first-b, l.second-b));
        // 点aが直線lの左側
        if (da >= 0) res.emplace_back(a);
        // 辺(a,b)と直線lが交わる
        if (da * db < 0) res.emplace_back(crosspoint(L{a, b}, l));
    }
    return res;
}

// 1直線上に3点が並んでるような部分を消去 O(p.size())
G normalize_poligon(G p) {
    int n = p.size();
    REP(i, p.size()) {
        if(ccw(p[(i+n-1)%n], p[i], p[(i+1)%n]) == ON_SEG) {
            p.erase(p.begin() + i);
            i--;
        }
    }
    return p;
}
// 点a,bの垂直二等分線 O(1)
L bisector(P a, P b) {
    const P mid = (a + b) / P(2, 0);
    return L{mid, mid + (b - a)*P(0, 1)};
}
// 多角形polと点集合vについてボロノイ図を計算
// 点v[s]が属する部分を返す O(pol.size * v.size())
G voronoi_cell(G pol, G v, int s) {
    pol = normalize_poligon(pol);
    REP(i, v.size()) if(i != s) {
        pol = convex_cut(pol, bisector(v[s], v[i]));
    }
    return pol;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

