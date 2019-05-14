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