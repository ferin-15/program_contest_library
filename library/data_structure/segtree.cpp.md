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


# :heavy_check_mark: data_structure/segtree.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/segtree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/DSL2A_1.test.cpp.html">test/DSL2A_1.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DSL2B_2.test.cpp.html">test/DSL2B_2.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
// 根が1
template<typename Monoid>
struct segtree {
    using T = typename Monoid::T;
    int n;
    vector<T> dat;

    segtree(int n_) {
        n = 1;
        while(n < n_) n <<= 1;
        dat.assign(n*2, Monoid::id());
    }
    void build(vector<T> v) {
        REP(i, v.size()) dat[i+n] = v[i];
        for(int i=n-1; i>0; --i) dat[i] = Monoid::op(dat[i*2], dat[i*2+1]);
    }

    T query(int a, int b) {
        if(a >= b) return Monoid::id();
        T l = Monoid::id(), r = Monoid::id();
        for(a+=n, b+=n; a<b; a>>=1, b>>=1) {
            if(a&1) l = Monoid::op(l, dat[a++]);
            if(b&1) r = Monoid::op(dat[--b], r);
        }
        return Monoid::op(l, r);
    }
    void update(int i, T v) {
        i += n;
        dat[i] = v;
        while(i >>= 1) {
            dat[i] = Monoid::op(dat[i*2], dat[i*2+1]);
        }
    }

    friend ostream &operator <<(ostream& out,const segtree<Monoid>& seg){
        out << "---------------------" << endl;
        int cnt = 1;
        for(int i=1; i<=seg.n; i*=2) {
            REP(j, i) {
                out << seg.dat[cnt] << " ";
                cnt++;
            }
            out << endl;
        }
        out << "---------------------" << endl;
        return out;
    }
};

template<typename Tp>
struct min_monoid {
    using T = Tp;
    static constexpr Tp id() { return INT_MAX; }
    static Tp op(const Tp &a, const Tp &b) { return min(a, b); }
};
template<typename Tp>
struct max_monoid {
    using T = Tp;
    static constexpr Tp id() { return -INF; }
    static Tp op(const Tp &a, const Tp &b) { return max(a, b); }
};
template<typename Tp>
struct sum_monoid {
    using T = Tp;
    static constexpr Tp id() { return 0; }
    static Tp op(const Tp &a, const Tp &b) { return a+b; }
};
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/segtree.cpp"
// BEGIN CUT
// 根が1
template<typename Monoid>
struct segtree {
    using T = typename Monoid::T;
    int n;
    vector<T> dat;

    segtree(int n_) {
        n = 1;
        while(n < n_) n <<= 1;
        dat.assign(n*2, Monoid::id());
    }
    void build(vector<T> v) {
        REP(i, v.size()) dat[i+n] = v[i];
        for(int i=n-1; i>0; --i) dat[i] = Monoid::op(dat[i*2], dat[i*2+1]);
    }

    T query(int a, int b) {
        if(a >= b) return Monoid::id();
        T l = Monoid::id(), r = Monoid::id();
        for(a+=n, b+=n; a<b; a>>=1, b>>=1) {
            if(a&1) l = Monoid::op(l, dat[a++]);
            if(b&1) r = Monoid::op(dat[--b], r);
        }
        return Monoid::op(l, r);
    }
    void update(int i, T v) {
        i += n;
        dat[i] = v;
        while(i >>= 1) {
            dat[i] = Monoid::op(dat[i*2], dat[i*2+1]);
        }
    }

    friend ostream &operator <<(ostream& out,const segtree<Monoid>& seg){
        out << "---------------------" << endl;
        int cnt = 1;
        for(int i=1; i<=seg.n; i*=2) {
            REP(j, i) {
                out << seg.dat[cnt] << " ";
                cnt++;
            }
            out << endl;
        }
        out << "---------------------" << endl;
        return out;
    }
};

template<typename Tp>
struct min_monoid {
    using T = Tp;
    static constexpr Tp id() { return INT_MAX; }
    static Tp op(const Tp &a, const Tp &b) { return min(a, b); }
};
template<typename Tp>
struct max_monoid {
    using T = Tp;
    static constexpr Tp id() { return -INF; }
    static Tp op(const Tp &a, const Tp &b) { return max(a, b); }
};
template<typename Tp>
struct sum_monoid {
    using T = Tp;
    static constexpr Tp id() { return 0; }
    static Tp op(const Tp &a, const Tp &b) { return a+b; }
};
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

