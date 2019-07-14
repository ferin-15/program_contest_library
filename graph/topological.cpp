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

// ans[i] = (i番目の頂点v, swapできる頂点をまとめたときにvが何番目か)
vector<PII> tsort(vector<vector<ll>> g) {
    const int n = g.size();
    vector<ll> h(n, 0);
    REP(i, n) for(int j: g[i]) h[j]++;

    stack<PII> st;
    REP(i, n) if(h[i] == 0) st.push({i, 0});

    vector<PII> ans;
    while(st.size()) {
        PII p = st.top(); st.pop();
        ans.push_back(p);
        for(auto& j: g[p.first]) {
            h[j]--;
            if(h[j] == 0) st.push({j, p.second+1});
        }
    }

    return ans;
}

namespace GRL4B {
    void solve() {
        ll n, m;
        cin >> n >> m;
        vector<vector<ll>> g(n);
        REP(i, m) {
            ll u, v;
            cin >> u >> v;
            g[u].push_back(v);
        }

        auto ans = tsort(g);
        for(auto p: ans) cout << p.first << endl;
    }
}

signed main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    GRL4B::solve();

    return 0;
}
