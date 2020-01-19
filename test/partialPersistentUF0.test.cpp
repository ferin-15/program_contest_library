#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0575"
#include "../data_structure/partialPersistentUF.cpp"

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n, m, k, q;
    cin >> n >> m >> k >> q;
    vector<ll> a(m), b(m), l(m);
    vector<vector<PII>> g(n);
    REP(i, m) {
        cin >> a[i] >> b[i] >> l[i];
        a[i]--, b[i]--;
        g[a[i]].push_back({b[i], l[i]});
        g[b[i]].push_back({a[i], l[i]});
    }
    vector<ll> f(k);
    REP(i, k) cin >> f[i], f[i]--;
    vector<ll> s(q), t(q);
    REP(i, q) cin >> s[i] >> t[i], s[i]--, t[i]--;

    vector<ll> dist(n, LLINF);
    priority_queue<PII, vector<PII>, greater<PII>> que;
    for(auto i: f) {
        dist[i] = 0;
        que.push({0, i});
    }
    while(que.size()) {
        PII p = que.top(); que.pop();
        if(dist[p.second] < p.first) continue;
        for(auto to: g[p.second]) {
            if(dist[to.first] > dist[p.second] + to.second) {
                dist[to.first] = dist[p.second] + to.second;
                que.push({dist[to.first], to.first});
            }
        }
    }

    vector<ll> x(m);
    REP(i, m) x[i] = min(dist[a[i]], dist[b[i]]);
    vector<ll> xs(x);
    sort(ALL(xs));
    xs.erase(unique(ALL(xs)), xs.end());
    vector<vector<ll>> v(xs.size());
    REP(i, m) {
        x[i] = lower_bound(ALL(xs), x[i]) - xs.begin();
        v[x[i]].push_back(i);
    }

    // i番目の距離の辺まで追加した
    vector<ll> trans(xs.size());
    partialPersistentUF uf(n);
    for(ll i=(ll)xs.size()-1; i>=0; --i) {
        trans[i] = (i+1==(ll)xs.size()?0:trans[i+1]) + v[i].size();
        for(auto j: v[i]) uf.unite(a[j], b[j]);
    }

    REP(i, q) {
        // [mid,xs.size()) の辺を追加したときにs[i]とt[i]が連結か
        auto check = [&](ll mid) { return uf.same(s[i], t[i], trans[mid]); };
        ll lb=0, ub = xs.size();
        while(ub-lb > 1) {
            ll mid = (lb+ub)/2;
            if(check(mid)) lb = mid;
            else ub = mid;
        }
        cout << xs[lb] << endl;
    }

    return 0;
}