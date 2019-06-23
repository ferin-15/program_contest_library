vector<ll> dist(n);
function<void(ll,ll)> dfs1 = [&](ll v, ll p) {
    for(auto i: g[v]) if(i != p) {
        dfs1(i, v);
        chmax(dist[v], dist[i] + 1);
    }
};
dfs1(0, -1);

vector<ll> ans(n);
function<void(ll,ll,ll)> dfs2 = [&](ll v, ll d_par, ll p) {
    vector<PII> d_child;
    d_child.push_back({0, -1});
    for(auto i: g[v]) {
        if(i == p) d_child.push_back({d_par+1, i});
        else d_child.push_back({dist[i]+1, i});
    }
    sort(ALL(d_child), greater<>());
    ans[v] = d_child[0].first;
    for(auto i: g[v]) if(i != p) {
        dfs2(i, d_child[d_child[0].second == i].first, v);
    }
};
dfs2(0, 0, -1);
