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

const R EPS = 1e-8;
const R PI = atan(1)*4;

inline int sgn(const R& r) { return (r>EPS) - (r<-EPS); }
inline R dot(const P& a, const P& b) {
    return real(a)*real(b) + imag(a)*imag(b);
}
inline R det(const P& a, const P& b) {
    return real(a)*imag(b) - imag(a)*real(b);
}
inline P rotate(const P& p, const R& arg) {
    return P(cos(arg)*p.real()-sin(arg)*p.imag(),
             sin(arg)*p.real()+cos(arg)*p.imag());
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
