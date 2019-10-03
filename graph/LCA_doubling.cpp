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

struct LCA {
    const int n = 0;
    const int log2_n = 0;
    vector<vector<int>> g;
    vector<vector<int>> par;  // par[2^i上][頂点v]
    vector<int> dep;

    void dfs(int v, int p, int d) {
        par[0][v] = p;
        dep[v] = d;
        for(auto to: g[v]) {
            if(to == p) continue;
            dfs(to, v, d+1);
        }
    }

    LCA() {}
    LCA(int n) : n(n), log2_n(log2(n)+1), g(n),
        par(log2_n, vector<int>(n)), dep(n) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void build() {
        dfs(/*root=*/0, -1, 0);
        for(int i=0; i+1 < log2_n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(par[i][j] < 0) par[i+1][j] = -1;
                else par[i+1][j] = par[i][par[i][j]];
            }
        }
    }

    int get(int u, int v) {
        if(dep[u] > dep[v]) swap(u, v);
        REP(i, log2_n) {
            if((dep[v] - dep[u]) >> i & 1) {
                v = par[i][v];
            }
        }
        if(u == v) return u;
        for(int i=log2_n-1; i>=0; --i) {
            if(par[i][u] != par[i][v]) {
                u = par[i][u];
                v = par[i][v];
            }
        }
        return par[0][u];
    }
};

namespace abc014D {
    void solve() {
        ll n;
        cin >> n;
        LCA graph(n);
        vector<vector<ll>> g(n);
        REP(i, n-1) {
            ll a, b;
            cin >> a >> b;
            a--, b--;
            g[a].push_back(b);
            g[b].push_back(a);
            graph.add_edge(a, b);
        }
        graph.build();

        vector<ll> dist(n);
        function<void(ll,ll,ll)> dfs = [&](ll v, ll p, ll d) {
            dist[v] = d;
            for(auto to: g[v]) if(to != p) {
                dfs(to, v, d+1);
            }
        };
        dfs(0, -1, 0);

        ll q;
        cin >> q;
        REP(i, q) {
            ll u, v;
            cin >> u >> v;
            u--, v--;
            ll lca = graph.get(u, v);
            cout << dist[u] + dist[v] - 2*dist[lca] + 1 << endl;
        }
    }
}
