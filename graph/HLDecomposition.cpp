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

class HLDecomposition {
    void dfs1(ll v, ll p) {
        if(g[v].size() && g[v][0]==p) swap(g[v][0], g[v].back());
        for(auto &to: g[v]) {
            if(to == p) continue;
            dfs1(to, v);
            sz[v] += sz[to];
            if(sz[to] > sz[g[v][0]]) swap(to, g[v][0]);
        }
    }
    void dfs2(ll v, ll p, ll &k) {
        par[v] = p; vid[v] = k++;
        for(auto to: g[v]) {
            if(to == p) continue;
            head[to] = (to == g[v][0] ? head[v] : to);
            dfs2(to, v, k);
        }
    }

public:
    int n;
    vector<vector<ll>> g;
    vector<ll> vid, head, sz, par;

    HLDecomposition(){}
    HLDecomposition(ll sz): n(sz), g(n), vid(n,-1), head(n), sz(n,1), par(n) {}

    void add_edge(ll u, ll v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void build(vector<ll> rs=vector<ll>(1,0)) {
        ll k = 0;
        for(ll r: rs) {
            dfs1(r, -1);
            head[r] = r;
            dfs2(r, -1, k);
        }
    }

    // パスu-vの頂点属性クエリ
    void for_each(ll u, ll v, const function<void(ll,ll)>& f) {
        while(1){
            if(vid[u]>vid[v]) swap(u,v);
            f(max(vid[head[v]], vid[u]), vid[v]); // 開区間!!!
            if(head[u]!=head[v]) v = par[head[v]];
            else break;
        }
    }
    // パスu-vの辺属性クエリ
    void for_each_edge(ll u, ll v, const function<void(ll,ll)>& f) {
        while(1) {
            if(vid[u]>vid[v]) swap(u,v);
            if(head[u]!=head[v]) {
                f(vid[head[v]], vid[v]); // 開区間!!!
                v = par[head[v]];
            } else {
                if(u!=v) f(vid[u]+1, vid[v]); // 開区間!!!
                break;
            }
        }
    }
    ll lca(ll u, ll v) {
        while(1) {
            if(vid[u]>vid[v]) swap(u,v);
            if(head[u]==head[v]) return u;
            v = par[head[v]];
        }
    }
};
// 頂点vの部分木に対するクエリ → 区間[hld.vid[u]+1, hld.vid[u] + hld.sub[u]) に操作

namespace abc014D {
    void solve() {
        ll n;
        cin >> n;
        HLDecomposition graph(n);
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
            ll lca = graph.lca(u, v);
            cout << dist[u] + dist[v] - 2*dist[lca] + 1 << endl;
        }
    }
}