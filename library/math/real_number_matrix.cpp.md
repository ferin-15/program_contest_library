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


# :warning: math/real_number_matrix.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/real_number_matrix.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 04:35:05+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/real_number_matrix.cpp"
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

