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


# :warning: oldcode/beats_example.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#bf50ccff88ac9b2562bee63cf804278c">oldcode</a>
* <a href="{{ site.github.repository_url }}/blob/master/oldcode/beats_example.cpp">View this file on GitHub</a>
    - Last commit date: 2019-10-03 22:20:29+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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

template<typename Monoid>
struct segtreebeats {
    using T = typename Monoid::T;
    using E = typename Monoid::E;
    ll n;
    vector<T> dat;
    vector<E> lazy;

    segtreebeats() {}
    segtreebeats(int n_) {
        n = 1; while(n < n_) n *= 2;
        dat.assign(n*2-1, Monoid::dt());
        lazy.assign(n*2-1, Monoid::de());
    }
    void build(vector<T> v) {
        REP(i, v.size()) dat[i+n] = v[i];
        for(int i=n-1; i>0; --i) dat[i] = Monoid::f(dat[i*2], dat[i*2+1]);
    }

    void eval(int k) {
        if(lazy[k] == Monoid::de()) return;
        dat[k] = Monoid::g(dat[k], lazy[k]);
        if(k*2+1 < n*2-1) {
            lazy[2*k+1] = Monoid::h(lazy[2*k+1], lazy[k]);
            lazy[2*k+2] = Monoid::h(lazy[2*k+2], lazy[k]);
        }
        lazy[k] = Monoid::de();
    }

    T query(int a, int b, int k, int l, int r) {
        eval(k);
        if(b <= l || r <= a) return Monoid::dt();
        if(a <= l && r <= b) return dat[k];
        int m=(l+r)>>1;
        T vl = query(a, b, 2*k+1, l, m);
        T vr = query(a, b, 2*k+2, m, r);
        return Monoid::f(vl, vr);
    }
    T query(int a, int b) { return query(a, b, 0, 0, n); }

    void update(int a, int b, E x, int k, int l, int r) {
        if(b <= l || r <= a) return;
        if(a <= l && r <= b) {
            lazy[k] = Monoid::h(lazy[k], x);
            eval(k);
            return;
        }
        eval(k);
        int m = (l+r)>>1;
        update(a, b, x, 2*k+1, l, m);
        update(a, b, x, 2*k+2, m, r);
        dat[k] = Monoid::f(dat[2*k+1], dat[2*k+2]);
    }
    void update(int a, int b, E x) { update(a, b, x, 0, 0, n); }

    void update_div(int a, int b, ll x, int k, int l, int r) {
        if(b <= l || r <= a || dat[k].max < x) return;
        if(a <= l && r <= b && dat[k].max == dat[k].min) {
            lazy[k] = Monoid::h(lazy[k], PII(0, dat[k].max/x));
            eval(k);
            return;
        }
        eval(k);
        int m = (l+r)>>1;
        update_mod(a, b, x, 2*k+1, l, m);
        update_mod(a, b, x, 2*k+2, m, r);
        dat[k] = Monoid::f(dat[2*k+1], dat[2*k+2]);
    }
    void update_div(int a, int b, ll x) { update_div(a, b, x, 0, 0, n); }

    void update_mod(int a, int b, ll x, int k, int l, int r) {
        if(b <= l || r <= a || dat[k].max < x) return;
        if(a <= l && r <= b && dat[k].max == dat[k].min) {
            lazy[k] = Monoid::h(lazy[k], PII(0, dat[k].max%x));
            eval(k);
            return;
        }
        eval(k);
        int m = (l+r)>>1;
        update_mod(a, b, x, 2*k+1, l, m);
        update_mod(a, b, x, 2*k+2, m, r);
        dat[k] = Monoid::f(dat[2*k+1], dat[2*k+2]);
    }
    void update_mod(int a, int b, ll x) { update_mod(a, b, x, 0, 0, n); }

    void update_gcd(int a, int b, ll x, int k, int l, int r) {
        if(b <= l || r <= a || x%dat[k].lcm==0) return;
        if(a <= l && r <= b && dat[k].max == dat[k].min) {
            lazy[k] = Monoid::h(lazy[k], PII(0, __gcd(dat[k].max, x)));
            eval(k);
            return;
        }
        eval(k);
        int m = (l+r)>>1;
        update_gcd(a, b, x, 2*k+1, l, m);
        update_gcd(a, b, x, 2*k+2, m, r);
        dat[k] = Monoid::f(dat[2*k+1], dat[2*k+2]);
    }
    void update_gcd(int a, int b, ll x) { update_gcd(a, b, x, 0, 0, n); }
};

struct node {
    ll sum, max, min, lcm, len;
    node() : sum(0), max(-LLINF), min(LLINF), lcm(1), len(0) {}
    node(ll v) : sum(v), max(v), min(v), lcm(v), len(1) {}
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
// nodeとfとupdate_*の中身を問題に応じて書き換える

signed main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    REP(i, n) cin >> a[i];

    segtreebeats<linear_exp> seg(n);
    vector<node> va(n);
    REP(i, n) va[i] = node(a[i]);
    seg.build(va);

    while(q--) {
        ll type;
        cin >> type;
        if(type == 1) {
            ll l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            seg.update(l, r+1, PII(0, x));
        } else if(type == 2) {
            ll l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            seg.update_gcd(l, r+1, x);
        } else if(type == 3) {
            ll l, r;
            cin >> l >> r;
            l--, r--;
            cout << seg.query(l, r+1).max << endl;
        } else if(type == 4) {
            ll l, r;
            cin >> l >> r;
            l--, r--;
            cout << seg.query(l, r+1).sum << endl;
        }
    }

