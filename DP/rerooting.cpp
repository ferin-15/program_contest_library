// BEGIN CUT
template <class T, class W> 
class rerooting {
private:
    struct edge {
        ll to, rev;
        W w;
    };

    const ll n;
    vector<vector<edge>> g;
    vector<vector<T>> ldp, rdp;
    vector<ll> lptr, rptr;
    const function<T(T,T)> merge;
    const function<T(T,W)> add;
    const T id;

    T dfs(ll v, ll p) {
        while(lptr[v] != p && lptr[v] < (ll)g[v].size()) {
            edge &e = g[v][lptr[v]];
            ldp[v][lptr[v]+1] = merge(ldp[v][lptr[v]], add(dfs(e.to, e.rev), e.w));
            lptr[v]++;
        }
        while(rptr[v] != p && rptr[v] >= 0) {
            edge &e = g[v][rptr[v]];
            rdp[v][rptr[v]] = merge(add(dfs(e.to, e.rev), e.w), rdp[v][rptr[v]+1]);
            rptr[v]--;
        }
        if(p < 0) return rdp[v][0];
        return merge(ldp[v][p], rdp[v][p+1]);
    }

public:
    rerooting(ll n, function<T(T,T)> merge, function<T(T,W)> add, T id) : n(n), g(n), ldp(n), rdp(n), lptr(n), rptr(n), merge(merge), add(add), id(id) {}

    void add_edge(ll u, ll v, W w) {
        g[u].push_back({v, (ll)g[v].size(), w});
        g[v].push_back({u, (ll)g[u].size()-1, w});
    }

    vector<T> build() {
        REP(i, n) {
            ldp[i].assign(g[i].size()+1, id);
            rdp[i].assign(g[i].size()+1, id);
            lptr[i] = 0;
            rptr[i] = (ll)g[i].size()-1;
        }
        vector<T> ans;
        REP(i, n) ans.emplace_back(dfs(i, -1));
        return ans;
    }
};
// END CUT