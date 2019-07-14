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

struct UnionFind {
    vector<int> par, s;
    UnionFind(int n=2e5) { init(n); }
    void init(int n) {
        s.assign(n, 1); par.resize(n);
        iota(par.begin(), par.end(), 0);
    }
    int find(int x) {
        if(par[x] == x) return x;
        return par[x] = find(par[x]);
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y) return;
        if(s[x] < s[y]) par[x] = y, s[y] = s[x] + s[y];
        else par[y] = x, s[x] = s[x] + s[y];
    }
    bool same(int x, int y) { return find(x) == find(y); }
    int size(int x) { return s[find(x)]; }
};

class tarjan_offline_lca {
private:
    ll n;
    UnionFind uf;
    vector<ll> anc, lca, visit, used;
    vector<vector<ll>> g;
    vector<vector<PII>> query;
    void dfs(ll v=0, ll p=-1) {
        anc[v] = v;
        for(auto to: g[v]) if(to != p) {
            dfs(to, v);
            uf.unite(to, v);
            anc[uf.find(v)] = v;
        }
        visit[v] = 1;
        for(auto i: query[v]) {
            if(visit[i.first] == 1 && used[i.second]++ == 0) {
                lca[i.second] = anc[uf.find(i.first)];
            }
        }
    }
public:
    tarjan_offline_lca() {}
    tarjan_offline_lca(ll n, ll q) : n(n), uf(n), anc(n), lca(q), visit(n), used(q), g(n), query(n) {}
    // 辺とクエリの追加
    void add_edge(ll a, ll b) {
        g[a].push_back(b);
        g[b].push_back(a);
    }
    // i番目のクエリは頂点aと頂点bのLCA
    void add_query(ll a, ll b, ll i) {
        query[a].push_back({b, i});
        query[b].push_back({a, i});
    }
    // lcaを求める
    vector<ll> build() { dfs(); return lca; }
};

namespace ABC014D {
    void solve() {
        ll n;
        cin >> n;
        tarjan_offline_lca graph(n, 100000);
        vector<vector<ll>> g(n);
        REP(i, n-1) {
            ll a, b;
            cin >> a >> b;
            a--, b--;
            g[a].push_back(b);
            g[b].push_back(a);
            graph.add_edge(a, b);
        }

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
        vector<ll> u(q), v(q);
        REP(i, q) {
            cin >> u[i] >> v[i];
            u[i]--, v[i]--;
            graph.add_query(u[i], v[i], i);
        }

        auto lca = graph.build();
        REP(i, q) cout << dist[u[i]] + dist[v[i]] - 2*dist[lca[i]] + 1 << endl;
    }
}

signed main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    ABC014D::solve();

    return 0;
}
