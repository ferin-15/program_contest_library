// O(n*1.466^n) n<=40で16ms
struct maxIndependentSet {
    ll n;
    vector<vector<ll>> g;

    ll dfs(ll v, vector<ll>& used) {
        if(v == n) return 0;
        ll ret = 0;
        if(!used[v]) {
            vector<ll> nv(1, v);
            for(ll i: g[v]) if(!used[i]) nv.push_back(i);
            for(ll i: nv) used[i] = 1;
            chmax(ret, dfs(v+1, used) + 1);
            for(ll i: nv) used[i] = 0;
        }
        ll d = 0;
        for(ll i: g[v]) if(!used[i]) d++;
        if(d > 1 || used[v]) {
            if(!used[v]) {
                used[v] = 1;
                chmax(ret, dfs(v+1, used));
                used[v] = 0;
            } else {
                chmax(ret, dfs(v+1, used));
            }
        }
        return ret;
    }

    maxIndependentSet() {}
    maxIndependentSet(ll n) : n(n), g(n) {}

    void add_edge(ll a, ll b) {
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int get() {
        vector<ll> used(n);
        return dfs(0, used);
    }
};

namespace thanks2017G {
    void solve() {
        ll n, m;
        cin >> n >> m;
        maxIndependentSet graph(n);
        REP(i, m) {
            int a, b;
            cin >> a >> b;
            graph.add_edge(a-1, b-1);
        }
        cout << graph.get() << endl;
    }
}