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

class twoEdgeComponent {
private:
    void dfs(ll v, ll p, ll &k) {
        ord[v] = k++;
        low[v] = ord[v];
        for(auto to: g[v]) {
            if(ord[to]==-1) {
                dfs(to, v, k);
                chmin(low[v], low[to]);
                if(ord[v] < low[to]) bridge.emplace_back(v, to);
            } else if(to != p) {
                chmin(low[v], ord[to]);
            }
        }
    }
    void dfs2(ll v, ll p, ll &k) {
        if(~p && ord[p] >= low[v]) cmp[v] = cmp[p];
        else cmp[v] = k++;
        for(auto to: g[v]) if(cmp[to] == -1) dfs2(to, v, k);
    }
public:
    vector<vector<ll>> g;
    vector<ll> ord, low, cmp;
    vector<PII> bridge;

    twoEdgeComponent() {}
    twoEdgeComponent(ll n) : g(n), ord(n, -1), low(n), cmp(n, -1) {}

    void add_edge(ll u, ll v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<vector<ll>> build() {
        ll k = 0;
        REP(i, g.size()) if(ord[i]==-1) dfs(i, -1, k);
        k = 0;
        REP(i, g.size()) if(cmp[i]==-1) dfs2(i, -1, k);
        vector<vector<ll>> ret(k);
        for(auto e: bridge) {
            ll x = cmp[e.first], y = cmp[e.second];
            ret[x].push_back(y);
            ret[y].push_back(x);
        }
        return ret;
    }
};
