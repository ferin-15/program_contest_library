#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-8;
const double INF = 1e12;

using R = long double;
using P = complex<R>;
using L = pair<P,P>;
using S = pair<P,P>;

inline int sgn(const R& r) { return (r>EPS) - (r<-EPS); }
namespace std {
	bool operator < (const P& a, const P& b) {
		return sgn(real(a-b)) ? real(a-b) < 0 : sgn(imag(a-b)) < 0;
	}
	bool operator == (const P& a, const P& b) {
		return sgn(real(a-b)) == 0 && sgn(imag(a-b)) == 0;
	}
}
inline R det(const P& a, const P& b) { return real(a)*real(b) + imag(a)*imag(b); }
inline R dot(const P& a, const P& b) { return real(a)*imag(b)-imag(a)*real(b); }
inline P div(const P &a, const P &b) { return {dot(a,b)/norm(a), det(a,b)/norm(a)}; }

enum CCW{LEFT=1, RIGHT=2, BACK=4, FRONT=8, ON=16};
int ccw(P a, P b, P c) {
	P p = div(c-a, b-a);
	if(imag(p) > 0) return LEFT;
	if(imag(p) < 0) return RIGHT;
	if(real(p) < 0) return BACK;
	if(real(p) < 1) return FRONT;
	return ON;
}

// // Lが直線でSが線分、Pが点
// bool intersect(const L &l, const L &m) {
//   return abs(det(l.second-l.first, m.second-m.first)) > EPS || // non-parallel
//          abs(det(l[1]-l.first, m.first-l.first)) < EPS;   // same line
// }
// bool intersect(const L &l, const L &s) {
//   return det(l[1]-l.first, s[0]-l[0])*       // s[0] is left of l
//          det(l[1]-l.first, s[1]-l[0]) < EPS; // s[1] is right of l
// }
// bool intersect(const L &l, const P &p) {
//   return abs(det(l[1]-p, l[0]-p)) < EPS;
// }
// bool intersect(const L &s, const L &t) {
//   return ccw(s[0],s[1],t[0])*ccw(s[0],s[1],t[1]) <= 0 &&
//          ccw(t[0],t[1],s[0])*ccw(t[0],t[1],s[1]) <= 0;
// }
// bool intersect(const L &s, const P &p) {
//   return abs(s[0]-p)+abs(s[1]-p)-abs(s[1]-s[0]) < EPS; // triangle inequality
// }
//
// // 射影
// P projection(const L &l, const P &p) {
// 	R t = dot(p-l.first, l.first-l.second) / norm(l.first-l.second);
// 	return l.first + t*(l.first-l.second);
// }
// // 反射
// P reflection(const L &l, const P &p) {
// 	return p + (R)2 * (projection(l, p) - p);
// }
// double distanceLP(const L &l, const P &p) {
// 	return abs(p - projection(l, p));
// }
// double distanceLL(const L &l, const L &m) {
// 	return intersect(l, m) ? 0 : distance(l, m[0]);
// }
// double distanceLS(const L &l, const L &s) {
// 	if (intersect(l, s)) return 0;
// 	return min(distance(l, s[0]), distance(l, s[1]));
// }
// double distanceSP(const L &s, const P &p) {
// 	const P r = projection(s, p);
// 	if (intersect(s, r)) return abs(r - p);
// 	return min(abs(s[0] - p), abs(s[1] - p));
// }
// double distanceSS(const L &s, const L &t) {
// 	if (intersect(s, t)) return 0;
// 		return min({distanceSP(s, t[0]), distanceSP(s, t[1]), distanceSP(t, s[0]), distanceSP(t, s[1])});
// }
// P crosspoint(const L &l, const L &m) {
//   double A = cross(l[1] - l[0], m[1] - m[0]);
//   double B = cross(l[1] - l[0], l[1] - m[0]);
//   if (abs(A) < EPS && abs(B) < EPS) return m[0]; // same line
//   if (abs(A) < EPS) assert(false); // !!!PRECONDITION NOT SATISFIED!!!
//   return m[0] + B / A * (m[1] - m[0]);
// }

int main() {
	
	return 0;
}