    return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "oldcode/beats_example.cpp"
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

template<typename Monoid>
struct segtreebeats {
    using T = typename Monoid::T;
    using E = typename Monoid::E;
    ll n;
    vector<T> dat;
    vector<E> lazy;

    segtreebeats() {}
    segtreebeats(int n_) {
        n = 1; while(n < n_) n *= 2;
        dat.assign(n*2-1, Monoid::dt());
        lazy.assign(n*2-1, Monoid::de());
    }
    void build(vector<T> v) {
        REP(i, v.size()) dat[i+n] = v[i];
        for(int i=n-1; i>0; --i) dat[i] = Monoid::f(dat[i*2], dat[i*2+1]);
    }

    void eval(int k) {
        if(lazy[k] == Monoid::de()) return;
        dat[k] = Monoid::g(dat[k], lazy[k]);
        if(k*2+1 < n*2-1) {
            lazy[2*k+1] = Monoid::h(lazy[2*k+1], lazy[k]);
            lazy[2*k+2] = Monoid::h(lazy[2*k+2], lazy[k]);
        }
        lazy[k] = Monoid::de();
    }

    T query(int a, int b, int k, int l, int r) {
        eval(k);
        if(b <= l || r <= a) return Monoid::dt();
        if(a <= l && r <= b) return dat[k];
        int m=(l+r)>>1;
        T vl = query(a, b, 2*k+1, l, m);
        T vr = query(a, b, 2*k+2, m, r);
        return Monoid::f(vl, vr);
    }
    T query(int a, int b) { return query(a, b, 0, 0, n); }

    void update(int a, int b, E x, int k, int l, int r) {
        if(b <= l || r <= a) return;
        if(a <= l && r <= b) {
            lazy[k] = Monoid::h(lazy[k], x);
            eval(k);
            return;
        }
        eval(k);
        int m = (l+r)>>1;
        update(a, b, x, 2*k+1, l, m);
        update(a, b, x, 2*k+2, m, r);
        dat[k] = Monoid::f(dat[2*k+1], dat[2*k+2]);
    }
    void update(int a, int b, E x) { update(a, b, x, 0, 0, n); }

    void update_div(int a, int b, ll x, int k, int l, int r) {
        if(b <= l || r <= a || dat[k].max < x) return;
        if(a <= l && r <= b && dat[k].max == dat[k].min) {
            lazy[k] = Monoid::h(lazy[k], PII(0, dat[k].max/x));
            eval(k);
            return;
        }
        eval(k);
        int m = (l+r)>>1;
        update_mod(a, b, x, 2*k+1, l, m);
        update_mod(a, b, x, 2*k+2, m, r);
        dat[k] = Monoid::f(dat[2*k+1], dat[2*k+2]);
    }
    void update_div(int a, int b, ll x) { update_div(a, b, x, 0, 0, n); }

    void update_mod(int a, int b, ll x, int k, int l, int r) {
        if(b <= l || r <= a || dat[k].max < x) return;
        if(a <= l && r <= b && dat[k].max == dat[k].min) {
            lazy[k] = Monoid::h(lazy[k], PII(0, dat[k].max%x));
            eval(k);
            return;
        }
        eval(k);
        int m = (l+r)>>1;
        update_mod(a, b, x, 2*k+1, l, m);
        update_mod(a, b, x, 2*k+2, m, r);
        dat[k] = Monoid::f(dat[2*k+1], dat[2*k+2]);
    }
    void update_mod(int a, int b, ll x) { update_mod(a, b, x, 0, 0, n); }

    void update_gcd(int a, int b, ll x, int k, int l, int r) {
        if(b <= l || r <= a || x%dat[k].lcm==0) return;
        if(a <= l && r <= b && dat[k].max == dat[k].min) {
            lazy[k] = Monoid::h(lazy[k], PII(0, __gcd(dat[k].max, x)));
            eval(k);
            return;
        }
        eval(k);
        int m = (l+r)>>1;
        update_gcd(a, b, x, 2*k+1, l, m);
        update_gcd(a, b, x, 2*k+2, m, r);
        dat[k] = Monoid::f(dat[2*k+1], dat[2*k+2]);
    }
    void update_gcd(int a, int b, ll x) { update_gcd(a, b, x, 0, 0, n); }
};

struct node {
    ll sum, max, min, lcm, len;
    node() : sum(0), max(-LLINF), min(LLINF), lcm(1), len(0) {}
    node(ll v) : sum(v), max(v), min(v), lcm(v), len(1) {}
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
// nodeとfとupdate_*の中身を問題に応じて書き換える

signed main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    REP(i, n) cin >> a[i];

    segtreebeats<linear_exp> seg(n);
    vector<node> va(n);
    REP(i, n) va[i] = node(a[i]);
    seg.build(va);

    while(q--) {
        ll type;
        cin >> type;
        if(type == 1) {
            ll l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            seg.update(l, r+1, PII(0, x));
        } else if(type == 2) {
            ll l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            seg.update_gcd(l, r+1, x);
        } else if(type == 3) {
            ll l, r;
            cin >> l >> r;
            l--, r--;
            cout << seg.query(l, r+1).max << endl;
        } else if(type == 4) {
            ll l, r;
            cin >> l >> r;
            l--, r--;
            cout << seg.query(l, r+1).sum << endl;
        }
    }

    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

