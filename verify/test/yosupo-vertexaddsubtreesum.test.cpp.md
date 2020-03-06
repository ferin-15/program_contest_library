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


# :heavy_check_mark: test/yosupo-vertexaddsubtreesum.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo-vertexaddsubtreesum.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00


* see: <a href="https://judge.yosupo.jp/problem/vertex_add_subtree_sum">https://judge.yosupo.jp/problem/vertex_add_subtree_sum</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/linkcuttree_subtree.cpp.html">data_structure/linkcuttree_subtree.cpp</a>
* :heavy_check_mark: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
#include "../memo/macro.hpp"
#include "../data_structure/linkcuttree_subtree.cpp"

int main(void) {
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    REP(i, n) cin >> a[i];
    
    struct SUM {
        ll ret, laz, all;
        SUM() : ret(0), laz(0), all(0) {}
        void toggle() {}
        void merge(ll key, const SUM &left, const SUM &right) {
            ret = laz + key + right.all;
            all = ret + left.all;
        }
        void add(const SUM &ch) { laz += ch.all; }
        void erase(const SUM &ch) { laz -= ch.all; }
    };
    LinkCutTreeForSubTree<ll,SUM> lct(a);

    REP(i, n-1) {
        ll p;
        cin >> p;
        lct.link(i+1, p);
    }
    while(q--) {
        ll t;
        cin >> t;
        if(t == 0) {
            ll u, x;
            cin >> u >> x;
            auto g = [](ll p, ll q) { return p+q; };
            lct.update(u, x, g);
        } else {
            ll u;
            cin >> u;
            cout << lct.query(u).ret << endl;
        }
    }

    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo-vertexaddsubtreesum.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
#line 1 "test/../memo/macro.hpp"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PII = pair<ll, ll>;
#define FOR(i, a, n) for (ll i = (ll)a; i < (ll)n; ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(x) x.begin(), x.end()
template<typename T> void chmin(T &a, const T &b) { a = min(a, b); }
template<typename T> void chmax(T &a, const T &b) { a = max(a, b); }
struct FastIO {FastIO() { cin.tie(0); ios::sync_with_stdio(0); }}fastiofastio;
const ll INF = 1LL<<60;
#line 1 "test/../data_structure/linkcuttree_subtree.cpp"
// BEGIN CUT
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
// END CUT
#line 4 "test/yosupo-vertexaddsubtreesum.test.cpp"

int main(void) {
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    REP(i, n) cin >> a[i];
    
    struct SUM {
        ll ret, laz, all;
        SUM() : ret(0), laz(0), all(0) {}
        void toggle() {}
        void merge(ll key, const SUM &left, const SUM &right) {
            ret = laz + key + right.all;
            all = ret + left.all;
        }
        void add(const SUM &ch) { laz += ch.all; }
        void erase(const SUM &ch) { laz -= ch.all; }
    };
    LinkCutTreeForSubTree<ll,SUM> lct(a);

    REP(i, n-1) {
        ll p;
        cin >> p;
        lct.link(i+1, p);
    }
    while(q--) {
        ll t;
        cin >> t;
        if(t == 0) {
            ll u, x;
            cin >> u >> x;
            auto g = [](ll p, ll q) { return p+q; };
            lct.update(u, x, g);
        } else {
            ll u;
            cin >> u;
            cout << lct.query(u).ret << endl;
        }
    }

    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

