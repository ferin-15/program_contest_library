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

// http://tokoharuland.hateblo.jp/entry/2018/04/01/155743
// 距離行列を仮想頂点とか使ってグラフで表してこれに渡すと最小全域木になる
// initで渡すのは元のグラフの頂点集合
template<bool istree = true>
ll voronoiMst(vector<vector<PII>> g, vector<ll> init) {
    const ll n = g.size();
    ll ret = 0;
    vector<pair<ll,PII>> edges;
    vector<ll> dist(n, LLINF), col(n, -1);
    struct node {
        ll dist, vertex, col;
        node() {}
        node(ll a, ll b, ll c) : dist(a), vertex(b), col(c) {}
        bool operator<(node nd) const { return dist > nd.dist; }
    };
    priority_queue<node> que;
    for(auto i: init) que.push(node(0, i, i));
    while(que.size()) {
        node p = que.top(); que.pop();
        if(dist[p.vertex] == LLINF) {
            dist[p.vertex] = p.dist;
            col[p.vertex] = p.col;
            for(auto to: g[p.vertex]) {
                que.push(node(p.dist+to.second, to.first, p.col));
            }
        } else {
            if(p.col != col[p.vertex]) {
                if(istree) ret += dist[p.vertex] + p.dist;
                else edges.push_back({dist[p.vertex]+p.dist, {col[p.vertex], p.col}});
            }
        }
    }
    if(istree) return ret/2;
    sort(ALL(edges));
    UnionFind uf(2*n);
    REP(i, edges.size()) {
        if(uf.same(edges[i].second.first, edges[i].second.second)) continue;
        uf.unite(edges[i].second.first, edges[i].second.second);
        ret += edges[i].first;
    }
    return ret;
}

// https://codeforces.com/problemset/problem/1095/F
namespace cf529div3F {
    void solve() {
        ll n, m;
        cin >> n >> m;
        vector<vector<PII>> g(n+1);
        REP(i, n) {
            ll a;
            cin >> a;
            g[n].push_back({i, a});
            g[i].push_back({n, a});
        }
        REP(i, m) {
            ll u, v, w;
            cin >> u >> v >> w;
            u--, v--;
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }

        vector<ll> init(n);
        iota(ALL(init), 0);
        cout << voronoiMst<false>(g, init) << endl;
    }
}

// https://atcoder.jp/contests/cf17-final/tasks/cf17_final_j
namespace codefestival2017finalJ {
    void solve() {
        ll n;
        cin >> n;
        vector<vector<PII>> g(2*n);
        REP(i, n) {
          ll x;
          cin >> x;
          g[i].push_back({i+n, x});
          g[i+n].push_back({i, x});
        }
        REP(i, n-1) {
          ll a, b, c;
          cin >> a >> b >> c;
          a--, b--;
          g[a+n].push_back({b+n, c});
          g[b+n].push_back({a+n, c});
        }

        vector<ll> init(n);
        iota(ALL(init), 0);
        cout << voronoiMst<false>(g, init) << endl;
    }
}

signed main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    // cf529div3F::solve();
    codefestival2017finalJ::solve();

    return 0;
}
