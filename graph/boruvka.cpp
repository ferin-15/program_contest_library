// BEGIN CUT
template< typename T, typename F >
T boruvka(ll n, F f) {
    vector<ll> rev(n), belong(n);
    UnionFind uf(n);
    T ret = T();
    while(uf.size(0) != n) {
        ll ptr = 0;
        REP(i, n) if(uf.find(i) == i) belong[i] = ptr++, rev[belong[i]] = i;
        REP(i, n) belong[i] = belong[uf.find(i)];
        vector<PII> v = f(ptr, belong);
        bool update = false;
        REP(i, ptr) {
            if(~v[i].second && !uf.same(rev[i], rev[v[i].second])) {
                uf.unite(rev[i], rev[v[i].second]);
                ret += v[i].first;
                update = true;
            }
        }
        if(!update) return -1; // notice!!
    }
    return ret;
}

/*
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
*/
// END CUT