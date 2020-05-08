// 2乗の木DPの雛形
vector<ll> sz(n);
vector<vector<mint>> dp(n);
auto dfs = [&](auto &&self, ll v, ll p) -> void {
    sz[v] = 1;
    dp[v].resize(sz[v]+1);
    dp[v][1] = 1;
    for(auto to: g[v]) if(to!=p) {
        self(self, to, v);
        vector<mint> merged(2*(sz[v]+sz[to])+1);
        REP(i, sz[v]*2+1) REP(j, sz[to]*2+1) {
            merged[i+j] += dp[v][i] * dp[to][j];
        }
        sz[v] += sz[to];
        dp[v] = move(merged);
    }
    dp[v][0] = 1;
};