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
ostream &operator <<(ostream& out,const pair<S,T>& a){
    out<<'('<<a.first<<','<<a.second<<')'; return out;
}
template<class T>
ostream &operator <<(ostream& out,const vector<T>& a){
    out<<'['; for(T i: a) {out<<i<<',';} out<<']'; return out;
}

int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0}; // DRUL
const int INF = 1<<30;
const ll LLINF = 1LL<<60;
const ll MOD = 1000000007;

template<class T, class E=T>
struct RBST {
    using F = function<T(T,T)>;
    using G = function<T(T,E)>;
    using H = function<E(E,E)>;
    using P = function<E(E,int)>;

    const F f; const G g; const H h; const P p;
    const T dt; const E de;

    struct node {
        node *l, *r;
        T val, sum;
        E lazy;
        bool rev;
        int sz;

        node(T v, E p) : l(nullptr),r(nullptr),val(v),sum(v),lazy(p),rev(false),sz(1) {}
    };

    RBST(F f, T dt) :
        f(f), g(G()), h(H()), p(P()), dt(dt), de(E()) {}
    RBST(F f, G g, H h, P p, T dt, E de) :
        f(f), g(g), h(h), p(p), dt(dt), de(de) {}

    // 子を操作したあとに呼ぶ
    node* fix(node* a) {
        a->sz = size(a->l) + 1 + size(a->r);
        a->sum = f(f(sum(a->l), a->val), sum(a->r));
        return a;
    }
    // valとsumを操作したあとに呼ぶ
    void eval(node* a) {
        if(a->lazy != de) {
            a->val = g(a->val, a->lazy);
            a->sum = g(a->sum, p(a->lazy, a->sz));
            if(a->l != nullptr) a->l->lazy = h(a->l->lazy, a->lazy);
            if(a->r != nullptr) a->r->lazy = h(a->r->lazy, a->lazy);
            a->lazy = de;
        }
        if(a->rev) {
            std::swap(a->l, a->r);
            if(a->l != nullptr) a->l->rev ^= 1;
            if(a->r != nullptr) a->r->rev ^= 1;
            a->rev = false;
        }
    }
    T sum(node* a) { return a == nullptr ? dt : (eval(a), a->sum); }
    int size(node* a) { return a == nullptr ? 0 : a->sz; }

    inline int xor128() {
        static int x = 123456789, y = 362436069, z = 521288629, w = 88675123;
        int t;
        t = x ^ (x << 11); x = y; y = z; z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }

