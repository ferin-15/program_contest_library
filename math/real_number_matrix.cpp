// 実数体の行列 ToDo: verify
struct matrix {
    int h, w;
    vector<double> dat;
    matrix() {}
    matrix(int h, int w) : h(h), w(w), dat(h*w) {}
    double& get(int y, int x) { return dat[y*w+x]; }
    double get(int y, int x) const { return dat[y*w+x]; }

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
    bool operator==(const matrix& a) { return dat==a.dat; }
    bool operator!=(const matrix& a) { return dat!=a.dat; }

    friend matrix pow(matrix p, ll n) {
        matrix ret(p.h, p.w);
        REP(i, p.h) ret.get(i, i) = 1;
        while(n > 0) {
            if(n&1) {ret *= p; n--;}
            else {p *= p; n >>= 1;}
        }
        return ret;
    }
    // 階段行列を求める O(H*W^2)
    friend int gauss_jordan(matrix& a) {
        int rank = 0;
        REP(i, a.w) {
            int pivot = -1;
            FOR(j, rank, a.h) if(a.get(j,i) != 0) { pivot = j; break; }
            if(pivot == -1) continue;
            REP(j, a.w) swap(a.get(rank,j), a.get(pivot,j));
            const mint inv = a.get(rank,i).inv();
            REP(j, a.w) a.get(rank,j) *= inv;
            REP(j, a.h) if(j != rank && a.get(j,i) != 0) {
                const mint num = a.get(j,i);
                REP(k, a.w) a.get(j,k) -= a.get(rank,k) * num;
            }
            rank++;
        }
        return rank;
    }

    friend ostream &operator<<(ostream& os, matrix a) {
        REP(i, a.h) {
            REP(j, a.w) os << a.get(i,j) << " ";
            os << endl;
        }
        return os;
    }
};