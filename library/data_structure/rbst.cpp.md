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


# :heavy_check_mark: data_structure/rbst.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/rbst.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/DSL2A_0.test.cpp.html">test/DSL2A_0.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DSL2B_1.test.cpp.html">test/DSL2B_1.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DSL2F.test.cpp.html">test/DSL2F.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DSL2G_1.test.cpp.html">test/DSL2G_1.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DSL2H_1.test.cpp.html">test/DSL2H_1.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/DSL2I_1.test.cpp.html">test/DSL2I_1.test.cpp</a>
* :x: <a href="../../verify/test/aoj1508.test.cpp.html">test/aoj1508.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
template<class M>
struct RBST {
    using T = typename M::T;
    using E = typename M::E;

    struct node {
        node *l, *r, *p;
        T val;
        E lazy;
        bool rev;
        int sz;

        node(T v, E p) : l(nullptr),r(nullptr),val(v),lazy(p),rev(false),sz(1) {}
    };

    int size(node* a) { return !a ? 0 : a->sz; }
    T val(node* a) { return !a ? M::dt() : (eval(a), a->val); }
    node* fix(node* a) {
        a->sz = size(a->l) + 1 + size(a->r);
        a->val = M::f(val(a->l), a->val, val(a->r));
        return a;
    }
    void eval(node* a) {
        if(a->lazy != M::de()) {
            a->val = M::g(a->val, a->lazy, size(a));
            if(a->l) a->l->lazy = M::h(a->l->lazy, a->lazy);
            if(a->r) a->r->lazy = M::h(a->r->lazy, a->lazy);
            a->lazy = M::de();
        }
        if(a->rev) {
            swap(a->l, a->r);
            if(a->l) a->l->rev ^= 1;
            if(a->r) a->r->rev ^= 1;
            a->rev = false;
        }
    }

    inline int xor128() {
        static int x = 123456789, y = 362436069, z = 521288629, w = 88675123;
        int t;
        t = x ^ (x << 11); x = y; y = z; z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }

    node* merge(node *a, node *b) {
        if(!a) return b;
        if(!b) return a;
        eval(a); eval(b);
        if(xor128() % (size(a) + size(b)) < size(a)) {
            a->r = merge(a->r, b);
            if(a->r) a->r->p = a;
            return fix(a);
        } else {
            b->l = merge(a, b->l);
            if(b->l) b->l->p = b;
            return fix(b);
        }
    }
    // [0,k) [k,n)
    pair<node*, node*> split(node *a, int k) {
        if(!a) return pair<node*, node*>(nullptr, nullptr);
        eval(a);
        node *sl, *sr;
        if(k <= size(a->l)) {
            tie(sl, sr) = split(a->l, k);
            if(a->l) a->l->p = nullptr;
            a->l = sr;
            if(a->l) a->l->p = a;
            return pair<node*, node*>(sl, fix(a));
        }
        tie(sl, sr) = split(a->r, k - size(a->l) - 1);
        if(a->r) a->r->p = nullptr;
        a->r = sl;
        if(a->r) a->r->p = a;
        return pair<node*, node*>(fix(a), sr);
    }
    // 要素の挿入/削除
    void insert(node*& a, int k, const T& x) {
        node *sl, *sr;
        tie(sl, sr) = split(a, k);
        a = merge(sl, merge(new node(x, M::de()), sr));
    }
    T erase(node*& a, int k) {
        node *sl, *sr, *tl, *tr;
        tie(sl, sr) = split(a, k + 1);
        tie(tl, tr) = split(sl, k);
        a = merge(tl, sr);
        return val(tr);
    }
    // 点更新
    void update(node*& a, int k, const E& x) {
        node *sl, *sr, *tl, *tr;
        tie(sl, sr) = split(a, k + 1);
        tie(tl, tr) = split(sl, k);
        if(tr) tr->val = M::g(tr->val, x, size(tr));
        a = merge(merge(tl, tr), sr);
    }
    // 区間更新
    void update(node*& a, int l, int r, const E& m) {
        node *sl, *sr, *tl, *tr;
        tie(sl, sr) = split(a, r);
        tie(tl, tr) = split(sl, l);
        if(tr) tr->lazy = M::h(tr->lazy, m);
        a = merge(merge(tl, tr), sr);
    }
    // 点取得
    T get(node*& a, int k) {
        node *sl, *sr, *tl, *tr;
        tie(sl, sr) = split(a, k + 1);
        tie(tl, tr) = split(sl, k);
        T res = !tr ? M::dt() : tr->val;
        a = merge(merge(tl, tr), sr);
        return res;
    }
    // 区間クエリ
    T query(node*& a, int l, int r) {
        node *sl, *sr, *tl, *tr;
        tie(sl, sr) = split(a, r);
        tie(tl, tr) = split(sl, l);
        T res = !tr ? M::dt() : tr->val;
        a = merge(merge(tl, tr), sr);
        return res;
    }
    // 区間[l,r)の反転
    void reverse(node*& a, int l, int r) {
        node *sl, *sr, *tl, *tr;
        tie(sl, sr) = split(a, r);
        tie(tl, tr) = split(sl, l);
        if(tr) tr->rev ^= 1;
        a = merge(merge(tl, tr), sr);
    }
    // 頂点aが属する木の根を求める
    node* getroot(node *a) {
        if(!a->p) return a;
        return getroot(a->p);
    }
    // x以上の最小の位置
    int lower_bound(node *t, const T &x) {
        if(!t) return 0;
        if(x <= val(t)) return lower_bound(t->l, x);
        return lower_bound(t->r, x) + size(t->l) + 1;
    }
    // xより大きい最小の位置
    int upper_bound(node *t, const T &x) {
        if(!t) return 0;
        if(x < val(t)) return upper_bound(t->l, x);
        return upper_bound(t->r, x) + RBST<T>::size(t->l) + 1;
    }
    // xの個数
    int count(node *t, const T &x) {
        return upper_bound(t, x) - lower_bound(t, x);
    }
    // k番目の要素を求める
    T kth_element(node *t, int k) {
        if(k < RBST<T>::size(t->l)) return kth_element(t->l, k);
        if(k == RBST<T>::size(t->l)) return val(t);
        return kth_element(t->r, k - RBST<T>::size(t->l) - 1);
    }
    // 要素xを追加する
    void insert_key(node *&t, const T &x) {
        RBST<T>::insert(t, lower_bound(t, x), x);
    }
    // 要素xを消す
    void erase_key(node *&t, const T &x) {
        if(!count(t, x)) return;
        RBST<T>::erase(t, lower_bound(t, x));
    }
    // デバッグ用
    void debug(node* t) {
        if(t == nullptr) return;
        cerr << "{";
        debug(t->l);
        cerr << " " << t->val << " ";
        debug(t->r);
        cerr << "}";
    }
};

