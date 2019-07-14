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

// 各iについてf(i,*)のargminとminをペアで返す
template<typename T, typename Compare = less<T>>
vector<pair<ll,T>> monotone_minima(ll h, ll w, const function<T(ll,ll)> &f, const Compare &comp = Compare()) {
    vector<pair<ll,T>> dp(h);
    function<void(ll,ll,ll,ll)> dfs = [&](ll top, ll bottom, ll left, ll right) {
        if(top > bottom) return;
        ll line = (top + bottom) / 2;
        ll idx = left;
        T mi = f(line, left);
        for(ll i=left+1; i<=right; ++i) {
            T cost = f(line, i);
            if(comp(cost, mi)) {
                mi = cost;
                idx = i;
            }
        }
        dp[line] = make_pair(idx, mi);
        dfs(top, line-1, left, idx);
        dfs(line+1, bottom, idx, right);
    };
    dfs(0, h-1, 0, w-1);
    return dp;
}

// https://atcoder.jp/contests/colopl2018-final/tasks/colopl2018_final_c
namespace colocon2018finalC {
    void solve() {
        int n;
        cin >> n;
        vector<ll> a(n);
        REP(i, n) cin >> a[i];
        function<ll(ll,ll)> f = [&](ll i, ll j) {
            return a[j] + (j-i)*(j-i);
        };
        auto dp = monotone_minima(n, n, f);
        for(auto p: dp) cout << p.second << endl;
    }
}

signed main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    colocon2018finalC::solve();

    return 0;
}
