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


# :warning: geometry/circle.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed7daeb157cd9b31e53896ad3c771a26">geometry</a>
* <a href="{{ site.github.repository_url }}/blob/master/geometry/circle.cpp">View this file on GitHub</a>
    - Last commit date: 2019-07-14 12:12:28+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// 3点が与えられたときに円を求める
// 3点が直線上に並んでいるときは{0, 0, -1}を返す
C calcCircle(R x1, R y1, R x2, R y2, R x3, R y3) {
    R a = x2-x1, b = y2-y1, c = x3-x1, d = y3-y1;
    if ((sgn(a) && sgn(d)) || (sgn(b) && sgn(c))) {
        R ox = x1+(d*(a*a+b*b)-b*(c*c+d*d))/(a*d-b*c)/2, oy;
        if (b) oy = (a*(x1+x2-ox-ox) + b*(y1+y2)) / b/2;
        else oy = (c*(x1+x3-ox-ox) + d*(y1+y3)) / d/2;
        R r1 = sqrt((ox-x1) * (ox-x1) + (oy-y1) * (oy-y1)),
        r2 = sqrt((ox-x2) * (ox-x2) + (oy-y2) * (oy-y2)),
        r3 = sqrt((ox-x3) * (ox-x3) + (oy-y3) * (oy-y3)),
        r = (r1+r2+r3) / 3;
        return {P{ox, oy}, r};
    }
    return {P{0, 0}, -1};
}
// 2点p1, p2を通り、半径がrの円を2つ返す
vector<C> calcCircle(P p1, P p2, R r) {
	if(abs(p1-p2) > 2*r) return {}; // 存在しない
	P p3 = {(p1.real()+p2.real())/2, (p1.imag()+p2.imag())/2};
	R l = abs(p1-p3);
	P p1p2 = p2-p1;
	R a = p1p2.real(), b = p1p2.imag();
	R dx1 = b*sqrt((r*r-l*l)/(a*a+b*b)), dy1 = a*sqrt((r*r-l*l)/(a*a+b*b));
	return {{{p3.real()+dx1, p3.imag()-dy1}, r}, {{p3.real()-dx1, p3.imag()+dy1}, r}};
}

// 交差
int intersect(const C& c, const L& l) {
    R dist = dist(c.c, l);
    if(sgn(c.r-dist) > 0) return 2; // 交差している
    else if(sgn(c.r-dist) == 0) return 1; // 接している
    return 0; // 交差しない
}
int intersect(const C& a, const C& b) {
	R dist = norm(a.c-b.c), r1 = (a.r+b.r)*(a.r+b.r), r2 = (a.r-b.r)*(a.r-b.r);
	if(sgn(r1-dist) < 0)  return 4;	// 円が離れている
	if(sgn(r1-dist) == 0) return 3;	// 外接
	if(sgn(r2-dist) < 0 && sgn(dist-r1) < 0) return 2; // 交差
	if(sgn(dist-r2) == 0) return 1; // 内接
	return 0;	// 内部に含む
}

// 交点 交差の確認を先にすること！！！
vector<P> crosspoint(C c, L l) {
	R d = dist(l, c.c), r = c.r;
	P m = projection(l, c.c);
	P x = sqrt(r*r-d*d)*vec(l)/abs(vec(l));
	vector<P> ret(2,m);
	ret[0] -= x; ret[1] += x;
	if(ret[1] < ret[0]) swap(ret[0], ret[1]);
	return ret;
}
// intersect=2 を確認すること
vector<P> crosspoint(C a, C b) {
    R d = abs(a.c-b.c);
    R t = (a.r*a.r-b.r*b.r+d*d)/2/d, h = sqrt(a.r*a.r-t*t);
    P m = t/abs(b.c-a.c)*(b.c-a.c)+a.c;
    P n(-(a.c-b.c).imag()/abs(a.c-b.c), (a.c-b.c).real()/abs(a.c-b.c));
    vector<P> ret(2, m);
    ret[0] -= h*n; ret[1] += h*n;
    return ret;
}

// 点aを通る接線を返す
// pl = ((a, 接線と円の交点), (a, 接線と円の交点))
pair<L,L> tangent(C c, P a) {
    pair<L,L> pl;
    if(sgn(abs(a-c.c)-c.r) == 0) { // 点aが円周上にあるとき 要verify
        auto normal = [](P a) {
            L vp({a*P(0,1), a*P(0,-1)});
            return vp;
        };
        L l = normal(a-c.c); // 法線ベクトル
        l.first = a; l.second += a;
        pl.first = pl.second = l;
    } else if(sgn(abs(a-c.c)-c.r) > 0) { // 点aが円の外側にあるとき
        R xp = a.real() - c.c.real();
        R yp = a.imag() - c.c.imag();
        R A = sqrt(xp*xp + yp*yp - c.r*c.r);
        R B = xp*xp + yp*yp;
        P p1(c.r*(xp*c.r + yp*A)/B , c.r*(yp*c.r - xp*A)/B);
        P p2(c.r*(xp*c.r - yp*A)/B , c.r*(yp*c.r + xp*A)/B);
        pl = make_pair(L(a, p1+c.c), L(a, p2+c.c));
    } else { // 点 a が円の内側にあるとき
        pl.first = pl.second = L(P(INF,INF), P(INF,INF));
    }
    return pl;
}

