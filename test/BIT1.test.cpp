#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2270"
#include "../memo/macro.hpp"
#include "../data_structure/BIT.cpp"

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

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n, q;
    cin >> n >> q;
    vector<ll> x(n);
    REP(i, n) cin >> x[i];
    
    vector<ll> vs(x);
    sort(ALL(vs));
    vs.erase(unique(ALL(vs)), vs.end());
    REP(i, n) x[i] = lower_bound(ALL(vs), x[i]) - vs.begin();

    BIT<ll> bit(vs.size());
    auto add = [&](ll idx) { bit.update(x[idx], 1); };
    auto del = [&](ll idx) { bit.update(x[idx], -1); };
    Mo_Tree_Vertex mo(n, add, del);

    REP(i, n-1) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        mo.add_edge(a, b);
    }
    mo.prepare();

    vector<ll> k(q);
    REP(i, q) {
        ll a, b;
        cin >> a >> b >> k[i];
        a--, b--;
        mo.insert(a, b);
    }
    mo.build();

    vector<ll> ans(q);
    REP(i, q) {
        ll idx = mo.process();
        ans[idx] = vs[bit.lower_bound(k[idx])];
    }
    REP(i, q) cout << ans[i] << "\n";
    cout << flush;

    return 0;
}