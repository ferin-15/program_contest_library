#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-8;
const double INF = 1e12;

// polygon
typedef vector<P> G;

P extreme(const vector<P> &po, const L &l) {
  int k = 0;
  for (int i = 1; i < po.size(); ++i)
    if (dot(po[i], l[1]-l[0]) > dot(po[k], l[1]-l[0])) k = i;
  return po[k];
}

enum { OUT, ON, IN };
int contains(const G& po, const P& p) {
  bool in = false;
  for (int i = 0; i < po.size(); ++i) {
  	P a = po[i] - p, b = po[(i+1)%po.size()] - p;
    if (imag(a) > imag(b)) swap(a, b);
    if (imag(a) <= 0 && 0 < imag(b))
      if (cross(a, b) < 0) in = !in;
    if (cross(a, b) == 0 && dot(a, b) <= 0) return ON;
  }
  return in ? IN : OUT;
}

double area2(const G& po) {
	double A = 0;
  for (int i = 0; i < po.size(); ++i)
  	A += cross(po[i], po[(i+1)%po.size()]);
  return A/2;
}

bool isconvex(const G &p) {
	int n = p.size();
	if(cross(p[0]-p[n-1],p[n-2]-p[n-1]) < 0) return false;
	for(int i = 1; i < n-1; ++i) {
		if(cross(p[i+1]-p[i],p[i-1]-p[i]) < 0) return false;
	}
	return true;
}

G convex_hull(G ps) {
  int n = ps.size(), k = 0;
  sort(ps.begin(), ps.end());
  G r(2*n);
  for(int i = 0; i < n; i++){
    while(k>1 && cross(r[k-1]-r[k-2],ps[i]-r[k-2]) < -EPS)k--;
    r[k++] = ps[i];
  }
  for(int i = n-2, t = k; i >= 0; i--){
    while(k>t && cross(r[k-1]-r[k-2],ps[i]-r[k-2]) < -EPS)k--;
    r[k++] = ps[i];
  }
  r.resize(k-1);
  return r;
}

// caliper
double convex_diameter(const G &pt) {
	const int n = pt.size();
	if(n <= 1) return 0;
	if(n == 2) return abs(pt[0]-pt[1]);

	int i = 0, j = 0;
	for(int k = 0; k < n; ++k){
		if(!(pt[i] < pt[k])) i = k;
		if(pt[j] < pt[k]) j = k;
	}

	double res = 0;
	int si = i, sj = j;
	while(i != sj || j != si) {
		res = max(res, abs(pt[i]-pt[j]));
		if(cross(pt[(i+1)%n]-pt[i],pt[(j+1)%n]-pt[j]) < 0) i = (i+1)%n;
		else j = (j+1)%n;
	}
	return res;
}

// po��l�Őؒf���č����݂̂��Ԃ�
G convex_cut(const G& po, const L& l) {
  G Q;
  for (int i = 0; i < po.size(); ++i) {
  	P A = po[i], B = po[(i+1)%po.size()];
    if (ccw(l[0], l[1], A) != -1) Q.push_back(A);
  	if (ccw(l[0], l[1], A)*ccw(l[0], l[1], B) < 0) {
  		Q.push_back(crosspoint(L(A, B), l));
  	}
  }
  return Q;
}

//�ŋߓ_�΋���
double closestPair(G p, int flag=1) {
	if(flag) sort(p.begin(), p.end());
	int n = p.size(), s = 0, m=n/2;
	if(n<=1) return INF;
	G b(begin(p), begin(p)+m), c(begin(p)+m, end(p)), e;
	double x = p[m].real(), d=min(closestPair(b, 0), closestPair(c, 0));
	sort(p.begin(), p.end(), cmp_y);
	for(int i=0; i<n; ++i) {
		if(abs(real(p[i])-x) >= d) continue;
		for(int j=0; j<e.size(); ++j) {
			if(imag(p[i]-e[e.size()-1-j]) >= d) break;
			d = min(d, abs(p[i]-e[e.size()-1-j]));
		}
		e.push_back(p[i]);
	}
	return d;
}

int main() {
}
