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

template <typename S>
class sparseTable {
public:
    using T = typename S::T;
    int n;
    vector<int> log2;
    vector<vector<T>> t;
    sparseTable(int nn = 1e5) { init(nn); }
    void init(int nn) {
        n = nn;
        log2.assign(n+1, 0);
        for(int i=2; i<=n; ++i) log2[i] = log2[i >> 1] + 1;
        t.assign(log2[n]+1, vector<T>(n));
    }
    void build(vector<T> v) {
        for(int i=0; i<n; ++i) t[0][i] = v[i];
        for(int j=1; j<=log2[n]; ++j) {
            int w = 1LL<<(j-1);
            for (int i = 0; i+(w<<1) <= n; ++i) {
                t[j][i] = S::op(t[j-1][i], t[j-1][i+w]);
            }
        }
    }
    // [l, r]
    T query(int l, int r) {
        int j = log2[r - l];
        return S::op(t[j][l], t[j][r-(1 << j)+1]);
    }
};
struct minimum {
    using T = PII;
    static T op(const T& a, const T& b) { return min(a, b); }
};

class LCA {
private:
    const int n = 0;
    const int log2_n = 0;
    vector<vector<int>> par;
    vector<vector<int>> g;
    vector<int> depth;     // 頂点iの深さ
    vector<int> vs;        // 頂点を訪問順に並べたもの
    vector<int> depth_seq; // depth_seq[i] = (頂点vs[i]の深さ)
    vector<int> id;        // 頂点が初めてvsに登場するインデックス
    sparseTable<minimum> st;
    void dfs(int v, int p, int d, int &k) {
        id[v] = k; vs[k] = v; depth_seq[k++] = d; depth[v] = d;
        for(auto to: g[v]) if(to != p) {
            dfs(to, v, d+1, k);
            vs[k] = v; depth_seq[k++] = d;
        }
    }
public:
    LCA(int n_=1e5) : n(n_), g(n), depth(n), vs(2*n-1), depth_seq(2*n-1), id(n) {}
    // u-vに辺を張る
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    // rootを根として初期化
    void build(int root = 0) {
        int k = 0;
        dfs(root, -1, 0, k);
        vector<PII> v(2*n-1);
        REP(i, 2*n-1) v[i] = {depth_seq[i], i};
        st.init(2*n-1);
        st.build(v);
    }
    // uとvのlcaを返す O(1)
    int get(int u, int v) {
        if(id[u] > id[v]) swap(u, v);
        return vs[st.query(id[u], id[v]).second];
    }
};

namespace ABC014D {
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