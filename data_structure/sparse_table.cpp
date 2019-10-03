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

template <typename S>
struct sparseTable {
    using T = typename S::T;
    int n;
    vector<int> log2;
    vector<vector<T>> t;

    sparseTable(int nn) {
        n = nn;
        log2.assign(n+1, 0);
        for(int i=2; i<=n; ++i) log2[i] = log2[i >> 1] + 1;
        t = vector<vector<T>>(log2[n]+1, vector<T>(n));
    }
    void init(vector<T> v) {
        for(int i=0; i<n; ++i) t[0][i] = v[i];
        for(int j=1; j<=log2[n]; ++j) {
            int w = 1LL<<(j-1);
            for (int i = 0; i+(w<<1) <= n; ++i) {
                t[j][i] = S::op(t[j-1][i], t[j-1][i+w]);
            }
        }
    }
    // [l, r]
    T query(int l, int r) {
        int j = log2[r - l];
        return S::op(t[j][l], t[j][r-(1 << j)+1]);
    }
};

// 集合T、結合則・可換・冪等律が成り立つ二項演算op
struct minnimum {
    using T = ll;
    static T op(const T& a, const T& b) { return min(a, b); }
};
struct maximum {
    using T = ll;
    static T op(const T& a, const T& b) { return max(a, b); }
};
struct gcd_op {
    using T = ll;
    static T op(const T& a, const T& b) { return __gcd(a, b); }
};
