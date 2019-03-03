// 有限体の行列
struct matrix {
    int h, w;
    vector<ll> dat;
    matrix() {}
    matrix(int h, int w) : h(h), w(w), dat(h*w) {}
    ll& get(int y, int x) { return dat[y*w+x]; }
    ll get(int y, int x) const { return dat[y*w+x]; }

    matrix& operator+=(const matrix& r) {
        assert(h==r.h && w==r.w);
        REP(i, h*w) {
            dat[i] += r.dat[i]; 
            if(dat[i] >= MOD) dat[i] -= MOD;
        }
        return *this;
    }
    matrix& operator-=(const matrix& r) {
        assert(h==r.h && w==r.w);
        REP(i, h*w) {
            dat[i] -= r.dat[i];
            if(dat[i] < 0) dat[i] += MOD;
        }
        return *this;
    }
    matrix& operator*=(const matrix& r) {
        assert(w==r.h);
        matrix ret(2, 2);
        REP(i, h) REP(j, r.w) REP(k, w) {
            ret.dat[i*r.w+j] += dat[i*w+k] * r.dat[k*r.w+j] % MOD;
            if(ret.dat[i*r.w+j] >= MOD) ret.dat[i*r.w+j] -= MOD;
        }
        return (*this) = ret;
    }
};
matrix operator+(const matrix& l, const matrix& r) { 
    return matrix(l) += r; 
}
matrix operator-(const matrix& l, const matrix& r) {
    return matrix(l) -= r;
}
matrix operator*(const matrix& l, const matrix& r) {
    return matrix(l) *= r;
}
matrix pow(matrix A, ll n) {
    matrix B(A.h, A.w);
    REP(i, A.h) B.get(i, i) = 1;
    while(n > 0) {
        if(n&1) B *= A;
        A *= A;
        n >>= 1;
    }
}
// 有限体の除算用
ll binpow(ll x, ll e) {
  ll ret = 1, p = x;
  while(e > 0) {
    if(e&1) {(ret *= p) %= MOD; e--;}
    else {(p *= p) %= MOD; e /= 2;} 
  }
  return ret;
}
// 階段行列を求める O(H*W*min(H,W))
matrix gauss_jordan(matrix a) {
    REP(i, min(a.w, a.h)) {
        int pivot = i;
        REP(j, a.h) if(abs(a.get(j, i)) > abs(a.get(pivot, i))) pivot = j;
        vector<ll> tmp(a.w);
        REP(j, a.w) tmp[j] = a.get(pivot, j);
        REP(j, a.w) a.get(pivot, j) = a.get(i, j);
        REP(j, a.w) a.get(i, j) = tmp[j];
        FOR(j, i+1, a.w) (a.get(i, j) *= binpow(a.get(i, i), MOD-2)) %= MOD;
        REP(j, a.h) {
            if(i == j) continue;
            FOR(k, i+1, a.w) {
                a.get(j, k) -= a.get(j, i) * a.get(i, k) % MOD;
                if(a.get(j, k) < 0) a.get(j, k) += MOD;
            }
        }
    }
    return a;
}
// 行列式を求める
ll determinant(matrix a) {
    assert(a.h==a.w);
    REP(i, a.h) if(a.get(i, i) == 0) return 0;
    REP(i, a.h) FOR(j, i+1, a.h) FOR(k, i, a.w) {
        ll tmp = a.get(j,i) * a.get(i,k) % MOD;
        (tmp *= binpow(a.get(i,i), MOD-2)) %= MOD; 
        a.get(j,k) -=  tmp;
        if(a.get(j, k) < 0) a.get(j, k) += MOD;
    }
    ll ret = 1;
    REP(i, a.h) (ret *= a.get(i, i)) %= MOD;
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