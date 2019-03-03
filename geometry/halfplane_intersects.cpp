// yosupoさんのhalfplane_intersects
// https://beta.atcoder.jp/contests/ddcc2019-qual/submissions/3646806
#include <bits/stdc++.h>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

using D = double;
const D PI = acos(D(-1)), EPS = 1e-14;

int sgn(D a) { return (a < -EPS) ? -1 : (a > EPS); }
int sgn(D a, D b) { return sgn(a - b); }
// relative sign
// int rsgn(D a, D f) {
//     if (abs(a) <= f*EPS) return 0;
//     return (a < 0) ? -1 : 1;
// }
struct Pt2 {
    D x, y;
    Pt2(D _x = D(), D _y = D()) : x(_x), y(_y) {}
    Pt2 operator+(const Pt2& r) const { return Pt2(x + r.x, y + r.y); }
    Pt2 operator-(const Pt2& r) const { return Pt2(x - r.x, y - r.y); }
    Pt2 operator*(const Pt2& r) const {
        return Pt2(x * r.x - y * r.y, x * r.y + y * r.x);
    }

    Pt2 operator*(const D& r) const { return Pt2(x * r, y * r); }
    Pt2 operator/(const D& r) const { return Pt2(x / r, y / r); }

    Pt2& operator+=(const Pt2& r) { return *this = *this + r; }
    Pt2& operator-=(const Pt2& r) { return *this = *this - r; }
    Pt2& operator*=(const Pt2& r) { return *this = *this * r; }
    Pt2& operator*=(const D& r) { return *this = *this * r; }
    Pt2& operator/=(const D& r) { return *this = *this / r; }

    Pt2 operator-() const { return Pt2(-x, -y); }

    bool operator<(const Pt2& r) const {
        return 2 * sgn(x, r.x) + sgn(y, r.y) < 0;
    }
    bool operator==(const Pt2& r) const { return sgn((*this - r).rabs()) == 0; }
    bool operator!=(const Pt2& r) const { return !(*this == r); }

    D norm() const { return x * x + y * y; }
    D abs() const { return sqrt(norm()); }
    D rabs() const { return max(std::abs(x), std::abs(y)); }  // robust abs
    D arg() const { return atan2(y, x); }

    pair<D, D> to_pair() const { return make_pair(x, y); }
    static Pt2 polar(D le, D th) { return Pt2(le * cos(th), le * sin(th)); }
};
ostream& operator<<(ostream& os, const Pt2& p) {
    return os << "P(" << p.x << ", " << p.y << ")";
}
using P = Pt2;

struct L {
    P s, t;
    L(P _s = P(), P _t = P()) : s(_s), t(_t) {}
    P vec() const { return t - s; }
    D abs() const { return vec().abs(); }
    D arg() const { return vec().arg(); }
};
ostream& operator<<(ostream& os, const L& l) {
    return os << "L(" << l.s << ", " << l.t << ")";
}

D crs(P a, P b) { return a.x * b.y - a.y * b.x; }
D dot(P a, P b) { return a.x * b.x + a.y * b.y; }
// cross(a, b) is too small?
int sgncrs(P a, P b) {
    D cr = crs(a, b);
    if (abs(cr) <= (a.rabs() + b.rabs()) * EPS) return 0;
    return (cr < 0) ? -1 : 1;
}

// -2, -1, 0, 1, 2 : front, clock, on, cclock, back
int ccw(P b, P c) {
    int s = sgncrs(b, c);
    if (s) return s;
    if (!sgn(c.rabs()) || !sgn((c - b).rabs())) return 0;
    if (dot(b, c) < 0) return 2;
    if (dot(-b, c - b) < 0) return -2;
    return 0;
}
int ccw(P a, P b, P c) { return ccw(b - a, c - a); }
int ccw(L l, P p) { return ccw(l.s, l.t, p); }

D deg2rad(D x) { return x / 180 * PI; }
D rad2deg(D x) { return x / PI * 180; }

//角度を[0, 2*PI)に
D radNorP(D x) { return fmod(fmod(x, 2 * PI) + 2 * PI, 2 * PI); }

//角度を[-PI, PI)に
D radNorN(D x) {
    x = radNorP(x);
    if (x >= PI) x -= 2 * PI;
    return x;
}

/**
 * radianで、xが[l, r]に入っているかを判別する
 * 0:OFF
 * 1:IN
 * 2:ON
 */
