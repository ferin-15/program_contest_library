// BEGIN CUT
template<typename M>
class LinkCutTree {
public:
    using T = typename M::T;
    using E = typename M::E;

    struct node {
        int sz, idx;
        T val, sum;
        E lazy;
        node *left, *right, *par;
        bool rev;
        node(int idx) : sz(1), idx(idx), val(M::T0()), sum(M::T0()), lazy(M::E0()),
            left(nullptr), right(nullptr), par(nullptr), rev(false) {}
        node(T _val, int idx) : sz(1), idx(idx), val(_val), sum(_val), lazy(M::E0()),
            left(nullptr), right(nullptr), par(nullptr), rev(false) {}
        inline bool isRoot() const {
            return (!par) || (par->left != this && par->right != this);
        }
        void push() {
            if(lazy != M::E0()) {
                val = M::g(val, lazy, 1), sum = M::g(sum, lazy, sz);
                if(left) left->lazy = M::h(left->lazy, lazy);
                if(right) right->lazy = M::h(right->lazy, lazy);
                lazy = M::E0();
            }
            if(rev) {
                swap(left, right);
                sum = M::s(sum);
                if(left) left->rev ^= true;
                if(right) right->rev ^= true;
                rev = false;
            }
        }
        void eval() {
            sz = 1, sum = val;
            if(left) left->push(), sz += left->sz, sum = M::f(left->sum, sum);
            if(right) right->push(), sz += right->sz, sum = M::f(sum, right->sum);
        }
    };
 
private:
    void rotate(node *u, bool right) {
        node *p = u->par, *g = p->par;
        if(right) {
            if((p->left = u->right)) u->right->par = p;
            u->right = p, p->par = u;
        } else {
            if((p->right = u->left)) u->left->par = p;
            u->left = p, p->par = u;
        }
        p->eval(), u->eval(), u->par = g;
        if(!g) return;
        if(g->left == p) g->left = u;
        if(g->right == p) g->right = u;
        g->eval();
    }
    // uをsplay木の根にする
    void splay(node *u) {
        while(!u->isRoot()) {
            node *p = u->par, *gp = p->par;
            if(p->isRoot()) { // zig
                p->push(), u->push();
                rotate(u, (u == p->left));
            } else {
                gp->push(), p->push(), u->push();
                bool flag = (u == p->left);
                if((u == p->left) == (p == gp->left)) { // zig-zig
                    rotate(p, flag), rotate(u, flag);
                } else { // zig-zag
                    rotate(u, flag), rotate(u, !flag);
                }
            }
        }
        u->push();
    }
    // 頂点uから根へのパスをつなげる
    node* expose(node *u) {
        node *last = nullptr;
        for(node *v = u; v; v = v->par) {
            splay(v);
            v->right = last;
            v->eval();
            last = v;
        }
        splay(u);
        return last;
    }
    void evert(node *u) {
        expose(u), u->rev = !(u->rev), u->push();
    }
    bool connected(node *u, node *v) {
        expose(u), expose(v);
        return u == v || u->par;
    }
    void link(node *u, node *v) {
        evert(u), u->par = v;
    }
    void cut(node *u) { // uと親の辺を切る
        expose(u), u->left->par = nullptr, u->left = nullptr, u->eval();
    }
    void cut(node *u, node *v) {
        expose(u), expose(v);
        if(u->isRoot()) u->par = nullptr;
        else v->left->par = nullptr, v->left = nullptr, v->eval();
    }
    node* lca(node *u, node *v) {
        expose(u);
        return expose(v);
    }
    int depth(node *u) {
        expose(u);
        return u->sz - 1;
    }
    void toRoot_range(node *u, const E x) {
        expose(u);
        u->lazy = M::h(u->lazy, x), u->push();
    }
    void range(node *u, node *v, const E x) {
        evert(u), expose(v);
        v->lazy = M::h(v->lazy, x), v->push();
    }
    void toRoot_query(node *u) {
        expose(u);
        return u->sum;
    }
    T query(node *u, node *v) {
        evert(u), expose(v);
        return v->sum;
    }
    node* get_kth(node *u, node *v, int k) {
        evert(v), expose(u);
        while(u) {
            u->eval();
            if(u->right && u->right->sz > k) u = u->right;
            else {
                if(u->right) k -= u->right->sz;
                if(k == 0) return u;
                k--;
                u = u->left;
            }
        }
        return nullptr;
    }
 
public:
    const int n;
    node** arr;
    LinkCutTree(const vector<T> &v) : n(v.size()) { 
        arr = new node*[n];
        REP(i, n) arr[i] = new node(v[i], i);
    }
    ~LinkCutTree(){
        REP(i, n) delete arr[i];
        delete[] arr;
    }
    bool connected(int id1, int id2) { return connected(arr[id1], arr[id2]); }
    void link(int id1, int id2) { return link(arr[id1], arr[id2]); }
    void cut(int id) { return cut(arr[id]); } // uと親の辺を切る
    void cut(int id1, int id2) { return cut(arr[id1], arr[id2]); }
    int lca(int id1, int id2) { return lca(arr[id1], arr[id2])->idx; }
    void evert(int id) { return evert(arr[id]); }
    int depth(int id) { return depth(arr[id]); }
    void toRoot_range(int id, const E x) { return toRoot_range(arr[id], x); }
    void range(int id1, int id2, const E x) { return range(arr[id1], arr[id2], x); }
    T toRoot_query(int id) { return toRoot_query(arr[id]); }
    T query(int id1, int id2) { return query(arr[id1], arr[id2]); }
    int get_kth(int id1, int id2, int k) {
        node *u = get_kth(arr[id1], arr[id2], k);
        return !u ? -1 : u->idx;
    }
};

/*
struct monoid {
    using T = ll;
    using E = ll;
    static T T0() { return 0; }
    static constexpr E E0() { return 0; }
    static T f(const T &x, const T &y) { return x+y; }
    static T g(const T &x, const E &y, int sz) { return x + y*sz; }
    static E h(const E &x, const E &y) { return x+y; }
    static T s(const T &x) { return x; }
};
*/
// END CUT