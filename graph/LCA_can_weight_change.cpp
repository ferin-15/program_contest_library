struct LCA {
    struct edge { int id, to, cost; };
    const int n = 0;
    const int log2_n = 0;
    vector<vector<int>> par;
    vector<vector<edge>> g;
    vector<int> depth;     // 頂点iの深さ
    vector<int> vs;        // 頂点を訪問順に並べたもの
    vector<int> depth_seq; // depth_seq[i] = (頂点vs[i]の深さ)
    vector<int> id;        // 頂点が初めてvsに登場するインデックス
    vector<int> es;        // 辺のインデックス(i*2+(葉方向:0,根方向:1))
    vector<int> w;         // 辺の重み
    BIT<int> bit;
    struct minimum_st {
        using T = PII;
        static T op(const T& a, const T& b) { return min(a, b); }
    };
    sparseTable<minimum_st> st;

    void dfs(int v, int p, int d, int &k) {
        id[v] = k; vs[k] = v; depth_seq[k++] = d; depth[v] = d;
        for(auto e: g[v]) {
            if(e.to == p) continue;
            bit.update(k, e.cost); es[e.id*2] = k;
            dfs(e.to, v, d+1, k);
            vs[k] = v; depth_seq[k++] = d;
            bit.update(k, -e.cost); es[e.id*2+1] = k;
        }
    }

    LCA(int n_=1e5) :
    n(n_), g(n, vector<edge>()), depth(n), vs(2*n-1),
    depth_seq(2*n-1), id(n), es((n-1)*2), w(n-1) {
        bit.init(2*n-1);
    }
    // 重みcostのi番目の辺(u,v)
    void add_edge(int i, int u, int v, int cost) {
        g[u].push_back({i, v, cost});
        g[v].push_back({i, u, cost});
        w[i] = cost;
    }
    void build(int root = 0) {
        int k = 0;
        dfs(root, -1, 0, k);
        vector<PII> v(2*n-1);
        REP(i, 2*n-1) v[i] = {depth_seq[i], i};
        st.construct(2*n-1);
        st.init(v);
    }

    // LCA O(logN)
    int get(int u, int v) {
        if(id[u] > id[v]) swap(u, v);
        return vs[st.query(id[u], id[v]).second];
    }
    // uとvの距離 O(logN)
    int length(int u, int v) {
        int lca = get(u, v);
        return bit.query(id[v]) + bit.query(id[u]) - 2*bit.query(id[lca]);
    }
    // 辺xのコストをtに変更 O(logN)
    void update(int x, int t) {
        bit.update(es[x*2], t - w[x]);
        bit.update(es[x*2+1], w[x] - t);
        w[x] = t;
    }
};

// https://atcoder.jp/contests/njpc2017/tasks/njpc2017_h
namespace njpc2017h {
    int c[100010];
    signed main(void) {
        int n;
        cin >> n;
        LCA lca(n);
        vector<ll> p(n);
        FOR(i, 1, n) cin >> p[i], p[i]--;
        REP(i, n) cin >> c[i];

        FOR(i, 1, n) {
            int cost = c[i]==c[p[i]]?1:0;
            lca.add_edge(i-1, i, p[i], cost);
        }
        lca.build();

        int q;
        cin >> q;
        vector<string> ans(q);
        REP(i, q) {
            int type;
            cin >> type;
            if(type == 1) {
                int u; cin >> u; u--;
                if(u == 0) continue;
                // u と p[u] の間の辺について更新
                lca.update(u-1, 1-lca.w[u]);
            } else {
                int u, v; cin >> u >> v; u--, v--;
                ans[i] = lca.length(u,v)>=1?"NO":"YES";
            }
        }
        for(auto i: ans) cout << i << endl;

        return 0;
    }
}