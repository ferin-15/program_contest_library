// BEGIN CUT
// require LCA_sparsetable
struct auxiliaryTreeBasedLCA {
    ll cur;
    LCA lca;
    vector<vector<ll>> g;
    vector<ll> depth, fs, ls;

    void dfs(ll v, ll p) {
        fs[v] = cur++;
        for(auto to: g[v]) {
            if(to == p) continue;
            depth[to] = depth[v] + 1;
            dfs(to, v);
        }
        ls[v] = cur-1;
    }
    
    auxiliaryTreeBasedLCA() {}
    auxiliaryTreeBasedLCA(ll n) : lca(n), g(n), depth(n), fs(n), ls(n) {}
    void add_edge(ll a, ll b) {
        lca.add_edge(a, b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    void build() {
        dfs(0, -1);
        lca.build();
    }
    // 頂点集合vとvのLCAからなる部分グラフになるよう縮約し，辺集合を返す
    // この部分グラフは頂点数がO(v.size())
    vector<PII> makeTree(vector<ll> v) {
        sort(ALL(v), [&](ll a, ll b){ return fs[a] < fs[b]; });
        const int k = v.size();
        REP(i, k-1) v.push_back(lca.get(v[i], v[i+1]));
        sort(ALL(v), [&](ll a, ll b){ return fs[a] < fs[b]; });

        stack<ll> st;
        vector<PII> edges;
        int pre = -1;
        REP(i, (ll)v.size()) {
            if(pre == v[i]) continue;
            while(st.size() && ls[st.top()] < fs[v[i]]) st.pop();
            if(st.size()) edges.push_back({st.top(), v[i]});
            st.push(v[i]);
            pre = v[i];
        }
        return edges;
    }
};
// END CUT

// verify 2019/10/5
// https://yukicoder.me/problems/no/901
namespace yukicoder901 {
    void solve() {
        cin.tie(0);
        ios::sync_with_stdio(false);

        ll n;
        cin >> n;
        vector<vector<PII>> g(n);
        auxiliaryTreeBasedLCA tree(n);
        REP(i, n-1) {
            ll a, b, c;
            cin >> a >> b >> c;
            g[a].push_back({b, c});
            g[b].push_back({a, c});
            tree.add_edge(a, b);
        }
        tree.build();
        
        vector<ll> dist(n);
        function<void(ll,ll)> dfs = [&](ll v, ll p) {
            for(auto to: g[v]) {
                if(to.first == p) continue;
                dist[to.first] = dist[v] + to.second;
                dfs(to.first, v);
            }
        };
        dfs(0, -1);

        ll q;
        cin >> q;
        while(q--) {
            ll k;
            cin >> k;
            vector<ll> v(k);
            REP(i, k) cin >> v[i];

            auto edges = tree.makeTree(v);

            ll ret = 0;
            for(auto e: edges) {
                ret += dist[e.first] + dist[e.second] - 2*dist[tree.lca.get(e.first, e.second)];
            }
            cout << ret << endl;
        }
    }
}