// 有限体の行列
struct matrix {
    int h, w;
    vector<mint> dat;
    matrix() {}
    matrix(int h, int w) : h(h), w(w), dat(h*w) {}
    mint& get(int y, int x) { return dat[y*w+x]; }
    mint get(int y, int x) const { return dat[y*w+x]; }

    matrix& operator+=(const matrix& r) {
        assert(h==r.h && w==r.w);
        REP(i, h*w) dat[i] += r.dat[i];
        return *this;
    }
    matrix& operator-=(const matrix& r) {
        assert(h==r.h && w==r.w);
        REP(i, h*w) dat[i] -= r.dat[i];
        return *this;
    }
    matrix& operator*=(const matrix& r) {
        assert(w==r.h);
        matrix ret(h, w);
        REP(i, h) REP(j, r.w) REP(k, w) {
            ret.dat[i*r.w+j] += dat[i*w+k] * r.dat[k*r.w+j];
        }
        return (*this) = ret;
    }
    matrix operator+(const matrix& r) { return matrix(*this) += r; }
    matrix operator-(const matrix& r) { return matrix(*this) -= r; }
    matrix operator*(const matrix& r) { return matrix(*this) *= r; }
    matrix pow(ll n) {
        matrix ret(h, w), p = *this;
        REP(i, h) ret.get(i, i) = 1;
        while(n > 0) {
            if(n&1) {ret *= p; n--;}
            else {p *= p; n >>= 1;}
        }
        return ret;
    }
};

// 階段行列を求める O(H*W*min(H,W))
matrix gauss_jordan(matrix a) {
    REP(i, min(a.w, a.h)) {
        int pivot = i;
        REP(j, a.h) if(abs(a.get(j, i)) > abs(a.get(pivot, i))) pivot = j;
        vector<mint> tmp(a.w);
        REP(j, a.w) tmp[j] = a.get(pivot, j);
        REP(j, a.w) a.get(pivot, j) = a.get(i, j);
        REP(j, a.w) a.get(i, j) = tmp[j];
        FOR(j, i+1, a.w) a.get(i, j) *= a.get(i, i).inv();
        REP(j, a.h) {
            if(i == j) continue;
            FOR(k, i+1, a.w) a.get(j, k) -= a.get(j, i) * a.get(i, k);
        }
    }
    return a;
}
// 行列式を求める
mint determinant(matrix a) {
    assert(a.h==a.w);
    REP(i, a.h) if(a.get(i, i) == 0) return 0;
    REP(i, a.h) FOR(j, i+1, a.h) FOR(k, i, a.w) {
        a.get(j,k) -= a.get(j,i) * a.get(i,k) * a.get(i,i).inv();
    }
    mint ret = 1;
    REP(i, a.h) ret *= a.get(i, i);
    return ret;
}
// ランクを求める
ll matrix_rank(matrix a) {
    matrix b = gauss_jordan(a);
    ll rank = b.h;
    REP(i, b.h) {
        bool flag = false;
        REP(j, b.w) if(b.get(i, j)) flag = true;
        if(!flag) { rank = i; break; }
    }
    return rank;
}
// 逆行列を求める
matrix inv(matrix a) {
    assert(a.h==a.w);
    matrix b(a.h, a.w*2);
    REP(i, a.h) REP(j, a.w) b.get(i, j) = a.get(i, j);
    REP(i, a.h) b.get(i, i+a.w) = 1;
    matrix c = gauss_jordan(b);
    if(matrix_rank(c) != a.h) {
        return matrix(a.h, a.w); // !!!
    }
    matrix ret(a.h, a.w);
    REP(i, a.h) REP(j, a.w) ret.get(i, j) = c.get(i, j+a.h);
    return ret;
}
