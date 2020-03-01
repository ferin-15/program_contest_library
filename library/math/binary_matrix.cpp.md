---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :x: math/binary_matrix.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/binary_matrix.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00




## Verified with

* :x: <a href="../../verify/test/aoj1308.test.cpp.html">test/aoj1308.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/binary_matrix.cpp"
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

