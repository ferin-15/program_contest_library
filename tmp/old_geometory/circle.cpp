#include <bits/stdc++.h>
using namespace std;

// circle
struct C {
	P p; double r;
	C(const P& p, double r) : p(p), r(r) {}
};

int intersectCC(const C& a, const C& b) {
	double dist = sqrt(norm(a.p-b.p)), r1 = a.r + b.r, r2 = abs(a.r - b.r);
	if(r1 < dist) return 4;		//�ڂ��Ȃ�
	if(dist == r1) return 3;	//�O��
	if(r2 < dist && dist < r1) return 2; //������
	if(dist == r2) return 1; //����
	return 0;	//����
}

vector<P> crossPointCL(C c, L l) {
	double d = distanceLP(l, c.p), r = c.r;
	P m = projection(l, c.p);
	P x = sqrt(r*r-d*d)/abs(l[1]-l[0])*(l[1]-l[0]);
	vector<P> ret(2,m);
	ret[0] -= x;
	ret[1] += x;
	sort(ret.begin(), ret.end());	//!!!
	return ret;
}

vector<P> crossPointCC(C a, C b) {
	double d = abs(a.p-b.p);
	double t = (a.r*a.r-b.r*b.r+d*d)/2/d, h = sqrt(a.r*a.r-t*t);
	P m = t/abs(b.p-a.p)*(b.p-a.p)+a.p;
	P n = n_vector(a.p-b.p);
	vector<P> ret(2, m);
	ret[0] -= h*n;
	ret[1] += h*n;
	sort(ret.begin(), ret.end());	//!!!
	return ret;
}

vector<P> tangentLC(P p, C c) {
	C c2 = C((p+c.p)/2.0, abs(p-c.p)/2.0);
	return crossPointCC(c, c2);
}

vector<P> commonTangent(C a, C b) {
	vector<P> ret, cp;
	if(a.r == b.r) {
		P n = n_vector(b.p-a.p);
		ret.push_back(P{a.p+a.r*n});
		ret.push_back(P{a.p-a.r*n});
	}
	P i = (a.p*b.r+b.p*a.r)/(a.r+b.r);
  	if(abs(a.p-b.p) > a.r+b.r){
    	cp = tangentLC(i,a);
    	for(int i = 0; i < 2; ++i) ret.push_back(cp[i]);
    	if(a.r != b.r){
      		P e = (a.p*b.r-b.p*a.r)/(b.r-a.r);
      		cp = tangentLC(e,a);
      		for(int i = 0; i < 2; ++i) ret.push_back(cp[i]);
    	}
  	}else if(abs(a.p-b.p) == a.r+b.r){
    	cp = tangentLC(i,a);
    	ret.push_back(cp[0]);
    	if(a.r != b.r){
    		P e = (a.p*b.r-b.p*a.r)/(b.r-a.r);
      		cp = tangentLC(e,a);
      		for(int i = 0; i < 2; ++i) ret.push_back(cp[i]);
    	}
  	}else if(abs(a.p-b.p) > abs(a.r-b.r)){
    	if(a.r != b.r){
    		P e = (a.p*b.r-b.p*a.r)/(b.r-a.r);
      		cp = tangentLC(e,a);
      		for(int i = 0; i < 2; ++i) ret.push_back(cp[i]);
    	}
  	}else if(abs(a.p-b.p) == abs(a.r-b.r)){
    	P e = (a.p*b.r-b.p*a.r)/(b.r-a.r);
    	cp = tangentLC(e,a);
    	ret.push_back(cp[0]);
  	}
	sort(ret.begin(), ret.end());
  	return ret;
}

/*
3点が与えられたときに円を求める
返り値は{中心のx座標、y座標、半径}
3点が直線上に並んでいるときは{0, 0, -1}を返す
*/
C calcCircle(int x1, int y1, int x2, int y2, int x3, int y3) {
  long ox, oy, a, b, c, d;
  long r1, r2, r3;

  a = x2 - x1; b = y2 - y1; c = x3 - x1; d = y3 - y1;
  int cx, cy, r;
  if ((a && d) || (b && c)) {
    ox = x1 + (d*(a*a + b*b) - b*(c*c + d*d)) / (a*d - b*c) / 2;
    if (b) oy = (a*(x1+x2-ox-ox) + b*(y1+y2)) / b/2;
    else oy = (c*(x1+x3-ox-ox) + d*(y1+y3)) / d/2;
    r1 = sqrt((ox-x1) * (ox-x1) + (oy-y1) * (oy-y1));
    r2 = sqrt((ox-x2) * (ox-x2) + (oy-y2) * (oy-y2));
    r3 = sqrt((ox-x3) * (ox-x3) + (oy-y3) * (oy-y3));
    cx = ox;
    cy = oy;
    r = (r1+r2+r3) / 3;
    return {P{cx, cy}, r};
  }

  return {P{0, 0}, -1};
}

// 2点p1, p2を通り、半径がrの円を2つ返す
vector<C> calcCircle(P p1, P p2, double r) {
	// 存在しない
	if(abs(p1-p2) > 2*r) return {};
	P p3 = {(p1.real()+p2.real())/2, (p1.imag()+p2.imag())/2};
	double l = abs(p1-p3);
	P p1p2 = p2-p1;
	double a = p1p2.real(), b = p1p2.imag();
	double dx = b*sqrt((r*r-l*l)/(a*a+b*b)), dy = a*sqrt((r*r-l*l)/(a*a+b*b));
	return {{{p3.real()+dx, p3.imag()-dy}, r}, {{p3.real()-dx, p3.imag()+dy}, r}};
}

// 点pが円cの内部に存在するかの判定
bool intersectCP(C c, P p) { return abs(p-c.p) <= c.r + EPS; }

int main() {

}
