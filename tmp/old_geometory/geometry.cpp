#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-8;
const double INF = 1e12;
const double PI = atan(1)*4;

//point
typedef complex<double> P;
namespace std {
	bool operator < (const P& a, const P& b) {
		return real(a) != real(b) ? real(a)<real(b) : imag(a)<imag(b);
	}
	bool cmp_y(const P &a, const P &b){
		return imag(a) != imag(b) ? imag(a)<imag(b) : real(a)<real(b);
	}
}
double cross(const P& a, const P& b) {
	return imag(conj(a)*b);
}
double dot(const P& a, const P& b) {
	return real(conj(a)*b);
}

// line
struct L : public vector<P> {
	L(const P& a, const P& b) {
		push_back(a); push_back(b);
	}
};

// polygon
typedef vector<P> G;

// circle
struct C {
	P p; double r;
	C(const P& p, double r) : p(p), r(r) {}
};

int main() {

}
