// ToDo: verify
// 実数体
using vec = vector<double>;
using mat = vector<vec>;
const double EPS = 1e-8;

// 加減乗累乗
mat add(mat l, const mat& r) {
    assert(l.size()==l[0].size() && l.size()>=1);
    mat ret(l.size(), vec(l[0].size()));
    REP(i, l.size()) REP(j, l[0].size()) {
        ret[i][j] = l[i][j] + r[i][j];
    }
    return ret;
}
mat sub(mat l, const mat& r) {
    assert(l.size()==l[0].size() && l.size()>=1);
    mat ret(l.size(), vec(l[0].size()));
    REP(i, l.size()) REP(j, l[0].size()) {
        ret[i][j] = l[i][j] - r[i][j];
    }
}
mat mul(mat l, const mat& r) {
    assert(l[0].size()==r.size());
    mat ret(l.size(), vec(r[0].size()));
    REP(i, l.size()) REP(j, r[0].size()) REP(k, r.size()) {
        ret[i][j] += l[i][k] * r[k][j];
    }
    return ret;
}
mat pow(mat A, ll n) {
  mat B(A.size(), vec(A.size()));
  REP(i, A.size()) B[i][i] = 1;
  while(n > 0) {
    if(n & 1) B = mul(B, A);
    A = mul(A, A);
    n >>= 1;
  }
  return B;
}
// 階段行列を求める O(H*W*min(H,W))
mat gauss_jordan(mat a) {
    const int h = a.size(), w = a[0].size();
    REP(i, min(w, h)) {
        int pivot = i;
        REP(j, h) if(abs(a[j][i]) > abs(a[pivot][i])) pivot = j;
        swap(a[i], a[pivot]);
        FOR(j, i+1, w) a[i][j] /= a[i][i];
        REP(j, h) {
            if(i == j) continue;
            FOR(k, i+1, w) a[j][k] -= a[j][i] * a[i][k];
        }
    }
    return a;
}
// 行列式を求める
ll determinant(mat a) {
    const int h = a.size(), w = a[0].size();
    assert(h==w);
    REP(i, h) if(abs(a[i][i]) < EPS) return 0;
    REP(i, h) FOR(j, i+1, h) FOR(k, i, w) {
        a[j][k] -= a[j][i] * a[i][k] / a[i][i];    
    }
    double ret = 1;
    REP(i, h) ret *= a[i][i];
    return ret;
}
// ランクを求める
ll matrix_rank(mat a) {
    mat b = gauss_jordan(a);
    ll rank = b.size();
    REP(i, b.size()) {
        bool flag = false;
        REP(j, b.size()) if(b[i][j] > EPS) flag = true;
        if(!flag) { rank = i; break; }
    }
    return rank;
}
// 逆行列を求める
mat inv(mat a) {
    assert(a.size()==a[0].size());
    mat b(a.size(), vec(a.size()*2));
    REP(i, a.size()) REP(j, a.size()) b[i][j] = a[i][j]; 
    REP(i, a.size()) b[i][i+a.size()] = 1;
    mat c = gauss_jordan(b);
    if(matrix_rank(c) != a.size()) {
        return mat(a.size(), vec(a.size(), -1)); // !!!
    }
    mat ret(a.size(), vec(a.size()));
    REP(i, a.size()) REP(j, a.size()) ret[i][j] = c[i][j+a.size()];
    return ret;
}