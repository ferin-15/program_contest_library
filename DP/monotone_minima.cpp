// BEGIN CUT
// 各iについてf(i,*)のargminとminをペアで返す
template<typename T, typename Compare = less<T>>
vector<pair<ll,T>> monotone_minima(ll h, ll w, const function<T(ll,ll)> &f, const Compare &comp = Compare()) {
    vector<pair<ll,T>> dp(h);
    function<void(ll,ll,ll,ll)> dfs = [&](ll top, ll bottom, ll left, ll right) {
        if(top > bottom) return;
        ll line = (top + bottom) / 2;
        ll idx = left;
        T mi = f(line, left);
        for(ll i=left+1; i<=right; ++i) {
            T cost = f(line, i);
            if(comp(cost, mi)) {
                mi = cost;
                idx = i;
            }
        }
        dp[line] = make_pair(idx, mi);
        dfs(top, line-1, left, idx);
        dfs(line+1, bottom, idx, right);
    };
    dfs(0, h-1, 0, w-1);
    return dp;
}
// END CUT

// https://atcoder.jp/contests/colopl2018-final/tasks/colopl2018_final_c
namespace colocon2018finalC {
    void solve() {
        int n;
        cin >> n;
        vector<ll> a(n);
        REP(i, n) cin >> a[i];
        function<ll(ll,ll)> f = [&](ll i, ll j) {
            return a[j] + (j-i)*(j-i);
        };
        auto dp = monotone_minima(n, n, f);
        for(auto p: dp) cout << p.second << endl;
    }
}