    node* merge(node* a, node* b) {
        if(a == nullptr) return b;
        if(b == nullptr) return a;
        eval(a); eval(b);
        if(xor128() % (size(a) + size(b)) < size(a)) {
            a->r = merge(a->r, b);
            return fix(a);
        } else {
            b->l = merge(a, b->l);
            return fix(b);
        }
    }
    // [0,k) [k,n)
    pair<node*, node*> split(node* a, int k) {
        if(a == nullptr) return pair<node*, node*>(nullptr, nullptr);
        eval(a);
        node *sl, *sr;
        if(k <= size(a->l)) {
            std::tie(sl, sr) = split(a->l, k);
            a->l = sr;
            return pair<node*, node*>(sl, fix(a));
        } else {
            std::tie(sl, sr) = split(a->r, k - size(a->l) - 1);
            a->r = sl;
            return pair<node*, node*>(fix(a), sr);
        }
    }
    // 要素の挿入/削除
    void insert(node*& a, int k, const T& x) {
        node *sl, *sr;
        std::tie(sl, sr) = split(a, k);
        a = merge(sl, merge(new node(x, de), sr));
    }
    T erase(node*& a, int k) {
        node *sl, *sr, *tl, *tr;
        std::tie(sl, sr) = split(a, k + 1);
        std::tie(tl, tr) = split(sl, k);
        a = merge(tl, sr);
        return tr->val;
    }
    // 点代入
    void set_element(node*& a, int k, const T& x) {
        node *sl, *sr, *tl, *tr;
        std::tie(sl, sr) = split(a, k + 1);
        std::tie(tl, tr) = split(sl, k);
        if(tr != nullptr) tr->val = tr->sum = x;
        a = merge(merge(tl, tr), sr);
    }
    // 区間更新
    void update(node*& a, int l, int r, const E& m) {
        node *sl, *sr, *tl, *tr;
        std::tie(sl, sr) = split(a, r);
        std::tie(tl, tr) = split(sl, l);
        if(tr != nullptr) tr->lazy = h(tr->lazy, m);
        a = merge(merge(tl, tr), sr);
    }
    // 点取得
    T get(node*& a, int k) {
        node *sl, *sr, *tl, *tr;
        std::tie(sl, sr) = split(a, k + 1);
        std::tie(tl, tr) = split(sl, k);
        T res = tr == nullptr ? dt : tr->val;
        a = merge(merge(tl, tr), sr);
        return res;
    }
    // 区間クエリ
    T query(node*& a, int l, int r) {
        node *sl, *sr, *tl, *tr;
        std::tie(sl, sr) = split(a, r);
        std::tie(tl, tr) = split(sl, l);
        T res = tr == nullptr ? dt : tr->sum;
        a = merge(merge(tl, tr), sr);
        return res;
    }
    // 区間[l,r)の反転
    void reverse(node*& a, int l, int r) {
        node *sl, *sr, *tl, *tr;
        std::tie(sl, sr) = split(a, r);
        std::tie(tl, tr) = split(sl, l);
        if(tr != nullptr) tr->rev ^= 1;
        a = merge(merge(tl, tr), sr);
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
    void dump(node *r, typename vector< T >::iterator &it) {
        if(!r) return;
        eval(r);
        dump(r->l, it);
        *it = r->val;
        dump(r->r, ++it);
    }
    vector<T> dump(node *r) {
        vector<T> v((size_t) size(r));
        auto it = begin(v);
        dump(r, it);
        return v;
    }
    // x以上の最小の位置
    int lower_bound(node *t, const T &x) {
        if(!t) return 0;
        if(x <= t->val) return lower_bound(t->l, x);
        return lower_bound(t->r, x) + size(t->l) + 1;
    }
};

template<class T>
struct OrderedMultiSet : RBST<T> {
    using node = typename RBST<T>::node;

    OrderedMultiSet() : RBST<T>([&](T x, T y) { return x; }, T()) {}

    // k番目の要素を求める
    T kth_element(node *t, int k) {
        if(k < RBST<T>::size(t->l)) return kth_element(t->l, k);
        if(k == RBST<T>::size(t->l)) return t->val;
        return kth_element(t->r, k - RBST<T>::size(t->l) - 1);
    }
    // 要素xを追加する
    virtual void insert_key(node *&t, const T &x) {
        RBST<T>::insert(t, lower_bound(t, x), x);
    }
    // 要素xを消す
    void erase_key(node *&t, const T &x) {
        if(!count(t, x)) return;
        RBST<T>::erase(t, lower_bound(t, x));
    }
    // xの個数
    int count(node *t, const T &x) {
        return upper_bound(t, x) - lower_bound(t, x);
    }
    // x以上の最小の位置
    int lower_bound(node *t, const T &x) {
        if(!t) return 0;
        if(x <= t->val) return lower_bound(t->l, x);
        return lower_bound(t->r, x) + RBST<T>::size(t->l) + 1;
    }
    // xより大きい最小の位置
    int upper_bound(node *t, const T &x) {
        if(!t) return 0;
        if(x < t->val) return upper_bound(t->l, x);
        return upper_bound(t->r, x) + RBST<T>::size(t->l) + 1;
    }
};
template<class T>
struct OrderedSet : OrderedMultiSet<T>  {
    using SET = OrderedMultiSet<T>;
    using RBST = typename SET::RBST;
    using node = typename RBST::node;

    OrderedSet(int sz) : OrderedMultiSet<T>(sz) {}

