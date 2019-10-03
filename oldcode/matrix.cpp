// 実数体じゃなくて有限体なら四則演算を切り替える
const double EPS = 1e-8;
using mat = vector<vector<double>>;
mat gauss_jordan(mat a) {
    const int h = a.size(), w = a[0].size();
    REP(i, min(w, h)) {
        int pivot = i;
        REP(j, h) if(abs(a[j][i]) > abs(a[pivot][i])) pivot = j;
        swap(a[i], a[pivot]);
        if(abs(a[i][i]) < EPS) continue;
        FOR(j, i+1, w) a[i][j] /= a[i][i];
        REP(j, h) {
            if(i == j) continue;
            FOR(k, i+1, w) a[j][k] -= a[j][i] * a[i][k];
        }
    }
    return a;
}

double determinant(mat a) {
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