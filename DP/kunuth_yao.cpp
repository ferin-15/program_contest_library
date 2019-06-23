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

// dp(i,j) = min_{i<=s<j} {dp(i,s)+dp(s+1,j)} + W(i,j) を O(N^2) で計算
template<typename F>
ll knuth_yao(ll n, F W) {
    vector<vector<ll>> dp(n+1, vector<ll>(n+1));
    // K(i,j) = argmin_{i<=s<j} (X(i,s) + X(s+1,j))
    vector<vector<int>> K(n+1, vector<int>(n+1));
    REP(i, n+1) REP(j, n+1) {
        dp[i][j] = (i==j ? 0 : LLINF);
        K[i][j] = (i==j ? i : 0);
    }
    for(int w=1; w<=n; ++w) {
        for(int i=0, j=i+w; (j=i+w) < n; ++i) {
            // K(i,j)の単調性から範囲が限定できる
            for(int r = K[i][j-1]; r <= K[i+1][j]; ++r) {
                ll c = dp[i][r] + dp[r+1][j] + W(i, j);
                if(dp[i][j] > c) dp[i][j] = c, K[i][j] = r;
            }
        }
    }
    return dp[0][n-1];
}

namespace KUPC2012J {
    void solve() {
        ll n;
        cin >> n;
        vector<ll> a(n);
        REP(i, n) cin >> a[i];

        vector<ll> w(a);
        FOR(i, 1, n) w[i] += w[i-1];
        auto f = [&](ll i, ll j) { return w[j] - (i==0?0:w[i-1]); };

        cout << knuth_yao<decltype(f)>(n, f) << endl;
    }
}

namespace SPOJ_BRKSTRNG {
    void solve() {
        int n, m;
        while(cin >> n >> m) {
            vector<int> a(m+1);
            REP(i, m) cin >> a[i];
            a[m] = n;

            auto f = [&](ll i, ll j) {
                if(i >= j) return 0;
                return a[j] - (i==0?0:a[i-1]);
            };
            cout << knuth_yao<decltype(f)>(m+1, f) << endl;
        }
    }
}

signed main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    // KUPC2012J::solve();
    SPOJ_BRKSTRNG::solve();

    return 0;
}
