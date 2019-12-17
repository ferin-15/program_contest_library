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
ostream &operator <<(ostream& out,const pair<S,T>& a) {
    out<<'('<<a.first<<','<<a.second<<')'; return out;
}
template<class T>
ostream &operator <<(ostream& out,const vector<T>& a){
    out<<'[';
    for(const T &i: a) out<<i<<',';
    out<<']';
    return out;
}
template<class T>
ostream &operator <<(ostream& out, const set<T>& a) {
    out<<'{';
    for(const T &i: a) out<<i<<',';
    out<<'}';
    return out;
}
template<class T, class S>
ostream &operator <<(ostream& out, const map<T,S>& a) {
    out<<'{';
    for(auto &i: a) out<<i<<',';
    out<<'}';
    return out;
}

int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0}; // DRUL
const int INF = 1<<30;
const ll LLINF = 1LL<<60;
const ll MOD = 1000000007;

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
    node() : sum(0), max(-LLINF), min(LLINF), len(0) {}
    node(ll a, ll b, ll c, ll d) : sum(a), max(b), min(c), len(d) {}
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
struct xor_sum {
    using T = PII;  // (頂点の値, 頂点の区間長)
    using E = ll;
    static constexpr T dt() { return PII(0,0); }
    static constexpr E de() { return 0; }
    static T f(const T &a, const T &b) { return PII(a.first+b.first, a.second+b.second); }
    static T g(const T &a, const E &b) { return PII((b>=1?b-a.first:a.first)*a.second, a.second); }
    static E h(const E &a, const E &b) { return a^b; }
};

// 区間更新区間最小
namespace DSL2F {
    void solve() {
        int n, q;
        cin >> n >> q;

        lazysegtree<linear_exp> seg(n);
        seg.build(vector<node>(n, node(INT_MAX,INT_MAX,INT_MAX,1)));
        while(q--) {
            int c, s, t;
            cin >> c >> s >> t;
            if(c == 0) {
                int x;
                cin >> x;
                seg.update(s, t + 1, PII(0, x));
            } else {
                cout << seg.query(s, t + 1).min << endl;
            }
        }
    }
}

// 区間加算区間和
namespace DSL2G {
    void solve() {
        int n, q;
        cin >> n >> q;

        lazysegtree<linear_exp> seg(n);
        seg.build(vector<node>(n, node(0,0,0,1)));
        while(q--) {
            int c, s, t;
            cin >> c >> s >> t;
            s--, t--;
            if(c == 0) {
                int x;
                cin >> x;
                seg.update(s, t + 1, PII(1, x));
            } else {
                cout << seg.query(s, t + 1).sum << endl;
            }
        }
    }
}

// 区間加算区間最小
namespace DSL2H {
    void solve() {
        int n, q;
        cin >> n >> q;

        lazysegtree<linear_exp> seg(n);
        seg.build(vector<node>(n, node(0, 0, 0, 1)));
        while(q--) {
            int c, s, t;
            cin >> c >> s >> t;
            if(c == 0) {
                int x;
                cin >> x;
                seg.update(s, t+1, PII(1, x));
            } else {
                cout << seg.query(s, t+1).min << endl;
            }
        }
    }
}

// 区間更新区間和
namespace DSL2I {
    void solve() {
        int n, q;
        cin >> n >> q;

        lazysegtree<linear_exp> seg(n);
        seg.build(vector<node>(n, node(0, 0, 0, 1)));
        while(q--) {
            int c, s, t;
            cin >> c >> s >> t;
            if(c == 0) {
                int x;
                cin >> x;
                seg.update(s, t+1, PII(0, x));
            } else {
                cout << seg.query(s, t+1).sum << endl;
            }
        }
    }
}
