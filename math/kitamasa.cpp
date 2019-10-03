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

// 数列の初項k項aと漸化式の係数dが与えられる
// a_nをO(K^2logN)で求める
vector<ll> dfs(vector<ll> a, vector<ll> d, ll n) {
    ll k = d.size();
    if(n == k) return d;
    vector<ll> ret(k);
    if(n&1 || n<k*2) {
        auto v = dfs(a, d, n-1);
        ret[0] = v[k-1] * a[0] % MOD;
        FOR(i, 1, k) ret[i] = (v[i-1] + v[k-1] * a[i] % MOD) % MOD;
    } else {
        auto v = dfs(a, d, n/2);
        vector<vector<ll>> f(k, vector<ll>(k));
        f[0] = v;
        FOR(i, 1, k) {
            f[i][0] = f[i-1][k-1] * a[0] % MOD;
            FOR(j, 1, k) f[i][j] = (f[i-1][j-1] + f[i-1][k-1] * a[j] % MOD) % MOD;
        }
        REP(i, k) REP(j, k) (ret[i] += v[j] * f[j][i] % MOD) %= MOD;
    }
    return ret;
}
ll kitamasa(vector<ll> a, vector<ll> d, ll n) {
    auto ret = dfs(a, d, n);
    ll ans = 0;
    REP(i, d.size()) (ans += d[i] * ret[i]) %= MOD;
    return ans;
}
