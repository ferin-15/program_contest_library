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


# :heavy_check_mark: data_structure/lazysegtree.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/lazysegtree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00




## Required by

* :warning: <a href="../test/DSL2F.memo.cpp.html">test/DSL2F.memo.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/DSL2G_0.test.cpp.html">test/DSL2G_0.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DSL2H_0.test.cpp.html">test/DSL2H_0.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DSL2I_0.test.cpp.html">test/DSL2I_0.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/GRL5D.test.cpp.html">test/GRL5D.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/GRL5E.test.cpp.html">test/GRL5E.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj2667.test.cpp.html">test/aoj2667.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yuki899.test.cpp.html">test/yuki899.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
template <typename Monoid>
struct lazysegtree {
    using T = typename Monoid::T;
    using E = typename Monoid::E;
    int n, height;
    vector<T> dat;
    vector<E> lazy;

    lazysegtree() {}
    lazysegtree(int n_) {
        n = 1, height = 0;
        while(n <= n_) { n *= 2; height++; }
        dat.assign(n*2, Monoid::dt());
        lazy.assign(n*2, Monoid::de());
    }
    void build(vector<T> v) {
        REP(i, v.size()) dat[i+n] = v[i];
        for(int i=n-1; i>0; --i) dat[i] = Monoid::f(dat[i*2], dat[i*2+1]);
    }

    inline T reflect(int k) { return lazy[k]==Monoid::de()?dat[k]:Monoid::g(dat[k], lazy[k]); }
    inline void eval(int k) {
        if(lazy[k] == Monoid::de()) return;
        lazy[2*k]   = Monoid::h(lazy[k*2],   lazy[k]);
        lazy[2*k+1] = Monoid::h(lazy[k*2+1], lazy[k]);
        dat[k] = reflect(k);
        lazy[k] = Monoid::de();
    }
    inline void thrust(int k) { for(int i=height;i;--i) eval(k>>i); }
    inline void recalc(int k) { while(k>>=1) dat[k] = Monoid::f(reflect(k*2), reflect(k*2+1)); }

    void update(int a, int b, E x) {
        if(a >= b) return;
        thrust(a+=n);
        thrust(b+=n-1);
        for(int l=a, r=b+1; l<r; l>>=1,r>>=1) {
            if(l&1) lazy[l] = Monoid::h(lazy[l], x), ++l;
            if(r&1) --r, lazy[r] = Monoid::h(lazy[r], x);
        }
        recalc(a);
        recalc(b);
    }
    T query(int a, int b) {
        if(a >= b) return Monoid::dt();
        thrust(a+=n);
        thrust(b+=n-1);
        T vl=Monoid::dt(), vr=Monoid::dt();
        for(int l=a, r=b+1; l<r; l>>=1,r>>=1) {
            if(l&1) vl=Monoid::f(vl, reflect(l++));
            if(r&1) vr=Monoid::f(reflect(--r), vr);
        }
        return Monoid::f(vl, vr);
    }

    friend ostream &operator <<(ostream& out,const lazysegtree<Monoid>& seg) {
        out << "---------------------" << endl;
        int cnt = 1;
        for(int i=1; i<=seg.n; i*=2) {
            REP(j, i) {
                out << "(" << seg.dat[cnt] << "," << seg.lazy[cnt] << ") ";
                cnt++;
            }
            out << endl;
        }
        out << "---------------------" << endl;
        return out;
    }
};

struct node {
    ll sum, max, min, len;
    node() : sum(0), max(-INF), min(INF), len(0) {}
    node(ll a) : sum(a), max(a), min(a), len(1) {}
};
struct linear_exp {
    using T = node;
    using E = PII;
    static T dt() { return node(); }
    static constexpr E de() { return PII(1, 0); }
    static T f(const T &a, const T &b) {
        node ret;
        ret.sum = a.sum + b.sum;
        ret.min = min(a.min, b.min);
        ret.max = max(a.max, b.max);
        ret.len = a.len + b.len;
        return ret;
    }
    static T g(const T &a, const E &b) {
        node ret;
        ret.sum = b.first*a.sum+b.second*a.len;
        ret.min = b.first*a.min+b.second;
        ret.max = b.first*a.max+b.second;
        ret.len = a.len;
        return ret;
    }
    static E h(const E &a, const E &b) {
        return PII(b.first*a.first, b.first*a.second+b.second);
    }
};
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/lazysegtree.cpp"
// BEGIN CUT
template <typename Monoid>
struct lazysegtree {
    using T = typename Monoid::T;
    using E = typename Monoid::E;
    int n, height;
    vector<T> dat;
    vector<E> lazy;

