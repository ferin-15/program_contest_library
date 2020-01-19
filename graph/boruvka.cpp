struct UnionFind {
    vector<int> par, s;
    UnionFind(int n=2e5) { init(n); }
    void init(int n) {
        s.assign(n, 1); par.resize(n);
        iota(par.begin(), par.end(), 0);
    }
    int find(int x) {
        if(par[x] == x) return x;
        return par[x] = find(par[x]);
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y) return;
        if(s[x] < s[y]) par[x] = y, s[y] = s[x] + s[y];
        else par[y] = x, s[x] = s[x] + s[y];
    }
    bool same(int x, int y) { return find(x) == find(y); }
    int size(int x) { return s[find(x)]; }
};

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

namespace keyence2019E {
    void solve() {
        ll n, d;
        cin >> n >> d;
        vector<ll> a(n);
        REP(i, n) cin >> a[i];

        // 2番目に小さいコストの辺までを持つように遷移
        auto chain = [](pair<PII,PII> a, PII p) {
            if(a.first.second == p.second) {
                chmin(a.first.first, p.first);
            } else if(a.second.second == p.second) {
                chmin(a.second.first, p.first);
                if(a.first > a.second) swap(a.first, a.second);
            } else {
                if(p < a.first) {
                    a.second = a.first;
                    a.first = p;
                } else if(p < a.second) {
                    a.second = p;
                }
            }
            return a;
        };

        // 各頂点から最小のコストの辺を求める
        // f(連結成分数、i番目の頂点が属する連結成分)
        function<vector<PII>(ll,vector<ll>)> f = [&](ll sz, vector<ll> belong) {
            // ret[i] = (頂点iからコスト最小の辺の(コスト, i以外の端点))
            // iがufの親以外ならsecondは-1として連結成分ごとに管理
            vector<PII> ret(sz, PII(LLINF, -1));

            // ((最小の辺コスト,頂点)(2番目に小さい辺コスト,頂点))
            pair<PII,PII> mi({LLINF,-1}, {LLINF,-1});
            REP(i, n) {
                // mi.first.secondがiと同じ連結成分なら2番目に小さい辺を利用
                auto e = mi.first.second == belong[i] ? mi.second : mi.first;
                e.first += a[i] + i*d;
                ret[belong[i]] = min(ret[belong[i]], e);
                mi = chain(mi, PII(a[i]-i*d, belong[i]));
            }

            mi = {{LLINF,-1}, {LLINF,-1}};
            for(ll i=n-1; i>=0; --i) {
                auto e = mi.first.second == belong[i] ? mi.second : mi.first;
                e.first += a[i] - i*d;
                ret[belong[i]] = min(ret[belong[i]], e);
                mi = chain(mi, PII(a[i]+i*d, belong[i]));
            }

            return ret;
        };

        cout << boruvka<ll, decltype(f)>(n, f) << endl;
    }
}