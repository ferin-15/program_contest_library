// BEGIN CUT
class twoEdgeComponent {
private:
    void dfs(ll v, ll p, ll &k) {
        ord[v] = k++;
        low[v] = ord[v];
        for(auto to: g[v]) {
            if(ord[to]==-1) {
                dfs(to, v, k);
                chmin(low[v], low[to]);
                if(ord[v] < low[to]) bridge.emplace_back(v, to);
            } else if(to != p) {
                chmin(low[v], ord[to]);
            }
        }
    }
    void dfs2(ll v, ll p, ll &k) {
        if(~p && ord[p] >= low[v]) cmp[v] = cmp[p];
        else cmp[v] = k++;
        for(auto to: g[v]) if(cmp[to] == -1) dfs2(to, v, k);
    }
public:
    vector<vector<ll>> g;
    vector<ll> ord, low, cmp;
    vector<PII> bridge;

    twoEdgeComponent() {}
    twoEdgeComponent(ll n) : g(n), ord(n, -1), low(n), cmp(n, -1) {}

    void add_edge(ll u, ll v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<vector<ll>> build() {
        ll k = 0;
        REP(i, g.size()) if(ord[i]==-1) dfs(i, -1, k);
        k = 0;
        REP(i, g.size()) if(cmp[i]==-1) dfs2(i, -1, k);
        vector<vector<ll>> ret(k);
        for(auto e: bridge) {
            ll x = cmp[e.first], y = cmp[e.second];
            ret[x].push_back(y);
            ret[y].push_back(x);
        }
        return ret;
    }
};
// END CUT