bool inR(D l, D r, D x) {
    l = radNorP(l);
    r = radNorP(r);
    x = radNorP(x);
    if (!sgn(l, x) || !sgn(r, x)) return 2;
    if (!sgn(l, r)) return 0;
    if (sgn(l, r) == 1) {
        if (sgn(l, x) == 1 && sgn(x, r) == 1) return 1;
    } else {
        if (sgn(x, r) == 1 || sgn(l, x) == 1) return 1;
    }
    return 0;
}
D ssqrt(D d) {
    d = max(D(0), d);
    return sqrt(d);
}

D sacos(D d) {
    d = max(D(-1), d);
    d = min(D(1), d);
    return acos(d);
}

/*
argで2つの点をロバストに比較する, 整数点などで誤差を回避したい時に
arg(-1, 0) = PI, arg(0, 0) = arg(1, 0) = 0として扱う
*/
int argcmp(P l, P r) {
    auto psgn = [&](P p) {
        if (int u = sgn(p.y)) return u;
        if (sgn(p.x) == -1) return 2;
        return 0;
    };
    int lsgn = psgn(l), rsgn = psgn(r);
    if (lsgn < rsgn) return -1;
    if (lsgn > rsgn) return 1;
    return sgncrs(r, l);
}

using Pol = V<P>;

D area2(const Pol& pol) {
    D u = 0;
    if (!pol.size()) return u;
    P a = pol.back();
    for (auto b : pol) u += crs(a, b), a = b;
    return u;
}

V<L> halfplane_intersects(V<L> lines) {
    sort(lines.begin(), lines.end(), [&](const L& a, const L& b) {
        if (int u = argcmp(a.vec(), b.vec())) return u == -1;
        return sgncrs(a.vec(), b.s - a.s) < 0;
    });
    lines.erase(unique(lines.begin(), lines.end(),
                       [&](const L& a, const L& b) {
                           return argcmp(a.vec(), b.vec()) == 0;
                       }),
                lines.end());

    deque<L> st;
    for (auto l : lines) {
        bool err = false;
        auto is_need = [&](L a, L b, L c) {
            D ab_dw = crs(a.vec(), b.vec()), ab_up = crs(a.vec(), a.t - b.s);
            D bc_dw = crs(b.vec(), c.vec()), bc_up = crs(c.t - b.s, c.vec());
            if (ab_dw <= 0 || bc_dw <= 0) return true;
            bool f = bc_up * ab_dw > bc_dw * ab_up;
            if (!f && crs(a.vec(), c.vec()) < 0) err = true;
            return f;
        };
        while (st.size() >= 2 && !is_need(l, st[0], st[1])) st.pop_front();
        while (st.size() >= 2 &&
               !is_need(st[st.size() - 2], st[st.size() - 1], l))
            st.pop_back();
        if (st.size() < 2 || is_need(st.back(), l, st.front())) st.push_back(l);
        if (err) return {};
    }
    if (st.size() == 2 && !sgncrs(st[0].vec(), st[1].vec()) &&
        sgncrs(st[0].vec(), st[1].s - st[0].s) <= 0)
        return {};

    return V<L>(st.begin(), st.end());
}

int crossLL(const L& l, const L& m, P& r) {
    D cr1 = crs(l.vec(), m.vec()), cr2 = crs(l.vec(), l.t - m.s);
    if (sgncrs(l.vec(), m.vec()) == 0) {
        r = l.s;
        if (sgncrs(l.vec(), l.t - m.s)) return 0;
        return -1;
    }
    r = m.s + m.vec() * cr2 / cr1;
    return 1;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    int n;
    cin >> n;
    V<L> lines;
    lines.push_back(L(P(0, 0.5), P(0.5, 0)));
    lines.push_back(L(P(0.5, 0), P(1, 0.5)));
    lines.push_back(L(P(1, 0.5), P(0.5, 1)));
    lines.push_back(L(P(0.5, 1), P(0, 0.5)));

    int cnt = 0;
    D d = 1.0 / n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            V<L> buf = lines;
            buf.push_back(L(P(d*i, d*j), P(d*i+d, d*j)));
            buf.push_back(L(P(d*i+d, d*j), P(d*i+d, d*j+d)));
            buf.push_back(L(P(d*i+d, d*j+d), P(d*i, d*j+d)));
            buf.push_back(L(P(d*i, d*j+d), P(d*i, d*j)));
            auto lx = halfplane_intersects(buf);
//            cerr << i << " " << j << " " << lx.size() << endl;
            if (lx.size() == 0) continue;
            int m = int(lx.size());
            Pol po;
            for (int k = 0; k < m; k++) {
                P pp;
                crossLL(lx[k], lx[(k+1)%m], pp);
                po.push_back(pp);
            }
            if (area2(po)/2 >= d*d-EPS) {
                cnt++;
            }
        }
    }
    cout << cnt << endl;
    return 0;
}
