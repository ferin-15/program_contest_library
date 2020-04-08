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


# :heavy_check_mark: test/GRL5D.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/GRL5D.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-08 16:27:33+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_D">https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_D</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/lazysegtree.cpp.html">data_structure/lazysegtree.cpp</a>
* :heavy_check_mark: <a href="../../library/graph/hld.cpp.html">graph/hld.cpp</a>
* :heavy_check_mark: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_D"
#include "../memo/macro.hpp"
#include "../graph/hld.cpp"
#include "../data_structure/lazysegtree.cpp"

signed main(void) {
    ll n;
    cin >> n;
    HLDecomposition hld(n);
    vector<ll> p(n, -1);
    REP(i, n) {
        ll k;
        cin >> k;
        REP(j, k) {
            ll c;
            cin >> c;
            hld.add_edge(i, c);
            p[c] = i;
        }
    }
    hld.build();

    lazysegtree<linear_exp> seg(n);
    vector<node> init(n);
    REP(i, n) init[i] = node(0);
    seg.build(init);

    ll q;
    cin >> q;
    while(q--) {
        ll type;
        cin >> type;
        if(type == 0) {
            ll v, w;
            cin >> v >> w;
            hld.for_each_edge(v, p[v], [&](ll a, ll b){
                seg.update(a, b+1, PII(1, w));
            });
        } else {
            ll v;
            cin >> v;
            ll ans = 0;
            hld.for_each_edge(v, 0, [&](ll a, ll b){
                ans += seg.query(a, b+1).sum;
            });
            cout << ans << endl;
        }
    }

    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/GRL5D.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_D"
#line 1 "memo/macro.hpp"
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
#line 1 "graph/hld.cpp"
// BEGIN CUT
class HLDecomposition {
    void dfs1(ll v, ll p) {
        if(g[v].size() && g[v][0]==p) swap(g[v][0], g[v].back());
        for(auto &to: g[v]) {
            if(to == p) continue;
            dfs1(to, v);
            sz[v] += sz[to];
            if(sz[to] > sz[g[v][0]]) swap(to, g[v][0]);
        }
    }
    void dfs2(ll v, ll p, ll &k) {
        par[v] = p; vid[v] = k++;
        for(auto to: g[v]) {
            if(to == p) continue;
            head[to] = (to == g[v][0] ? head[v] : to);
            dfs2(to, v, k);
        }
    }

public:
    int n;
    vector<vector<ll>> g;
    vector<ll> vid, head, sz, par;

    HLDecomposition(){}
    HLDecomposition(ll sz): n(sz), g(n), vid(n,-1), head(n), sz(n,1), par(n) {}

    void add_edge(ll u, ll v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void build(vector<ll> rs=vector<ll>(1,0)) {
        ll k = 0;
        for(ll r: rs) {
            dfs1(r, -1);
            head[r] = r;
            dfs2(r, -1, k);
        }
    }

    // パスu-vの頂点属性クエリ
    void for_each(ll u, ll v, const function<void(ll,ll)>& f) {
        while(1){
            if(vid[u]>vid[v]) swap(u,v);
            f(max(vid[head[v]], vid[u]), vid[v]); // 閉区間!!!
            if(head[u]!=head[v]) v = par[head[v]];
            else break;
        }
    }
    // パスu-vの辺属性クエリ
    void for_each_edge(ll u, ll v, const function<void(ll,ll)>& f) {
        while(1) {
            if(vid[u]>vid[v]) swap(u,v);
            if(head[u]!=head[v]) {
                f(vid[head[v]], vid[v]); // 閉区間!!!
                v = par[head[v]];
            } else {
                if(u!=v) f(vid[u]+1, vid[v]); // 閉区間!!!
                break;
            }
        }
    }
    ll lca(ll u, ll v) {
        while(1) {
            if(vid[u]>vid[v]) swap(u,v);
            if(head[u]==head[v]) return u;
            v = par[head[v]];
        }
    }
};
// 部分木 頂点クエリ → 区間[hld.vid[u]+1, hld.vid[u] + hld.sub[u])
// 部分木 辺クエリ → 区間[hld.vid[u]+1, hld.vid[u] + hld.sub[u])
// END CUT
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
#line 5 "test/GRL5D.test.cpp"

signed main(void) {
    ll n;
    cin >> n;
    HLDecomposition hld(n);
    vector<ll> p(n, -1);
    REP(i, n) {
        ll k;
        cin >> k;
        REP(j, k) {
            ll c;
            cin >> c;
            hld.add_edge(i, c);
            p[c] = i;
        }
    }
    hld.build();

    lazysegtree<linear_exp> seg(n);
    vector<node> init(n);
    REP(i, n) init[i] = node(0);
    seg.build(init);

    ll q;
    cin >> q;
    while(q--) {
        ll type;
        cin >> type;
        if(type == 0) {
            ll v, w;
            cin >> v >> w;
            hld.for_each_edge(v, p[v], [&](ll a, ll b){
                seg.update(a, b+1, PII(1, w));
            });
        } else {
            ll v;
            cin >> v;
            ll ans = 0;
            hld.for_each_edge(v, 0, [&](ll a, ll b){
                ans += seg.query(a, b+1).sum;
            });
            cout << ans << endl;
        }
    }

    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