    lazysegtree() {}
    lazysegtree(int n_) {
        n = 1, height = 0;
        while(n <= n_) { n *= 2; height++; }
        dat.assign(n*2, Monoid::dt());
        lazy.assign(n*2, Monoid::de());
    }
    void build(vector<T> v) {
        REP(i, v.size()) dat[i+n] = v[i];
        for(int i=n-1; i>0; --i) dat[i] = Monoid::f(dat[i*2], dat[i*2+1]);
    }

    inline T reflect(int k) { return lazy[k]==Monoid::de()?dat[k]:Monoid::g(dat[k], lazy[k]); }
    inline void eval(int k) {
        if(lazy[k] == Monoid::de()) return;
        lazy[2*k]   = Monoid::h(lazy[k*2],   lazy[k]);
        lazy[2*k+1] = Monoid::h(lazy[k*2+1], lazy[k]);
        dat[k] = reflect(k);
        lazy[k] = Monoid::de();
    }
    inline void thrust(int k) { for(int i=height;i;--i) eval(k>>i); }
    inline void recalc(int k) { while(k>>=1) dat[k] = Monoid::f(reflect(k*2), reflect(k*2+1)); }

    void update(int a, int b, E x) {
        if(a >= b) return;
        thrust(a+=n);
        thrust(b+=n-1);
        for(int l=a, r=b+1; l<r; l>>=1,r>>=1) {
            if(l&1) lazy[l] = Monoid::h(lazy[l], x), ++l;
            if(r&1) --r, lazy[r] = Monoid::h(lazy[r], x);
        }
        recalc(a);
        recalc(b);
    }
    T query(int a, int b) {
        if(a >= b) return Monoid::dt();
        thrust(a+=n);
        thrust(b+=n-1);
        T vl=Monoid::dt(), vr=Monoid::dt();
        for(int l=a, r=b+1; l<r; l>>=1,r>>=1) {
            if(l&1) vl=Monoid::f(vl, reflect(l++));
            if(r&1) vr=Monoid::f(reflect(--r), vr);
        }
        return Monoid::f(vl, vr);
    }

    friend ostream &operator <<(ostream& out,const lazysegtree<Monoid>& seg) {
        out << "---------------------" << endl;
        int cnt = 1;
        for(int i=1; i<=seg.n; i*=2) {
            REP(j, i) {
                out << "(" << seg.dat[cnt] << "," << seg.lazy[cnt] << ") ";
                cnt++;
            }
            out << endl;
        }
        out << "---------------------" << endl;
        return out;
    }
};

struct node {
    ll sum, max, min, len;
    node() : sum(0), max(-INF), min(INF), len(0) {}
    node(ll a) : sum(a), max(a), min(a), len(1) {}
};
struct linear_exp {
    using T = node;
    using E = PII;
    static T dt() { return node(); }
    static constexpr E de() { return PII(1, 0); }
    static T f(const T &a, const T &b) {
        node ret;
        ret.sum = a.sum + b.sum;
        ret.min = min(a.min, b.min);
        ret.max = max(a.max, b.max);
        ret.len = a.len + b.len;
        return ret;
    }
    static T g(const T &a, const E &b) {
        node ret;
        ret.sum = b.first*a.sum+b.second*a.len;
        ret.min = b.first*a.min+b.second;
        ret.max = b.first*a.max+b.second;
        ret.len = a.len;
        return ret;
    }
    static E h(const E &a, const E &b) {
        return PII(b.first*a.first, b.first*a.second+b.second);
    }
};
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