/*
struct update_min {
    using T = PII;
    using E = ll;
    static T dt() { return PII(INT_MAX, INT_MAX); }
    static constexpr E de() { return INT_MAX; }
    static T f(const T &l, const T &self, const T &r) {
        return PII(self.first, min({l.second, self.first, r.second}));
    }
    static T g(const T &a, const E &b, const int &sz) {
        return b == de() ? a : PII(b, b);
    }
    static E h(const E &a, const E &b) {
        return b == de() ? a : b;
    }
};
*/
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/rbst.cpp"
// BEGIN CUT
template<class M>
struct RBST {
    using T = typename M::T;
    using E = typename M::E;

    struct node {
        node *l, *r, *p;
        T val;
        E lazy;
        bool rev;
        int sz;

        node(T v, E p) : l(nullptr),r(nullptr),val(v),lazy(p),rev(false),sz(1) {}
    };

    int size(node* a) { return !a ? 0 : a->sz; }
    T val(node* a) { return !a ? M::dt() : (eval(a), a->val); }
    node* fix(node* a) {
        a->sz = size(a->l) + 1 + size(a->r);
        a->val = M::f(val(a->l), a->val, val(a->r));
        return a;
    }
    void eval(node* a) {
        if(a->lazy != M::de()) {
            a->val = M::g(a->val, a->lazy, size(a));
            if(a->l) a->l->lazy = M::h(a->l->lazy, a->lazy);
            if(a->r) a->r->lazy = M::h(a->r->lazy, a->lazy);
            a->lazy = M::de();
        }
        if(a->rev) {
            swap(a->l, a->r);
            if(a->l) a->l->rev ^= 1;
            if(a->r) a->r->rev ^= 1;
            a->rev = false;
        }
    }

    inline int xor128() {
        static int x = 123456789, y = 362436069, z = 521288629, w = 88675123;
        int t;
        t = x ^ (x << 11); x = y; y = z; z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }

