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


# :warning: geometry/z_geometry_matome.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed7daeb157cd9b31e53896ad3c771a26">geometry</a>
* <a href="{{ site.github.repository_url }}/blob/master/geometry/z_geometry_matome.cpp">View this file on GitHub</a>
    - Last commit date: 2019-05-14 17:50:56+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
const double EPS = 1e-8;

using R = long double; // Rにmint渡せるようにする
using P = complex<R>;
using L = pair<P,P>;
using G = vector<P>;
struct C {
    P c; R r;
    C() {}
    C(const P &a, const R &b) : c(a), r(b) {}
};
struct S : public L {
    S() {}
    S(const P &a, const P &b) : L(a,b) {}
};

inline int sgn(const R& r) { return (r>EPS) - (r<-EPS); }
inline R dot(const P& a, const P& b) {
    return real(a)*real(b) + imag(a)*imag(b);
}
inline R det(const P& a, const P& b) {
    return real(a)*imag(b) - imag(a)*real(b);
}
inline P vec(const L& l) {return l.second - l.first;}
namespace std {
	bool operator < (const P& a, const P& b) {
		return sgn(real(a-b)) ? real(a-b) < 0 : sgn(imag(a-b)) < 0;
	}
	bool operator == (const P& a, const P& b) {
		return sgn(real(a-b)) == 0 && sgn(imag(a-b)) == 0;
	}
    bool cmp_y (const P& a, const P& b) {
        return sgn(imag(a-b)) ? imag(a-b) < 0 : sgn(real(a-b)) < 0;
    }
}

// P,L,Sについて入力
inline istream& operator>>(istream& is, P& p) {
    R x, y;
    is >> x >> y;
    p = P(x, y);
    return is;
}
inline istream& operator>>(istream& is, L& l) {
    P a, b;
    is >> a >> b;
    l = L(a, b);
    return is;
}
inline istream& operator>>(istream& is, S& s) {
    P a, b;
    is >> a >> b;
    s = S(a, b);
    return is;
}

// 線分abから見たcの位置
enum CCW{LEFT=1, RIGHT=2, BACK=4, FRONT=8, ON_SEG=16};
int ccw(P a, P b, P c) {
	P p = (c-a)/(b-a);
	if(sgn(imag(p)) > 0) return LEFT;
	if(sgn(imag(p)) < 0) return RIGHT;
	if(sgn(real(p)) < 0) return BACK;
	if(sgn(real(p)-1) > 0) return FRONT;
	return ON_SEG;
}

// ------- 線分・直線 -------
// 射影
P inline projection(const L &l, const P &p) {
    R t = dot(p-l.first, l.first-l.second) / norm(l.first-l.second);
    return l.first + t*(l.first-l.second);
}
// 反射
P inline reflection(const L &l, const P &p) {
    return p + (R)2 * (projection(l, p) - p);
}

// 垂直,平行
inline bool vertical(L a, L b) {return sgn(dot(vec(a), vec(b))) == 0;}
inline bool parallel(L a, L b) {return sgn(det(vec(a), vec(b))) == 0;}

// 交差判定
template<bool strict=false> inline bool intersect(const L&l1, const L&l2) {
    if(strict) return sgn(det(vec(l1),vec(l2))) != 0;
    return sgn(det(vec(l1),vec(l2))) != 0 || l1 == l2;
}
template<bool strict=false> inline bool intersect(const L&l, const S&s) {
    if(strict) det(s.first, vec(l)) * det(s.second, vec(l)) < 0;
    return det(s.first, vec(l)) * det(s.second, vec(l)) <= 0;
}
template<bool strict=false> inline bool intersect(const S&s1, const S&s2) {
    int ccw1 = ccw(s1.first, s1.second, s2.first) | ccw(s1.first, s1.second, s2.second);
    int ccw2 = ccw(s2.first, s2.second, s1.first) | ccw(s2.first, s2.second, s1.second);
    if(strict) return (ccw1 & ccw2) == (LEFT | RIGHT);
    return (ccw1 & ccw2) == (LEFT | RIGHT) || ((ccw1 | ccw2) & ON_SEG);
}
template<bool strict=false> inline bool intersect(const S&s, const P&p) {
    return ccw(s.first, s.second, p) == ON_SEG;
}
template<bool strict=false> inline bool intersect(const L&l, const P&p) {
    return ccw(l.first, l.second, p) == ON_SEG ||
            ccw(l.first, l.second, p) == FRONT ||
            ccw(l.first, l.second, p) == BACK;
}

