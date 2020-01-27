template<class M>
struct RBST {
    using T = typename M::T;
    using E = typename M::E;

    struct node {
        node *l, *r, *p;
        T val, sum;
        E lazy;
        bool rev;
        int sz;

        node(T v, E p) : l(nullptr),r(nullptr),val(v),sum(v),lazy(p),rev(false),sz(1) {}
    };

    RBST() {}

    int size(node* a) { return !a ? 0 : a->sz; }
    T sum(node* a) { return !a ? M::dt() : (eval(a), a->sum); }
    node* fix(node* a) {
        a->sz = size(a->l) + 1 + size(a->r);
        a->sum = M::f(M::f(sum(a->l), a->val), sum(a->r));
        return a;
    }
    void eval(node* a) {
        if(a->lazy != M::de()) {
            a->val = M::g(a->val, a->lazy);
            a->sum = M::g(a->sum, M::p(a->lazy, a->sz));
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
            a->l = sr;
            if(a->l) a->l->p = a;
            if(sl) sl->p = nullptr;
            return pair<node*, node*>(sl, fix(a));
        }
        tie(sl, sr) = split(a->r, k - size(a->l) - 1);
        a->r = sl;
        if(a->r) a->r->p = a;
        if(sr) sr->p = nullptr;
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
        return tr->val;
    }
    // 点代入
    void set_element(node*& a, int k, const T& x) {
        node *sl, *sr, *tl, *tr;
        tie(sl, sr) = split(a, k + 1);
        tie(tl, tr) = split(sl, k);
        if(tr) tr->val = tr->sum = x;
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
        T res = !tr ? M::dt() : tr->sum;
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
    // デバッグ用
    void debug(node* t) {
        if(t == nullptr) return;
        cout << "{";
        debug(t->l);
        cout << " " << t->val << " ";
        debug(t->r);
        cout << "}";
    }
    // x以上の最小の位置
    int lower_bound(node *t, const T &x) {
        if(!t) return 0;
        if(x <= t->val) return lower_bound(t->l, x);
        return lower_bound(t->r, x) + size(t->l) + 1;
    }
    // xより大きい最小の位置
    int upper_bound(node *t, const T &x) {
        if(!t) return 0;
        if(x < t->val) return upper_bound(t->l, x);
        return upper_bound(t->r, x) + RBST<T>::size(t->l) + 1;
    }
    // xの個数
    int count(node *t, const T &x) {
        return upper_bound(t, x) - lower_bound(t, x);
    }
    // k番目の要素を求める
    T kth_element(node *t, int k) {
        if(k < RBST<T>::size(t->l)) return kth_element(t->l, k);
        if(k == RBST<T>::size(t->l)) return t->val;
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
};

/*
struct add_sum {
    using T = ll;
    using E = ll;
    static T dt() { return 0; }
    static constexpr E de() { return 0; }
    static T f(const T &a, const T &b) {
        return a+b;
    }
    static T g(const T &a, const E &b) {
        return a+b;
    }
    static E h(const E &a, const E &b) {
        return a+b;
    }
    static E p(const E &a, const int &b) {
        return a*b;
    } 
};
*/