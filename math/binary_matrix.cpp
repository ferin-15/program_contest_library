// BEGIN CUT
// GF(2)の行列
template<int width=64>
struct matrix {
    int h, w;
    vector<bitset<width>> dat;
    matrix() {}
    matrix(int h) : h(h), w(width), dat(h) {}

    matrix& operator+=(const matrix& r) {
        assert(h==r.h && w==r.w);
        REP(i, h) dat[i] ^= r.dat[i];
        return *this;
    }
    matrix& operator-=(const matrix& r) {
        assert(h==r.h && w==r.w);
        REP(i, h) dat[i] ^= r.dat[i];
        return *this;
    }
    matrix& operator*=(const matrix& r) {
        assert(w==r.h);
        matrix ret(h, w);
        REP(i, h) REP(j, r.w) REP(k, w) {
            ret.dat[i][j] ^= dat[i][k] & r.dat[k][j];
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
        REP(i, p.h) ret.dat[i][i] = 1;
        while(n > 0) {
            if(n&1) {ret *= p; n--;}
            else {p *= p; n >>= 1;}
        }
        return ret;
    }
    // 階段行列を求める O(HW^2)
    friend int gauss_jordan(matrix &a) {
        int rank = 0;
        REP(i, a.w) {
            int pivot = -1;
            FOR(j, rank, a.h) if(a.dat[j][i] != 0) { pivot = j; break; }
            if(pivot == -1) continue;
            swap(a.dat[rank], a.dat[pivot]);
            REP(j, a.h) if(j != rank && a.dat[j][i] != 0) {
                a.dat[j] ^= a.dat[rank];
            }
            rank++;
        }
        return rank;
    }

    friend ostream &operator<<(ostream& os, matrix a) {
        REP(i, a.h) {
            REP(j, a.w) os << a.dat[i][j] << " ";
            os << endl;
        }
        return os;
    }
};
// END CUT