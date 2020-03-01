// BEGIN CUT
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
// 部分木 頂点クエリ → 区間[hld.vid[u]+1, hld.vid[u] + hld.sub[u])
// 部分木 辺クエリ → 区間[hld.vid[u]+1, hld.vid[u] + hld.sub[u])
// END CUT