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


# :warning: math/FPS.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/FPS.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
template<typename T>
struct formalPowerSeries {
    using Poly = vector<T>;
    using Conv = function<poly(poly,poly)>;
    Conv conv;
    formalPowerSeries(Conv conv) : conv(conv) {}

    // a mod x^deg を求める
    Poly pre(const Poly &a, int deg) {
        return Poly(a.begin(), a.begin()+min(a.size(),deg));
    }
    // 加減算 O(n)
    Poly add(Poly a, Poly b) {
        const int sz = max(a.size(), b.size());
        Poly c(sz, T(0));
        REP(i, a.size()) c[i] += a[i];
        REP(i, b.size()) c[i] += b[i];
        return c;
    }
    Poly sub(Poly a, Poly b) {
        const int sz = max(a.size(), b.size());
        Poly c(sz, T(0));
        REP(i, a.size()) c[i] += a[i];
        REP(i, b.size()) c[i] -= b[i];
        return c;
    }
    // 畳み込み O(nlogn)
    Poly mul(Poly a, Poly b) { return conv(a, b); }
    Poly mul(Poly a, T b) {
        REP(i, a.size()) a[i] *= b;
        return a;
    }
    // 1/a を求める O(nlogn)
    // 定数項が非0であること
    Poly inv(Poly a, int deg) {
        assert(a[0] != T(0));
        Poly ret({T(1)/as[0]});
        for(int i=1; i<deg; i<<=1) {
            ret = pre(sub(add(ret, ret), mul(mul(ret, ret), pre(a, i<<1))), i<<1);
        }
        return ret;
    }
    // a!=0 && b!=0
    Poly div(Poly a, Poly b) {
        while(a.back() == t(0)) a.pop_back();
        while(b.back() == t(0)) b.pop_back();
        if(b.size() > a.size()) return Poly();
        reverse(ALL(a)); reverse(ALL(b));
        int n = a.size()-b.size()+1;
        Poly ret = pre(mul(as, inv(bs, n)), n);
        reverse(ALL(ret));
        return ret;
    }
    // 定数項が1であること
    Poly sqrt(Poly a, int deg) {
        assert(a[0]==T(1));
        T inv2 = T(1)/2;
        Poly s({T(1)});
        for(int i=1; i<deg; i<<=1) {
            s = pre(add(ss, mul(pre(a, i<<1), inv(s, i<<1))), i<<1);
            for(auto &j: s) j *= inv2;
        }
    }
    // 微分 O(n)
    Poly diff(Poly a) {
        const int n = a.size();
        Poly r(n-1);
        FOR(i, 1, n) rs[i-1] = a[i] * T(i);
        return r;
    }
    // 積分 O(n) 定数項は0とする
    Poly integral(Poly a) {
        const int n = a.size();
        Poly ret(n+1);
        ret[0] = T(0);
        REP(i, n) ret[i+1] = ret[i] / T(i+1);
        return ret;
    }
    // 定数項は1であること
    Poly log(Poly a, int deg) {
        assert(a[0]==1);
        return pre(integral(mul(diff(a), inv(a, deg))), deg);
    }
    // 定数項が0であること
    Poly exp(Poly a, int deg) {
        assert(a[0]==0);
        Poly f({T(1)});
        a[0] += T(1);
        for(int i=1; i<deg; i<<=1) {
            f = pre(mul(f, sub(pre(a, i<<1), log(f, i<<1))), i<<1);
        }
        return f;
    }
};

template<class T, int primitive_root>
struct NTT {
    void ntt(vector<T>& a, int sign) {
        const int n = a.size();
        assert((n^(n&-n)) == 0);
        T g = 3; //g is primitive root of mod
        const ll mod = T::mod();
        T h = g.pow((mod-1)/n); // h^n = 1
        if(sign == -1) h = h.inv(); //h = h^-1 % mod
        //bit reverse
        int i = 0;
        for (int j = 1; j < n - 1; ++j) {
            for (int k = n >> 1; k >(i ^= k); k >>= 1);
            if (j < i) swap(a[i], a[j]);
        }
        for (int m = 1; m < n; m *= 2) {
            const int m2 = 2 * m;
            const T base = h.pow(n/m2);
            T w = 1;
            for(int x=0; x<m; ++x) {
                for (int s = x; s < n; s += m2) {
                    T u = a[s];
                    T d = a[s + m] * w;
                    a[s] = u + d;
                    a[s + m] = u - d;
                }
                w *= base;
            }
        }
    }
    void ntt(vector<T>& input) { ntt(input, 1); }
    void inv_ntt(vector<T>& input) {
        ntt(input, -1);
        const T n_inv = T((int)input.size()).inv();
        for(auto &x: input) x *= n_inv;
    }
    vector<T> convolution(const vector<T>& a, const vector<T>& b) {
        int sz = 1;
        while(sz < (int)a.size() + (int)b.size()) sz *= 2;
        vector<T> a2(a), b2(b);
        a2.resize(sz); b2.resize(sz);
        ntt(a2); ntt(b2);
        for(int i=0; i<sz; ++i) a2[i] *= b2[i];
        inv_ntt(a2);
        return a2;
    }
};

