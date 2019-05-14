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