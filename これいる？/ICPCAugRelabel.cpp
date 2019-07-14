using ll = long long;

// https://gist.github.com/MiSawa/2818cf0bfdb27d42c429f2adb7ee9bc0
// バグってても責任とりません >_<
// 下に行くほど最適化が減る代わりに記述が楽になります
struct ICPCAugRelabel {//{{{
    using Flow = int64_t;
    constexpr static Flow INF = numeric_limits<Flow>::max();
    struct E{
        size_t t, rev;
        Flow u;
    };
    vector<vector<E>> g;
    vector<size_t> label, cur;
    ICPCAugRelabel(const size_t n) : g(n), label(n), cur(n) {}
    void add_edge(const size_t s, const size_t t, const Flow u){
        if(s == t) return;
        g[s].emplace_back(E{t, g[t].size(), u});
        g[t].emplace_back(E{s, g[s].size()-1, 0});
    }
    Flow dfs(const size_t u, const size_t t, const Flow flow){
        if(u == t or flow == 0) return flow;
        Flow sum = 0;
        for(size_t &i = cur[u]; i < g[u].size(); ++i){ // & を付ける!!
            E &e = g[u][i], &re = g[e.t][e.rev]; // & を両方付ける!!
            const int &v = e.t;
            if(label[v]+1 != label[u] or e.u == 0) continue;
            const Flow f = dfs(v, t, min(flow - sum, e.u));
            e.u -= f; re.u += f;
            if((sum += f) == flow) return sum;
        }
        label[u] += 2;
        for(const auto &e : g[u]) if(e.u > 0)
            label[u] = std::min(label[u], label[e.t] + 1);
        cur[u] = 0;
        return sum;
    }
    Flow run(const size_t s, const size_t t){
        assert(s != t); // or return infinity
        for(Flow flow = 0; ; flow += dfs(s, t, INF))
            if(label[s] > g.size()) return flow;
    }
};//}}}
struct ICPCAugRelabel2 {//{{{
    struct E{
        int t, rev;
        ll u;
    };
    vector<vector<E>> g;
    vector<int> label, cur;
    ICPCAugRelabel2(int n) : g(n), label(n), cur(n) {}
    void add_edge(int s, int t, ll u){
        if(s == t) return;
        g[s].emplace_back(E{t, (int)g[t].size(), u});
        g[t].emplace_back(E{s, (int)g[s].size()-1, 0});
    }
    ll dfs(int u, int t, ll flow){
        if(u == t or flow == 0) return flow;
        ll sum = 0;
        for(int &i = cur[u]; i < g[u].size(); ++i){ // & を付ける!!
            E &e = g[u][i], &re = g[e.t][e.rev]; // & を両方付ける!!
            int &v = e.t;
            if(label[v]+1 != label[u] or e.u == 0) continue;
            ll f = dfs(v, t, min(flow - sum, e.u));
            e.u -= f; re.u += f;
            if((sum += f) == flow) return sum;
        }
        ++label[u];
        cur[u] = 0;
        return sum;
    }
    ll run(int s, int t){
        assert(s != t); // or return infinity
        for(ll flow = 0; ; flow += dfs(s, t, 1LL<<60))
            if(label[s] > g.size()) return flow;
    }
};//}}}
struct ICPCAugRelabel3 {//{{{
    struct E{
        int t, rev;
        ll u;
    };
    vector<vector<E>> g;
    vector<int> label, cur;
    ICPCAugRelabel3(int n) : g(n), label(n), cur(n) {}
    void add_edge(int s, int t, ll u){
        if(s == t) return;
        g[s].emplace_back(E{t, (int)g[t].size(), u});
        g[t].emplace_back(E{s, (int)g[s].size()-1, 0});
    }
    ll dfs(int u, int t, ll flow){
        if(u == t or flow == 0) return flow;
        for(int &i = cur[u]; i < g[u].size(); ++i){ // & を付ける!!
            E &e = g[u][i], &re = g[e.t][e.rev]; // & を両方付ける!!
            if(label[e.t]+1 != label[u]) continue;
            const ll f = dfs(e.t, t, min(flow, e.u));
            e.u -= f; re.u += f;
            if(f) return f;
        }
        ++label[u];
        cur[u] = 0;
        return 0;
    }
    ll run(int s, int t){
        assert(s != t); // or return infinity
        for(ll flow = 0; ; flow += dfs(s, t, 1LL<<60))
            if(label[s] > g.size()) return flow;
    }
};//}}}