    node* merge(node *a, node *b) {
        if(!a) return b;
        if(!b) return a;
        eval(a); eval(b);
        if(xor128() % (size(a) + size(b)) < size(a)) {
            a->r = merge(a->r, b);
            if(a->r) a->r->p = a;
            return fix(a);
        } else {
            b->l = merge(a, b->l);
            if(b->l) b->l->p = b;
            return fix(b);
        }
    }
    // [0,k) [k,n)
    pair<node*, node*> split(node *a, int k) {
        if(!a) return pair<node*, node*>(nullptr, nullptr);
        eval(a);
        node *sl, *sr;
        if(k <= size(a->l)) {
            tie(sl, sr) = split(a->l, k);
            if(a->l) a->l->p = nullptr;
            a->l = sr;
            if(a->l) a->l->p = a;
            return pair<node*, node*>(sl, fix(a));
        }
        tie(sl, sr) = split(a->r, k - size(a->l) - 1);
        if(a->r) a->r->p = nullptr;
        a->r = sl;
        if(a->r) a->r->p = a;
        return pair<node*, node*>(fix(a), sr);
    }
    // 要素の挿入/削除
    void insert(node*& a, int k, const T& x) {
        node *sl, *sr;
        tie(sl, sr) = split(a, k);
        a = merge(sl, merge(new node(x, M::de()), sr));
    }
    T erase(node*& a, int k) {
        node *sl, *sr, *tl, *tr;
        tie(sl, sr) = split(a, k + 1);
        tie(tl, tr) = split(sl, k);
        a = merge(tl, sr);
        return val(tr);
    }
    // 点更新
    void update(node*& a, int k, const E& x) {
        node *sl, *sr, *tl, *tr;
        tie(sl, sr) = split(a, k + 1);
        tie(tl, tr) = split(sl, k);
        if(tr) tr->val = M::g(tr->val, x, size(tr));
        a = merge(merge(tl, tr), sr);
    }
    // 区間更新
    void update(node*& a, int l, int r, const E& m) {
        node *sl, *sr, *tl, *tr;
        tie(sl, sr) = split(a, r);
        tie(tl, tr) = split(sl, l);
        if(tr) tr->lazy = M::h(tr->lazy, m);
        a = merge(merge(tl, tr), sr);
    }
    // 点取得
    T get(node*& a, int k) {
        node *sl, *sr, *tl, *tr;
        tie(sl, sr) = split(a, k + 1);
        tie(tl, tr) = split(sl, k);
        T res = !tr ? M::dt() : tr->val;
        a = merge(merge(tl, tr), sr);
        return res;
    }
    // 区間クエリ
    T query(node*& a, int l, int r) {
        node *sl, *sr, *tl, *tr;
        tie(sl, sr) = split(a, r);
        tie(tl, tr) = split(sl, l);
        T res = !tr ? M::dt() : tr->val;
        a = merge(merge(tl, tr), sr);
        return res;
    }
    // 区間[l,r)の反転
    void reverse(node*& a, int l, int r) {
        node *sl, *sr, *tl, *tr;
        tie(sl, sr) = split(a, r);
        tie(tl, tr) = split(sl, l);
        if(tr) tr->rev ^= 1;
        a = merge(merge(tl, tr), sr);
    }
    // 頂点aが属する木の根を求める
    node* getroot(node *a) {
        if(!a->p) return a;
        return getroot(a->p);
    }
    // x以上の最小の位置
    int lower_bound(node *t, const T &x) {
        if(!t) return 0;
        if(x <= val(t)) return lower_bound(t->l, x);
        return lower_bound(t->r, x) + size(t->l) + 1;
    }
    // xより大きい最小の位置
    int upper_bound(node *t, const T &x) {
        if(!t) return 0;
        if(x < val(t)) return upper_bound(t->l, x);
        return upper_bound(t->r, x) + RBST<T>::size(t->l) + 1;
    }
    // xの個数
    int count(node *t, const T &x) {
        return upper_bound(t, x) - lower_bound(t, x);
    }
    // k番目の要素を求める
    T kth_element(node *t, int k) {
        if(k < RBST<T>::size(t->l)) return kth_element(t->l, k);
        if(k == RBST<T>::size(t->l)) return val(t);
        return kth_element(t->r, k - RBST<T>::size(t->l) - 1);
    }
    // 要素xを追加する
    void insert_key(node *&t, const T &x) {
        RBST<T>::insert(t, lower_bound(t, x), x);
    }
    // 要素xを消す
    void erase_key(node *&t, const T &x) {
        if(!count(t, x)) return;
        RBST<T>::erase(t, lower_bound(t, x));
    }
    // デバッグ用
    void debug(node* t) {
        if(t == nullptr) return;
        cerr << "{";
        debug(t->l);
        cerr << " " << t->val << " ";
        debug(t->r);
        cerr << "}";
    }
};

/*
struct update_min {
    using T = PII;
    using E = ll;
    static T dt() { return PII(INT_MAX, INT_MAX); }
    static constexpr E de() { return INT_MAX; }
    static T f(const T &l, const T &self, const T &r) {
        return PII(self.first, min({l.second, self.first, r.second}));
    }
    static T g(const T &a, const E &b, const int &sz) {
        return b == de() ? a : PII(b, b);
    }
    static E h(const E &a, const E &b) {
        return b == de() ? a : b;
    }
};
*/
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

