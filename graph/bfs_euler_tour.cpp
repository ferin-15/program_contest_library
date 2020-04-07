// BEGIN CUT
struct bfsEulerTour {
    ll n, maxd;
    vector<ll> idx, tour;
    vector<vector<ll>> g, p, l, r;

    bfsEulerTour() {}
    bfsEulerTour(ll n, ll d) : n(n), maxd(d), idx(n+d, -1), g(n+d), p(d+1, vector<ll>(n+d, -1)), l(d+1, vector<ll>(n+d, -1)), r(d+1, vector<ll>(n+d, -1)) {}

    void add_edge(ll a, ll b) {
        g[a].push_back(b);
        g[b].push_back(a);
    }
    void build(ll root=0) {
        REP(i, maxd-1) {
            g[n+i].push_back(n+i+1);
            g[n+i+1].push_back(n+i);
        }
        g[n].push_back(root);
        g[root].push_back(n);

        queue<ll> que;
        que.push(n+maxd-1);
        idx[n+maxd-1] = tour.size();
        tour.push_back(n+maxd-1);
        while(que.size()) {
            ll v = que.front(); que.pop();
            for(auto to: g[v]) {
                if(idx[to] != -1) continue;
                que.push(to);
                idx[to] = tour.size();
                tour.push_back(to);

                p[0][to] = to;
                FOR(i, 1, maxd+1) p[i][to] = p[i-1][v];

                REP(i, maxd+1) {
                    if(p[i][to] == -1) continue;
                    if(l[i][p[i][to]] == -1) l[i][p[i][to]] = idx[to];
                    r[i][p[i][to]] = idx[to]+1;
                }
            }
        }
    }
    // WMに乗せるとupdateなしオンラインクエリでdが大きい場合でもいけるらしい
    // 頂点vからの距離がd以下の頂点に対応する区間を列挙 O(d)
    void for_each(ll v, ll d, function<void(ll,ll)> f) {
        for(ll i=d; i>=0; --i) {
            if(p[i][v] == -1) continue;
            if(d-1>=i && l[d-1-i][p[i][v]]!=-1 && r[d-1-i][p[i][v]]!=-1) {
                f(l[d-1-i][p[i][v]], r[d-1-i][p[i][v]]);
            }
            if(l[d-i][p[i][v]]!=-1 && r[d-i][p[i][v]]!=-1) {
                f(l[d-i][p[i][v]], r[d-i][p[i][v]]);
            }
        }
    }
};
// END CUT