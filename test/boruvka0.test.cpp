#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=ja"
#include "../graph/boruvka.cpp"

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n, m;
    cin >> n >> m;
    vector<vector<PII>> g(n);
    REP(i, m) {
        ll a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }

    // O(fの計算量 * logV)
    // 各頂点から最小のコストの辺を求める
    // sz=連結成分数 belong[i]=i番目の頂点が属する連結成分
    function<vector<PII>(ll,vector<ll>)> f = [&](ll sz, vector<ll> belong) {
        // ret[i] = (連結成分iからコスト最小の辺の(コスト, i以外の端点の連結成分))
        // iがufの親以外ならsecondは-1として連結成分ごとに管理
        vector<PII> ret(sz, PII(LLINF, -1));

        REP(i, n) for(auto to: g[i]) {
            if(belong[i] == belong[to.first]) continue;
            chmin(ret[belong[i]], PII(to.second, belong[to.first]));
        }
        return ret;
    };
    cout << boruvka<ll, decltype(f)>(n, f) << endl;

    return 0;
}