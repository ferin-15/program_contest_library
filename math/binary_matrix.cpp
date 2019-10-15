#include <bits/stdc++.h>

using namespace std;
using ll = long long;
// #define int ll
using PII = pair<ll, ll>;

#define FOR(i, a, n) for (ll i = (ll)a; i < (ll)n; ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(x) x.begin(), x.end()

template<typename T> T &chmin(T &a, const T &b) { return a = min(a, b); }
template<typename T> T &chmax(T &a, const T &b) { return a = max(a, b); }
template<typename T> bool IN(T a, T b, T x) { return a<=x&&x<b; }
template<typename T> T ceil(T a, T b) { return a/b + !!(a%b); }

template<typename T> vector<T> make_v(size_t a) { return vector<T>(a); }
template<typename T,typename... Ts>
auto make_v(size_t a,Ts... ts) {
    return vector<decltype(make_v<T>(ts...))>(a,make_v<T>(ts...));
}
template<typename T,typename V> typename enable_if<is_class<T>::value==0>::type
fill_v(T &t, const V &v) { t=v; }
template<typename T,typename V> typename enable_if<is_class<T>::value!=0>::type
fill_v(T &t, const V &v ) { for(auto &e:t) fill_v(e,v); }

template<class S,class T>
ostream &operator <<(ostream& out,const pair<S,T>& a) {
    out<<'('<<a.first<<','<<a.second<<')'; return out;
}
template<class T>
ostream &operator <<(ostream& out,const vector<T>& a){
    out<<'[';
    for(const T &i: a) out<<i<<',';
    out<<']';
    return out;
}
template<class T>
ostream &operator <<(ostream& out, const set<T>& a) {
    out<<'{';
    for(const T &i: a) out<<i<<',';
    out<<'}';
    return out;
}
template<class T, class S>
ostream &operator <<(ostream& out, const map<T,S>& a) {
    out<<'{';
    for(auto &i: a) out<<i<<',';
    out<<'}';
    return out;
}

int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0}; // DRUL
const int INF = 1<<30;
const ll LLINF = 1LL<<60;

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

// mod 2 でgauss jordanをする
namespace codeflyer_D {
    void solve() {
        ll n;
        cin >> n;
        vector<ll> a(n), b(n);
        REP(i, n) cin >> a[i];
        REP(i, n) cin >> b[i];

        matrix<64> mata(n), matb(n);
        REP(i, n) {
            REP(j, 61) {
                mata.dat[i][j] = !!(a[i]&1LL<<j);
                matb.dat[i][j] = !!(b[i]&1LL<<j);
            }
        }

        gauss_jordan(mata); gauss_jordan(matb);
        if(mata == matb) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
}

// mod 2 で行列式を求める
namespace ARC054C {
    void solve() {
        ll n;
        cin >> n;
        vector<string> s(n);
        REP(i, n) cin >> s[i];
        matrix<200> mat(n);
        REP(i, n) REP(j, n) mat.dat[i][j] = s[i][j]-'0';

        gauss_jordan(mat);
        ll ret = 1;
        REP(i, n) ret *= mat.dat[i][i];
        cout << (ret==1 ? "Odd" : "Even") << endl;
    }
}