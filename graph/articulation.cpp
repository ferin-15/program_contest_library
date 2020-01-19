class articulation {
private:
    void dfs(ll v, ll p, ll &k, vector<ll> &ret) {
        ord[v] = k++;
        low[v] = ord[v];
        ll cnt = 0;
        bool is_articulation = false;
        for(auto to: g[v]) {
            if(ord[to]==-1) {
                dfs(to, v, k, ret);
                chmin(low[v], low[to]);
                ++cnt;
                is_articulation |= p!=-1 && low[to] >= ord[v]; 
            } else if(to != p) {
                chmin(low[v], ord[to]);
            }
        }
        is_articulation |= p==-1 && cnt>1;
        if(is_articulation) ret.push_back(v);
    }
public:
    vector<vector<ll>> g;
    vector<ll> ord, low, cmp;

    articulation() {}
    articulation(ll n) : g(n), ord(n, -1), low(n) {}

    void add_edge(ll u, ll v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<ll> build() {
        ll k = 0;
        vector<ll> ret;
        REP(i, g.size()) if(ord[i]==-1) dfs(i, -1, k, ret);
        return ret;
    }
};

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A&lang=jp
namespace GRL3A {
    void solve() {
        ll n, m;
        cin >> n >> m;
        articulation graph(n);
        REP(i, m) {
            ll a, b;
            cin >> a >> b;
            graph.add_edge(a, b);
        }
        auto ret = graph.build();
        sort(ALL(ret));
        for(auto i: ret) cout << i << endl;
    }
}