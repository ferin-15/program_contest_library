template<typename KEY, typename SUM>
class LinkCutTreeForSubTree {
public:
    struct node {
        int sz, idx;
        KEY key;
        SUM sum;
        node *left, *right, *par;
        bool rev;
        node(int idx, KEY key = KEY()) : sz(1), idx(idx), key(key), sum(SUM()), 
            left(nullptr), right(nullptr), par(nullptr), rev(false) {}
        inline bool isRoot() const {
            return (!par) || (par->left != this && par->right != this);
        }
        void push() {
            if(rev) {
                swap(left, right);
                sum.toggle();
                if(left) left->rev ^= true;
                if(right) right->rev ^= true;
                rev = false;
            }
        }
        void eval() {
            sz = 1;
            if(left) sz += left->sz; 
            if(right) sz += right->sz;
            sum.merge(key, left?left->sum:SUM(), right?right->sum:SUM());
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
            if(v->right) v->sum.add(v->right->sum);
            v->right = last;
            if(v->right) v->sum.erase(v->right->sum);
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
        expose(u);
        expose(v);
        u->par = v;
        v->right = u;
        v->eval();
    }
    void cut(node *u) { // uと親の辺を切る
        expose(u);
        node *par = u->l;
        u->l = nullptr;
        par->par = nullptr;
        u->eval();
    }
    node* lca(node *u, node *v) {
        expose(u);
        return expose(v);
    }
    int depth(node *u) {
        expose(u);
        return u->sz - 1;
    }
    template<typename G>
    node* update(node *u, const KEY &key, G g) {
        expose(u);
        u->key = g(u->key, key);
        u->eval();
        return u;
    }
    SUM query(node *u, node *v) {
        evert(u), expose(v);
        return v->sum;
    }
    SUM query(node *u) {
        expose(u);
        return u->sum;
    }
    node* get_kth(node *u, node *v, int k) {
        evert(v), expose(u);
        while(u) {
            push(u);
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
    LinkCutTreeForSubTree(const vector<KEY> &v) : n(v.size()) { 
        arr = new node*[n];
        REP(i, n) arr[i] = new node(i, v[i]);
    }
    ~LinkCutTreeForSubTree(){
        REP(i, n) delete arr[i];
        delete[] arr;
    }
    bool connected(int id1, int id2) { return connected(arr[id1], arr[id2]); }
    void link(int id1, int id2) { return link(arr[id1], arr[id2]); }
    void cut(int id) { return cut(arr[id]); } // uと親の辺を切る
    int lca(int id1, int id2) { return lca(arr[id1], arr[id2])->idx; }
    void evert(int id) { return evert(arr[id]); }
    int depth(int id) { return depth(arr[id]); }
    template<typename G>
    int update(int id, const KEY &key, G g) { return update(arr[id], key, g)->idx; }
    SUM query(int id1, int id2) { return query(arr[id1], arr[id2]); }   // パス
    SUM query(int id) { return query(arr[id]); } // 部分木
    int get_kth(int id1, int id2, int k) {
        node *u = get_kth(arr[id1], arr[id2], k);
        return !u ? -1 : u->idx;
    }
};

/*
struct SUM {
    ll dat, sum, laz;
    SUM() : dat(0), sum(0), laz(0) {}
    void toggle() {}
    void merge(ll key, const SUM &left, const SUM &right) {
        dat = left.dat + key + right.dat;
        sum = dat + laz;
    }
    void add(const SUM &ch) { laz += ch.sum; }
    void erase(const SUM &ch) { laz -= ch.sum; }
};
*/