    void insert_key(node *&t, const T &x) override {
        if(SET::count(t, x)) return;
        RBST::insert(t, SET::lower_bound(t, x), x);
    }
};

// k-th element
namespace ARC033C {
    void solve() {
        ll q;
        cin >> q;
        OrderedMultiSet<ll> st;
        OrderedMultiSet<ll>::RBST::node *root = nullptr;
        while(q--) {
            ll t, x;
            cin >> t >> x;
            if(t == 1) {
                st.insert_key(root, x);
            } else {
                ll val = st.kth_element(root, x-1);
                cout << val << endl;
                st.erase_key(root, val);
            }
        }
    }
}

// 点更新区間最小
namespace DSL2A {
    void solve() {
        int n, q;
        cin >> n >> q;

        auto f = [](ll l, ll r) { return min(l, r); };
        RBST<ll> tree(f, INT_MAX);

        RBST<ll,ll>::node* root = nullptr;
        for(int i = 0; i < n; i++) tree.insert(root, i, INT_MAX);
        while(q--) {
            int c, x, y;
            cin >> c >> x >> y;
            if(c == 0) {
                tree.set_element(root, x, y);
            } else {
                cout << tree.query(root, x, y+1) << endl;
            }
        }
    }
}

// 点加算区間和
namespace DSL2B {
    void solve() {
        int n, q;
        cin >> n >> q;

        auto f = [](ll l, ll r) { return l+r; };
        RBST<ll> tree(f, 0);

        RBST<ll,ll>::node* root = nullptr;
        for(int i = 0; i < n; i++) tree.insert(root, i, 0);
        while(q--) {
            int c, x, y;
            cin >> c >> x >> y;
            if(c == 0) {
                x--;
                tree.set_element(root, x, tree.get(root, x) + y);
            } else {
                x--, y--;
                cout << tree.query(root, x, y+1) << endl;
            }
        }
    }
}

// 区間更新区間最小
namespace DSL2F {
    void solve() {
        int n, q;
        cin >> n >> q;

        auto f = [](ll l, ll r) { return min(l, r); };
        auto g = [](ll l, ll r) { return r; };
        auto p = [](ll l, int r) { return l; };
        RBST<ll,ll> tree(f, g, g, p, INT_MAX, INT_MAX);

        RBST<ll,ll>::node* root = nullptr;
        for(int i = 0; i < n; i++) tree.insert(root, i, INT_MAX);
        while(q--) {
            int c, s, t;
            cin >> c >> s >> t;
            if(c == 0) {
                int x;
                cin >> x;
                tree.update(root, s, t + 1, x);
            } else {
                cout << tree.query(root, s, t + 1) << endl;
            }
        }
    }
}

// 区間加算区間和
namespace DSL2G {
    void solve() {
        int n, q;
        cin >> n >> q;

        auto f = [](ll l, ll r) { return l+r; };
        auto p = [](ll l, int r) { return l*r; };
        RBST<ll,ll> tree(f, f, f, p, 0, 0);

        RBST<ll,ll>::node* root = nullptr;
        for(int i = 0; i < n; i++) tree.insert(root, i, 0);
        while(q--) {
            int c, s, t;
            cin >> c >> s >> t;
            s--, t--;
            if(c == 0) {
                int x;
                cin >> x;
                tree.update(root, s, t + 1, x);
            } else {
                cout << tree.query(root, s, t + 1) << endl;
            }
        }
    }
}

// 区間加算区間最小
namespace DSL2H {
    void solve() {
        int n, q;
        cin >> n >> q;

        auto f = [](ll l, ll r) { return min(l, r); };
        auto g = [](ll l, ll r) { return l+r; };
        auto p = [](ll l, int r) { return l; };
        RBST<ll,ll> tree(f, g, g, p, INT_MAX, 0);

        RBST<ll,ll>::node* root = nullptr;
        for(int i = 0; i < n; i++) tree.insert(root, i, 0);
        while(q--) {
            int c, s, t;
            cin >> c >> s >> t;
            if(c == 0) {
                int x;
                cin >> x;
                tree.update(root, s, t+1, x);
            } else {
                cout << tree.query(root, s, t+1) << endl;
            }
        }
    }
}

// 区間更新区間和
namespace DSL2I {
    void solve() {
        int n, q;
        cin >> n >> q;

        auto f = [](ll l, ll r) { return l+r; };
        auto g = [](ll l, ll r) { return r==INT_MAX?l:r; };
        auto p = [](ll l, int r) { return l*r; };
        RBST<ll,ll> tree(f, g, g, p, 0, INT_MAX);

        RBST<ll,ll>::node* root = nullptr;
        for(int i = 0; i < n; i++) tree.insert(root, i, 0);
        while(q--) {
            int c, s, t;
            cin >> c >> s >> t;
            if(c == 0) {
                int x;
                cin >> x;
                tree.update(root, s, t+1, x);
            } else {
                cout << tree.query(root, s, t+1) << endl;
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    // ARC033C::solve();
    // DSL2A::solve();
    // DSL2B::solve();
    // DSL2F::solve();
    // DSL2G::solve();
    // DSL2H::solve();
    DSL2I::solve();

    return 0;
}
