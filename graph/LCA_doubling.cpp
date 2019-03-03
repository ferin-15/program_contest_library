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