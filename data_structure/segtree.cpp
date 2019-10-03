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

// 1-index !!!!!
template<typename Monoid>
struct segtree {
    using T = typename Monoid::T;
    int n;
    vector<T> dat;

    segtree(int n_) {
        n = 1;
        while(n < n_) n <<= 1;
        dat.assign(n*2, Monoid::id());
    }
    void build(vector<T> v) {
        REP(i, v.size()) dat[i+n] = v[i];
        for(int i=n-1; i>0; --i) dat[i] = Monoid::op(dat[i*2], dat[i*2+1]);
    }

    T query(int a, int b) {
        T l = Monoid::id(), r = Monoid::id();
        for(a+=n, b+=n; a<b; a>>=1, b>>=1) {
            if(a&1) l = Monoid::op(l, dat[a++]);
            if(b&1) r = Monoid::op(dat[--b], r);
        }
        return Monoid::op(l, r);
    }
    void update(int i, T v) {
        i += n;
        dat[i] = v;
        while(i >>= 1) {
            dat[i] = Monoid::op(dat[i*2], dat[i*2+1]);
        }
    }

    friend ostream &operator <<(ostream& out,const segtree<Monoid>& seg){
        out << "---------------------" << endl;
        int cnt = 1;
        for(int i=1; i<=seg.n; i*=2) {
            REP(j, i) {
                out << seg.dat[cnt] << " ";
                cnt++;
            }
            out << endl;
        }
        out << "---------------------" << endl;
        return out;
    }
};

template<typename Tp>
struct min_monoid {
    using T = Tp;
    static constexpr Tp id() { return INT_MAX; }
    static Tp op(const Tp &a, const Tp &b) { return min(a, b); }
};
template<typename Tp>
struct max_monoid {
    using T = Tp;
    static constexpr Tp id() { return -LLINF; }
    static Tp op(const Tp &a, const Tp &b) { return max(a, b); }
};
template<typename Tp>
struct sum_monoid {
    using T = Tp;
    static constexpr Tp id() { return 0; }
    static Tp op(const Tp &a, const Tp &b) { return a+b; }
};
