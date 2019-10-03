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

struct segTreeRangeFreq {
    int n;
    vector<vector<ll>> dat;
    // 初期化 O(NlogN)
    segTreeRangeFreq() {}
    segTreeRangeFreq(vector<vector<ll>> v) {
        n = 1; while(n < (ll)v.size()) n *= 2;
        dat.resize(2*n-1);
        REP(i, v.size()) dat[i+n-1] = v[i];
        for(int i=n-2; i>=0; --i) {
            dat[i].resize(dat[i*2+1].size() + dat[i*2+2].size());
            merge(ALL(dat[i*2+1]), ALL(dat[i*2+2]), dat[i].begin());
        }
    }
    // [a, b) のx以下の個数を返す O(log^2N)
    int query(int a, int b, ll x, int k, int l, int r) {
        if(b <= l || r <= a) return 0;
        if(a <= l && r <= b) return upper_bound(ALL(dat[k]), x) - dat[k].begin();
        int vl = query(a, b, x, k*2+1, l, (l+r)/2);
        int vr = query(a, b, x, k*2+2, (l+r)/2, r);
        return vl + vr;
    }
    int query(int a, int b, ll x) { return query(a, b, x, 0, 0, n); }
};

// 2次元平面上の点集合 矩形中に何個点があるかのクエリに答えることが可能
// (x[i], y[i]) をxでソートしてyをセグ木に乗せるとrangefreqになる
// wavelet matrixじゃなくてセグ木でO(log^2N)でok
