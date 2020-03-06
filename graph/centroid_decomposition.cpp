// BEGIN CUT
vector<ll> sz(n), dead(n);
auto find_centroid = [&](ll root) {
    auto get_size = [&](auto &&self, ll v, ll p) -> void {
        sz[v] = 1;
        for(auto to: g[v]) if(to.first != p && !dead[to.first]) {
            self(self, to.first, v);
            sz[v] += sz[to.first];
        }
    };
    get_size(get_size, root, -1);
    auto dfs = [&](auto &&self, ll v, ll p) -> ll {
        for(auto to: g[v]) if(to.first != p && !dead[to.first]) {
            if(sz[to.first] > sz[root]/2) return self(self, to.first, v);
        }
        return v;
    };
    return dfs(dfs, root, -1);
};

vector<ll> par(n);
auto centroid_decomposition = [&](auto &&self, ll root, ll p) -> void {
    ll c = find_centroid(root);
    dead[c] = true;
    par[c] = p;
    for(auto to: g[c]) if(!dead[to.first]) {
        self(self, to.first, c);
    }
    // dead[v]=true な頂点には遷移しないようなdfsは計算量的に問題ない
    // dfsして重心cをまたぐ分を数える
    dead[c] = false;
};
centroid_decomposition(centroid_decomposition, 0, -1);
// END CUT