// 距離
R dist(const S& s, const P& p) {
    P q = projection(s, p);
    if(sgn(dot(s.second-s.first, p-s.first)) <= 0) q = s.first;
    if(sgn(dot(s.first-s.second, p-s.second)) <= 0) q = s.second;
    return abs(p-q);
}
R dist(const S& a, const S& b) {
    if(intersect(a, b)) return 0;
    return min({dist(a, b.first), dist(a, b.second), dist(b, a.first), dist(b, a.second)});
}
R dist(const L& l, const P& p) {
    P q = projection(l, p);
    return abs(p-q);
}

// 交点 交差判定を先にすること!!!
inline P crosspoint(const L& l1, const L& l2) {
    R ratio = det(vec(l2), l2.first-l1.first)/det(vec(l2),vec(l1));
    return l1.first + vec(l1)*ratio;
}

// ------- 多角形 -------
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
        if (da >= 0) res.emplace_back(a);
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

// ------- 円 -------
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
    R dist = dist(c.p, l);
    if(sgn(r-dist) < 0) return 2; // 交差している
    else if(sgn(r-dist) == 0) return 1; // 接している
    return 0; // 交差しない
}
int intersect(const C& a, const C& b) {
	R dist = sqrt(norm(a.c-b.c)), r1 = a.r + b.r, r2 = abs(a.r - b.r);
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
vector<P> crosspoint(C a, C b) {
	R d = abs(a.c-b.c);
	R t = (a.r*a.r-b.r*b.r+d*d)/2/d, h = sqrt(a.r*a.r-t*t);
	P m = t/abs(b.c-a.c)*(b.c-a.c)+a.c;
    auto n_vector = [&](P p) -> P { return P(-p.imag(), p.real())/abs(p); };
	P n = n_vector(a.c-b.c);
	vector<P> ret(2, m);
	ret[0] -= h*n; ret[1] += h*n;
	if(ret[1] < ret[0]) swap(ret[0], ret[1]);
	return ret;
}

// 点aを通る接線を返す
pair<L,L> tangent(C c, P a) {
    pair<L,L> pl;
    if(sgn(abs(a-c.p), c.r) == 0) { // 点 a が円周上にあるとき
        L l(normal(a-c.p)); // 法線ベクトル
        l[0] += a; l[1] += a;
        pl.first = pl.second = l;
    } else if(sgn(abs(a-c.p), c.r) < 0) { // 点 a が円の外側にあるとき
        double xp = a.real() - p.real();
        double yp = a.imag() - p.imag();
        double A = sqrt(xp*xp + yp*yp - r*r);
        double B = xp*xp + yp*yp;
        P p1(r*(xp*r + yp*A)/B , r*(yp*r - xp*A)/B);
        P p2(r*(xp*r - yp*A)/B , r*(yp*r + xp*A)/B);
        pl = make_pair(L(a ,p1+p), L(a ,p2+p));
    } else { // 点 a が円の内側にあるとき
        pl.first = pl.second = L(P(INF,INF), P(INF,INF));
    }
    return pl;
}

// 2つの円の共通接線の計算に使用
// flag=true のとき内接線, falseのとき外接線
L common_tangent(const C& c1, const C& c2, bool flag) {
    double xp = c1.p.real() - c2.p.real();
    double yp = c1.p.imag() - c2.p.imag();
    double R = (flag)? r + c.r : r - c.r ;
    double A = sqrt(xp*xp + yp*yp - R*R);
    double B = xp*xp + yp*yp;
    P p1(r*(xp*R + yp*A)/B, r*(yp*R - xp*A)/B);
    P p2(r*(xp*R - yp*A)/B, r*(yp*R + xp*A)/B);
    p1 += p; p2 += p;
    return L(p1,p 2);
}
// 2円の共通接線を返す
vector<L> common_tangent(C c1, C c2) {
    vector<L> vl;
    int pos = intersect(c1, c2);
    // 2つの共通内接線を求める
    L pp1 = common_tangent(c1, c2, true);
    L pp2 = common_tangent(c2, c1, true);
    if( pos == 4 ) { // 2つの円が離れているとき
        vl.push_back(L(pp1.first, pp2.first));
        vl.push_back(L(pp1.second, pp2.second));
    } else if( pos == 3 ) { // 外接するとき
        vl.push_back(tangent(c1, pp1.first).first);
    }
    // 2つの共通外接線を求める
    pp1 = common_tangent1(c1, c2, false);
    pp2 = common_tangent1(c2, c1, false);
    if(pos <= 2) { // 2つの円が交わるとき
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
#line 1 "geometry/z_geometry_matome.cpp"
const double EPS = 1e-8;

using R = long double; // Rにmint渡せるようにする
using P = complex<R>;
using L = pair<P,P>;
using G = vector<P>;
struct C {
    P c; R r;
    C() {}
    C(const P &a, const R &b) : c(a), r(b) {}
};
struct S : public L {
    S() {}
    S(const P &a, const P &b) : L(a,b) {}
};

inline int sgn(const R& r) { return (r>EPS) - (r<-EPS); }
inline R dot(const P& a, const P& b) {
    return real(a)*real(b) + imag(a)*imag(b);
}
inline R det(const P& a, const P& b) {
    return real(a)*imag(b) - imag(a)*real(b);
}
inline P vec(const L& l) {return l.second - l.first;}
namespace std {
	bool operator < (const P& a, const P& b) {
		return sgn(real(a-b)) ? real(a-b) < 0 : sgn(imag(a-b)) < 0;
	}
	bool operator == (const P& a, const P& b) {
		return sgn(real(a-b)) == 0 && sgn(imag(a-b)) == 0;
	}
    bool cmp_y (const P& a, const P& b) {
        return sgn(imag(a-b)) ? imag(a-b) < 0 : sgn(real(a-b)) < 0;
    }
}

// P,L,Sについて入力
inline istream& operator>>(istream& is, P& p) {
    R x, y;
    is >> x >> y;
    p = P(x, y);
    return is;
}
inline istream& operator>>(istream& is, L& l) {
    P a, b;
    is >> a >> b;
    l = L(a, b);
    return is;
}
inline istream& operator>>(istream& is, S& s) {
    P a, b;
    is >> a >> b;
    s = S(a, b);
    return is;
}

// 線分abから見たcの位置
enum CCW{LEFT=1, RIGHT=2, BACK=4, FRONT=8, ON_SEG=16};
int ccw(P a, P b, P c) {
	P p = (c-a)/(b-a);
	if(sgn(imag(p)) > 0) return LEFT;
	if(sgn(imag(p)) < 0) return RIGHT;
	if(sgn(real(p)) < 0) return BACK;
	if(sgn(real(p)-1) > 0) return FRONT;
	return ON_SEG;
}

// ------- 線分・直線 -------
// 射影
P inline projection(const L &l, const P &p) {
    R t = dot(p-l.first, l.first-l.second) / norm(l.first-l.second);
    return l.first + t*(l.first-l.second);
}
// 反射
P inline reflection(const L &l, const P &p) {
    return p + (R)2 * (projection(l, p) - p);
}

// 垂直,平行
inline bool vertical(L a, L b) {return sgn(dot(vec(a), vec(b))) == 0;}
inline bool parallel(L a, L b) {return sgn(det(vec(a), vec(b))) == 0;}

// 交差判定
template<bool strict=false> inline bool intersect(const L&l1, const L&l2) {
    if(strict) return sgn(det(vec(l1),vec(l2))) != 0;
    return sgn(det(vec(l1),vec(l2))) != 0 || l1 == l2;
}
template<bool strict=false> inline bool intersect(const L&l, const S&s) {
    if(strict) det(s.first, vec(l)) * det(s.second, vec(l)) < 0;
    return det(s.first, vec(l)) * det(s.second, vec(l)) <= 0;
}
template<bool strict=false> inline bool intersect(const S&s1, const S&s2) {
    int ccw1 = ccw(s1.first, s1.second, s2.first) | ccw(s1.first, s1.second, s2.second);
    int ccw2 = ccw(s2.first, s2.second, s1.first) | ccw(s2.first, s2.second, s1.second);
    if(strict) return (ccw1 & ccw2) == (LEFT | RIGHT);
    return (ccw1 & ccw2) == (LEFT | RIGHT) || ((ccw1 | ccw2) & ON_SEG);
}
template<bool strict=false> inline bool intersect(const S&s, const P&p) {
    return ccw(s.first, s.second, p) == ON_SEG;
}
template<bool strict=false> inline bool intersect(const L&l, const P&p) {
    return ccw(l.first, l.second, p) == ON_SEG ||
            ccw(l.first, l.second, p) == FRONT ||
            ccw(l.first, l.second, p) == BACK;
}

// 距離
R dist(const S& s, const P& p) {
    P q = projection(s, p);
    if(sgn(dot(s.second-s.first, p-s.first)) <= 0) q = s.first;
    if(sgn(dot(s.first-s.second, p-s.second)) <= 0) q = s.second;
    return abs(p-q);
}
R dist(const S& a, const S& b) {
    if(intersect(a, b)) return 0;
    return min({dist(a, b.first), dist(a, b.second), dist(b, a.first), dist(b, a.second)});
}
R dist(const L& l, const P& p) {
    P q = projection(l, p);
    return abs(p-q);
}

// 交点 交差判定を先にすること!!!
inline P crosspoint(const L& l1, const L& l2) {
    R ratio = det(vec(l2), l2.first-l1.first)/det(vec(l2),vec(l1));
    return l1.first + vec(l1)*ratio;
}

// ------- 多角形 -------
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
        if (da >= 0) res.emplace_back(a);
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

// ------- 円 -------
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
    R dist = dist(c.p, l);
    if(sgn(r-dist) < 0) return 2; // 交差している
    else if(sgn(r-dist) == 0) return 1; // 接している
    return 0; // 交差しない
}
int intersect(const C& a, const C& b) {
	R dist = sqrt(norm(a.c-b.c)), r1 = a.r + b.r, r2 = abs(a.r - b.r);
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
vector<P> crosspoint(C a, C b) {
	R d = abs(a.c-b.c);
	R t = (a.r*a.r-b.r*b.r+d*d)/2/d, h = sqrt(a.r*a.r-t*t);
	P m = t/abs(b.c-a.c)*(b.c-a.c)+a.c;
    auto n_vector = [&](P p) -> P { return P(-p.imag(), p.real())/abs(p); };
	P n = n_vector(a.c-b.c);
	vector<P> ret(2, m);
	ret[0] -= h*n; ret[1] += h*n;
	if(ret[1] < ret[0]) swap(ret[0], ret[1]);
	return ret;
}

// 点aを通る接線を返す
pair<L,L> tangent(C c, P a) {
    pair<L,L> pl;
    if(sgn(abs(a-c.p), c.r) == 0) { // 点 a が円周上にあるとき
        L l(normal(a-c.p)); // 法線ベクトル
        l[0] += a; l[1] += a;
        pl.first = pl.second = l;
    } else if(sgn(abs(a-c.p), c.r) < 0) { // 点 a が円の外側にあるとき
        double xp = a.real() - p.real();
        double yp = a.imag() - p.imag();
        double A = sqrt(xp*xp + yp*yp - r*r);
        double B = xp*xp + yp*yp;
        P p1(r*(xp*r + yp*A)/B , r*(yp*r - xp*A)/B);
        P p2(r*(xp*r - yp*A)/B , r*(yp*r + xp*A)/B);
        pl = make_pair(L(a ,p1+p), L(a ,p2+p));
    } else { // 点 a が円の内側にあるとき
        pl.first = pl.second = L(P(INF,INF), P(INF,INF));
    }
    return pl;
}

// 2つの円の共通接線の計算に使用
// flag=true のとき内接線, falseのとき外接線
L common_tangent(const C& c1, const C& c2, bool flag) {
    double xp = c1.p.real() - c2.p.real();
    double yp = c1.p.imag() - c2.p.imag();
    double R = (flag)? r + c.r : r - c.r ;
    double A = sqrt(xp*xp + yp*yp - R*R);
    double B = xp*xp + yp*yp;
    P p1(r*(xp*R + yp*A)/B, r*(yp*R - xp*A)/B);
    P p2(r*(xp*R - yp*A)/B, r*(yp*R + xp*A)/B);
    p1 += p; p2 += p;
    return L(p1,p 2);
}
// 2円の共通接線を返す
vector<L> common_tangent(C c1, C c2) {
    vector<L> vl;
    int pos = intersect(c1, c2);
    // 2つの共通内接線を求める
    L pp1 = common_tangent(c1, c2, true);
    L pp2 = common_tangent(c2, c1, true);
    if( pos == 4 ) { // 2つの円が離れているとき
        vl.push_back(L(pp1.first, pp2.first));
        vl.push_back(L(pp1.second, pp2.second));
    } else if( pos == 3 ) { // 外接するとき
        vl.push_back(tangent(c1, pp1.first).first);
    }
    // 2つの共通外接線を求める
    pp1 = common_tangent1(c1, c2, false);
    pp2 = common_tangent1(c2, c1, false);
    if(pos <= 2) { // 2つの円が交わるとき
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

