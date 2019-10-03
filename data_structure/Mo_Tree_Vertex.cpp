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

// 頂点クエリのMo
// HL分解で頂点クエリするときに下の辺に下ろすみたいなのをする
// add_edgeとinsertをした後buildをしてprocessを進めていく
struct Mo_Tree_Vertex {
    vector<vector<int>> g, parent;
    vector<int> vs, in;

    vector<int> left, right, order, lca, dep;
    vector<bool> v;
    int width;
    int nl, nr, ptr;

    using F = function<void(int)>;
    F add, del;

    void dfs(int idx, int depth, int par) {
        in[idx] = (int) vs.size();
        dep[idx] = depth;
        parent[0][idx] = par;
        vs.push_back(idx);
        for(auto &to : g[idx]) {
            if(to == par) continue;
            dfs(to, depth + 1, idx);
            vs.push_back(to);
        }
    }

    int getlca(int u, int v) {
        if(dep[u] > dep[v]) swap(u, v);
        for(int k = 0; k < (int)parent.size(); k++) {
            if(((dep[v] - dep[u]) >> k) & 1) {
                v = parent[k][v];
            }
        }
        if(u == v) return (u);
        for(int k = (int)parent.size()-1; k >= 0; k--) {
            if(parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return (parent[0][u]);
    }

    inline void distribute(int vertex) {
        v[vertex].flip();
        if(v[vertex]) add(vertex);
        else del(vertex);
    }

    Mo_Tree_Vertex(int n, F a, F d) : g(n), in(n), dep(n), v(n), width((int)sqrt(2*n-1)), nl(0), nr(0), ptr(0), add(a), del(d) {
        const auto lg = (int) (log2(n) + 1);
        parent.resize(lg, vector<int>(n));
        vs.reserve(2*n-1);
    }

    void add_edge(int x, int y) {
        g[x].push_back(y);
        g[y].push_back(x);
    }
    void prepare() {
        dfs(0, 0, -1);
        for(int k = 0; k+1 < (int)parent.size(); k++) {
            for(int i = 0; i < (int)parent[k].size(); i++) {
                if(parent[k][i] == -1) parent[k + 1][i] = -1;
                else parent[k + 1][i] = parent[k][parent[k][i]];
            }
        }
    }
    void insert(int x, int y) {
        if(in[x] > in[y]) swap(x, y);
        left.push_back(in[x] + 1);
        right.push_back(in[y] + 1);
        lca.push_back(getlca(x, y));
    }
    void build() {
        order.resize(left.size());
        iota(begin(order), end(order), 0);
        sort(begin(order), end(order), [&](int a, int b) {
            if(left[a] / width != left[b] / width) return left[a] < left[b];
            return bool((right[a] < right[b]) ^ (left[a] / width % 2));
        });
    }

    int process() {
        if(ptr == (int)order.size()) return (-1);
        if(ptr > 0) distribute(lca[order[ptr - 1]]); // 前のクエリで追加したLCAを削除
        const auto id = order[ptr];
        while(nl > left[id]) distribute(vs[--nl]);
        while(nr < right[id]) distribute(vs[nr++]);
        while(nl < left[id]) distribute(vs[nl++]);
        while(nr > right[id]) distribute(vs[--nr]);
        distribute(lca[id]); // LCA の頂点を例外として追加する
        return (order[ptr++]);
    }
};

namespace spoj_cot2 {
    void solve() {
        ll n, m;
        cin >> n >> m;
        vector<int> X(n), x(n);
        REP(i, n) cin >> X[i], x[i] = X[i];

        sort(ALL(X));
        X.erase(unique(ALL(X)), X.end());
        REP(i, n) x[i] = lower_bound(ALL(X), x[i]) - X.begin();

        ll sum = 0;
        vector<ll> cnt(1000010);
        auto add = [&](int idx) {
            if(cnt[x[idx]] == 0) ++sum;
            cnt[x[idx]]++;
        };
        auto del = [&](int idx) {
            cnt[x[idx]]--;
            if(cnt[x[idx]] == 0) --sum;
        };

        Mo_Tree_Vertex mo(n, add, del);
        REP(i, n-1) {
            ll a, b;
            cin >> a >> b;
            mo.add_edge(a-1, b-1);
        }
        mo.prepare();

        REP(i, m) {
            ll a, b;
            cin >> a >> b;
            mo.insert(a-1, b-1);
        }
        mo.build();

        vector<ll> ans(m);
        REP(i, m) ans[mo.process()] = sum;
        REP(i, m) cout << ans[i] << "\n";
    }
}