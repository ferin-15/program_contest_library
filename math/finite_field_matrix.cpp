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
    // 階段行列を求める O(HW^2)
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

// 任意mod(<=1e9)で行列累乗
namespace ARC050C {
    void solve() {
        ll a, b;
        cin >> a >> b >> MOD;

        ll g = __gcd(a, b);

        matrix X(2, 2);
        X.get(0,0) = 10, X.get(0,1) = 1;
        X.get(1,1) = 1;
        matrix ret = pow(X, a-1);
        mint ans = ret.get(0,0) + ret.get(0,1);

        matrix Y(2, 2);
        Y.get(0,0) = mint(10).pow(g), Y.get(0,1) = 1;
        Y.get(1,1) = 1;
        ret = pow(Y, b/g-1);
        ans *= ret.get(0,0) + ret.get(0,1);

        cout << ans << endl;
    }
}

// mod 2 でgauss jordanをする
namespace codeflyer_D {
    void solve() {
        ll n;
        cin >> n;
        vector<ll> a(n), b(n);
        REP(i, n) cin >> a[i];
        REP(i, n) cin >> b[i];

        MOD = 2;
        matrix mata(n, 61), matb(n, 61);
        REP(i, n) {
            REP(j, 61) {
                mata.get(i,j) = !!(a[i]&1LL<<j);
                matb.get(i,j) = !!(b[i]&1LL<<j);
            }
        }

        gauss_jordan(mata), gauss_jordan(matb);
        if(mata == matb) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
}
