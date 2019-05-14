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