// 2つの円の共通接線の計算に使用
// flag=true のとき内接線, falseのとき外接線
L common_tangent(const C& c1, const C& c2, bool flag) {
    R xp = c2.c.real() - c1.c.real();
    R yp = c2.c.imag() - c1.c.imag();
    R r = flag ? c1.r + c2.r : c1.r - c2.r;
    R A = sqrt(xp*xp + yp*yp - r*r);
    R B = xp*xp + yp*yp;
    P p1(c1.r*(xp*r + yp*A)/B, c1.r*(yp*r - xp*A)/B);
    P p2(c1.r*(xp*r - yp*A)/B, c1.r*(yp*r + xp*A)/B);
    p1 += c1.c; p2 += c1.c;
    return L(p1, p2);
}
// 2円の共通接線を返す
// vl = {(c1の接点, c2の接点), …, (c1の接点, c2の接点)}
vector<L> common_tangent(C c1, C c2) {
    vector<L> vl;
    int pos = intersect(c1, c2);
    // 2つの共通内接線を求める
    L pp1 = common_tangent(c1, c2, true);
    L pp2 = common_tangent(c2, c1, true);
    if(pos == 4) { // 2つの円が離れているとき
        vl.push_back(L(pp1.first, pp2.first));
        vl.push_back(L(pp1.second, pp2.second));
    } else if(pos == 3) { // 外接するとき
        vl.push_back(tangent(c1, pp1.first).first);
    }
    // 2つの共通外接線を求める
    pp1 = common_tangent(c1, c2, false);
    pp2 = common_tangent(c2, c1, false);
    if(pos >= 2) { // 2つの円が交わるとき
        vl.push_back(L(pp1.first, pp2.second));
        vl.push_back(L(pp1.second, pp2.first));
    } else if(pos == 1) { // 2つの円が内接するとき
        vl.push_back(tangent(c1, pp1.first).first);
    }
    return vl;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "geometry/circle.cpp"
// 3点が与えられたときに円を求める
// 3点が直線上に並んでいるときは{0, 0, -1}を返す
C calcCircle(R x1, R y1, R x2, R y2, R x3, R y3) {
    R a = x2-x1, b = y2-y1, c = x3-x1, d = y3-y1;
    if ((sgn(a) && sgn(d)) || (sgn(b) && sgn(c))) {
        R ox = x1+(d*(a*a+b*b)-b*(c*c+d*d))/(a*d-b*c)/2, oy;
        if (b) oy = (a*(x1+x2-ox-ox) + b*(y1+y2)) / b/2;
        else oy = (c*(x1+x3-ox-ox) + d*(y1+y3)) / d/2;
        R r1 = sqrt((ox-x1) * (ox-x1) + (oy-y1) * (oy-y1)),
        r2 = sqrt((ox-x2) * (ox-x2) + (oy-y2) * (oy-y2)),
        r3 = sqrt((ox-x3) * (ox-x3) + (oy-y3) * (oy-y3)),
        r = (r1+r2+r3) / 3;
        return {P{ox, oy}, r};
    }
    return {P{0, 0}, -1};
}
// 2点p1, p2を通り、半径がrの円を2つ返す
vector<C> calcCircle(P p1, P p2, R r) {
	if(abs(p1-p2) > 2*r) return {}; // 存在しない
	P p3 = {(p1.real()+p2.real())/2, (p1.imag()+p2.imag())/2};
	R l = abs(p1-p3);
	P p1p2 = p2-p1;
	R a = p1p2.real(), b = p1p2.imag();
	R dx1 = b*sqrt((r*r-l*l)/(a*a+b*b)), dy1 = a*sqrt((r*r-l*l)/(a*a+b*b));
	return {{{p3.real()+dx1, p3.imag()-dy1}, r}, {{p3.real()-dx1, p3.imag()+dy1}, r}};
}

// 交差
int intersect(const C& c, const L& l) {
    R dist = dist(c.c, l);
    if(sgn(c.r-dist) > 0) return 2; // 交差している
    else if(sgn(c.r-dist) == 0) return 1; // 接している
    return 0; // 交差しない
}
int intersect(const C& a, const C& b) {
	R dist = norm(a.c-b.c), r1 = (a.r+b.r)*(a.r+b.r), r2 = (a.r-b.r)*(a.r-b.r);
	if(sgn(r1-dist) < 0)  return 4;	// 円が離れている
	if(sgn(r1-dist) == 0) return 3;	// 外接
	if(sgn(r2-dist) < 0 && sgn(dist-r1) < 0) return 2; // 交差
	if(sgn(dist-r2) == 0) return 1; // 内接
	return 0;	// 内部に含む
}

// 交点 交差の確認を先にすること！！！
vector<P> crosspoint(C c, L l) {
	R d = dist(l, c.c), r = c.r;
	P m = projection(l, c.c);
	P x = sqrt(r*r-d*d)*vec(l)/abs(vec(l));
	vector<P> ret(2,m);
	ret[0] -= x; ret[1] += x;
	if(ret[1] < ret[0]) swap(ret[0], ret[1]);
	return ret;
}
// intersect=2 を確認すること
vector<P> crosspoint(C a, C b) {
    R d = abs(a.c-b.c);
    R t = (a.r*a.r-b.r*b.r+d*d)/2/d, h = sqrt(a.r*a.r-t*t);
    P m = t/abs(b.c-a.c)*(b.c-a.c)+a.c;
    P n(-(a.c-b.c).imag()/abs(a.c-b.c), (a.c-b.c).real()/abs(a.c-b.c));
    vector<P> ret(2, m);
    ret[0] -= h*n; ret[1] += h*n;
    return ret;
}

// 点aを通る接線を返す
// pl = ((a, 接線と円の交点), (a, 接線と円の交点))
pair<L,L> tangent(C c, P a) {
    pair<L,L> pl;
    if(sgn(abs(a-c.c)-c.r) == 0) { // 点aが円周上にあるとき 要verify
        auto normal = [](P a) {
            L vp({a*P(0,1), a*P(0,-1)});
            return vp;
        };
        L l = normal(a-c.c); // 法線ベクトル
        l.first = a; l.second += a;
        pl.first = pl.second = l;
    } else if(sgn(abs(a-c.c)-c.r) > 0) { // 点aが円の外側にあるとき
        R xp = a.real() - c.c.real();
        R yp = a.imag() - c.c.imag();
        R A = sqrt(xp*xp + yp*yp - c.r*c.r);
        R B = xp*xp + yp*yp;
        P p1(c.r*(xp*c.r + yp*A)/B , c.r*(yp*c.r - xp*A)/B);
        P p2(c.r*(xp*c.r - yp*A)/B , c.r*(yp*c.r + xp*A)/B);
        pl = make_pair(L(a, p1+c.c), L(a, p2+c.c));
    } else { // 点 a が円の内側にあるとき
        pl.first = pl.second = L(P(INF,INF), P(INF,INF));
    }
    return pl;
}

// 2つの円の共通接線の計算に使用
// flag=true のとき内接線, falseのとき外接線
L common_tangent(const C& c1, const C& c2, bool flag) {
    R xp = c2.c.real() - c1.c.real();
    R yp = c2.c.imag() - c1.c.imag();
    R r = flag ? c1.r + c2.r : c1.r - c2.r;
    R A = sqrt(xp*xp + yp*yp - r*r);
    R B = xp*xp + yp*yp;
    P p1(c1.r*(xp*r + yp*A)/B, c1.r*(yp*r - xp*A)/B);
    P p2(c1.r*(xp*r - yp*A)/B, c1.r*(yp*r + xp*A)/B);
    p1 += c1.c; p2 += c1.c;
    return L(p1, p2);
}
// 2円の共通接線を返す
// vl = {(c1の接点, c2の接点), …, (c1の接点, c2の接点)}
vector<L> common_tangent(C c1, C c2) {
    vector<L> vl;
    int pos = intersect(c1, c2);
    // 2つの共通内接線を求める
    L pp1 = common_tangent(c1, c2, true);
    L pp2 = common_tangent(c2, c1, true);
    if(pos == 4) { // 2つの円が離れているとき
        vl.push_back(L(pp1.first, pp2.first));
        vl.push_back(L(pp1.second, pp2.second));
    } else if(pos == 3) { // 外接するとき
        vl.push_back(tangent(c1, pp1.first).first);
    }
    // 2つの共通外接線を求める
    pp1 = common_tangent(c1, c2, false);
    pp2 = common_tangent(c2, c1, false);
    if(pos >= 2) { // 2つの円が交わるとき
        vl.push_back(L(pp1.first, pp2.second));
        vl.push_back(L(pp1.second, pp2.first));
    } else if(pos == 1) { // 2つの円が内接するとき
        vl.push_back(tangent(c1, pp1.first).first);
    }
    return vl;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