// NTT<mint, 3> ntt;
// auto conv = [&](auto a, auto b) { return ntt.convolution(a, b); };
// formalPowerSeries<mint> fps(conv);
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/FPS.cpp"
// BEGIN CUT
template<typename T>
struct formalPowerSeries {
    using Poly = vector<T>;
    using Conv = function<poly(poly,poly)>;
    Conv conv;
    formalPowerSeries(Conv conv) : conv(conv) {}

    // a mod x^deg を求める
    Poly pre(const Poly &a, int deg) {
        return Poly(a.begin(), a.begin()+min(a.size(),deg));
    }
    // 加減算 O(n)
    Poly add(Poly a, Poly b) {
        const int sz = max(a.size(), b.size());
        Poly c(sz, T(0));
        REP(i, a.size()) c[i] += a[i];
        REP(i, b.size()) c[i] += b[i];
        return c;
    }
    Poly sub(Poly a, Poly b) {
        const int sz = max(a.size(), b.size());
        Poly c(sz, T(0));
        REP(i, a.size()) c[i] += a[i];
        REP(i, b.size()) c[i] -= b[i];
        return c;
    }
    // 畳み込み O(nlogn)
    Poly mul(Poly a, Poly b) { return conv(a, b); }
    Poly mul(Poly a, T b) {
        REP(i, a.size()) a[i] *= b;
        return a;
    }
    // 1/a を求める O(nlogn)
    // 定数項が非0であること
    Poly inv(Poly a, int deg) {
        assert(a[0] != T(0));
        Poly ret({T(1)/as[0]});
        for(int i=1; i<deg; i<<=1) {
            ret = pre(sub(add(ret, ret), mul(mul(ret, ret), pre(a, i<<1))), i<<1);
        }
        return ret;
    }
    // a!=0 && b!=0
    Poly div(Poly a, Poly b) {
        while(a.back() == t(0)) a.pop_back();
        while(b.back() == t(0)) b.pop_back();
        if(b.size() > a.size()) return Poly();
        reverse(ALL(a)); reverse(ALL(b));
        int n = a.size()-b.size()+1;
        Poly ret = pre(mul(as, inv(bs, n)), n);
        reverse(ALL(ret));
        return ret;
    }
    // 定数項が1であること
    Poly sqrt(Poly a, int deg) {
        assert(a[0]==T(1));
        T inv2 = T(1)/2;
        Poly s({T(1)});
        for(int i=1; i<deg; i<<=1) {
            s = pre(add(ss, mul(pre(a, i<<1), inv(s, i<<1))), i<<1);
            for(auto &j: s) j *= inv2;
        }
    }
    // 微分 O(n)
    Poly diff(Poly a) {
        const int n = a.size();
        Poly r(n-1);
        FOR(i, 1, n) rs[i-1] = a[i] * T(i);
        return r;
    }
    // 積分 O(n) 定数項は0とする
    Poly integral(Poly a) {
        const int n = a.size();
        Poly ret(n+1);
        ret[0] = T(0);
        REP(i, n) ret[i+1] = ret[i] / T(i+1);
        return ret;
    }
    // 定数項は1であること
    Poly log(Poly a, int deg) {
        assert(a[0]==1);
        return pre(integral(mul(diff(a), inv(a, deg))), deg);
    }
    // 定数項が0であること
    Poly exp(Poly a, int deg) {
        assert(a[0]==0);
        Poly f({T(1)});
        a[0] += T(1);
        for(int i=1; i<deg; i<<=1) {
            f = pre(mul(f, sub(pre(a, i<<1), log(f, i<<1))), i<<1);
        }
        return f;
    }
};

template<class T, int primitive_root>
struct NTT {
    void ntt(vector<T>& a, int sign) {
        const int n = a.size();
        assert((n^(n&-n)) == 0);
        T g = 3; //g is primitive root of mod
        const ll mod = T::mod();
        T h = g.pow((mod-1)/n); // h^n = 1
        if(sign == -1) h = h.inv(); //h = h^-1 % mod
        //bit reverse
        int i = 0;
        for (int j = 1; j < n - 1; ++j) {
            for (int k = n >> 1; k >(i ^= k); k >>= 1);
            if (j < i) swap(a[i], a[j]);
        }
        for (int m = 1; m < n; m *= 2) {
            const int m2 = 2 * m;
            const T base = h.pow(n/m2);
            T w = 1;
            for(int x=0; x<m; ++x) {
                for (int s = x; s < n; s += m2) {
                    T u = a[s];
                    T d = a[s + m] * w;
                    a[s] = u + d;
                    a[s + m] = u - d;
                }
                w *= base;
            }
        }
    }
    void ntt(vector<T>& input) { ntt(input, 1); }
    void inv_ntt(vector<T>& input) {
        ntt(input, -1);
        const T n_inv = T((int)input.size()).inv();
        for(auto &x: input) x *= n_inv;
    }
    vector<T> convolution(const vector<T>& a, const vector<T>& b) {
        int sz = 1;
        while(sz < (int)a.size() + (int)b.size()) sz *= 2;
        vector<T> a2(a), b2(b);
        a2.resize(sz); b2.resize(sz);
        ntt(a2); ntt(b2);
        for(int i=0; i<sz; ++i) a2[i] *= b2[i];
        inv_ntt(a2);
        return a2;
    }
};

// NTT<mint, 3> ntt;
// auto conv = [&](auto a, auto b) { return ntt.convolution(a, b); };
// formalPowerSeries<mint> fps(conv);
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

