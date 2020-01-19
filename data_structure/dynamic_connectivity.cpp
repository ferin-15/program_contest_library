using edge = PII;
struct dynamicConnectivity {
    int n, sz;
    vector<ll> ans;
    vector<vector<edge>> edges;

    vector<pair<PII, edge>> pending;
    map<edge, int> cnt, appear;

    // セグ木に追加
    void update(int a, int b, const edge &e, int k, int l, int r) {
        if(r <= a || b <= l) return;
        if(a <= l && r <= b) {
            edges[k].emplace_back(e);
            return;
        }
        update(a, b, e, 2*k+1, l, (l+r)/2);
        update(a, b, e, 2*k+2, (l+r)/2, r);
    }
    void update(int a, int b, const edge &e) { update(a, b, e, 0, 0, sz); }

    dynamicConnectivity(int n, int q) : n(q), ans(q) {
        sz = 1;
        while(sz < q) sz <<= 1;
        edges.resize(2 * sz - 1);
    }
    // idx番目のクエリで辺eを追加/削除する
    void insert(int idx, edge e) {
        if(e.first > e.second) swap(e.first, e.second);
        if(cnt[e]++ == 0) appear[e] = idx;
    }
    void erase(int idx, edge e) {
        if(e.first > e.second) swap(e.first, e.second);
        if(--cnt[e] == 0) pending.emplace_back(PII(appear[e], idx), e);
    }
    // クエリを変換してセグ木に追加する
    void build() {
        for(auto &p : cnt) if(p.second > 0) {
            pending.emplace_back(PII(appear[p.first], sz), p.first);
        }
        for(auto &s : pending) update(s.first.first, s.first.second, s.second);
    }
    // セグ木上を探索
    void execute(function<void(ll)> f, function<void(edge)> add, function<void(void)> undo, int k = 0) {
        for(auto &e : edges[k]) add(e);
        if(k < sz-1) {
            execute(f, add, undo, 2*k+1);
            execute(f, add, undo, 2*k+2);
        } else if(k-sz+1 < n) {
            // 時刻k-sz+1での処理
            f(k-sz+1);
        }
        REP(i, edges[k].size()) undo();
    }
};

namespace Dynamic_connectivity_contest_A {
    struct UnionFind {
        vector<int> data;
        stack<PII> st;
        ll num;

        UnionFind(int sz) : data(sz, -1), num(sz) {}

        int find(int k) {
            if(data[k] < 0) return (k);
            return (find(data[k]));
        }
        bool unite(int x, int y) {
            x = find(x), y = find(y);
            st.emplace(x, data[x]);
            st.emplace(y, data[y]);
            if(x == y) {
                st.emplace(0, 0);
                return (false);
            }
            num--;
            st.emplace(1, 1);
            if(data[x] > data[y]) swap(x, y);
            data[x] += data[y];
            data[y] = x;
            return (true);
        }
        void undo() {
            num += st.top().first;
            st.pop();
            data[st.top().first] = st.top().second;
            st.pop();
            data[st.top().first] = st.top().second;
            st.pop();
        }
        int size(int k) { return (-data[find(k)]); }
    };

    void solve() {
        #define NAME "connect"
        assert(freopen(NAME ".in", "r", stdin));
        assert(freopen(NAME ".out", "w", stdout));

        ll n, q;
        cin >> n >> q;
        vector<ll> x;
        dynamicConnectivity dc(n, q);
        REP(i, q) {
            char c;
            cin >> c;
            if(c == '?') {
                x.push_back(i);
            } else if(c == '+') {
                ll u, v;
                cin >> u >> v;
                dc.insert(i, {u-1, v-1});
            } else {
                ll u, v;
                cin >> u >> v;
                dc.erase(i, {u-1, v-1});
            }
        }
        dc.build();

        UnionFind uf(n);
        vector<ll> ans(q);
        auto f = [&](ll t) { ans[t] = uf.num; };
        auto add = [&](edge e) { uf.unite(e.first, e.second); };
        auto undo = [&]() { uf.undo(); };
        dc.execute(f, add, undo);

        for(auto i: x) cout << ans[i] << endl;
    }
}

namespace nikkei2019qualA {
    struct UnionFind {
        vector<int> data;
        stack<PII> st;
        vector<ll> cost;

        UnionFind(int sz) : data(sz, -1), cost(sz) {}

        int find(int k) {
            if(data[k] < 0) return (k);
            return (find(data[k]));
        }
        bool unite(int x, int y) {
            st.emplace(x, y);
            x = find(x), y = find(y);
            if(data[x] > data[y]) swap(x, y);
            st.emplace(x, data[x]);
            st.emplace(y, data[y]);
            st.emplace(x, cost[x]);
            if(x == y) return (false);
            data[x] += data[y];
            data[y] = x;
            cost[x] += cost[y];
            return (true);
        }
        PII undo() {
            cost[st.top().first] = st.top().second; st.pop();
            data[st.top().first] = st.top().second; st.pop();
            data[st.top().first] = st.top().second; st.pop();
            PII ret = st.top(); st.pop();
            return ret;
        }
        int size(int k) { return (-data[find(k)]); }
    };

    void solve() {
        ll n, m;
        cin >> n >> m;
        vector<ll> x(n), a(m), b(m), y(m);
        REP(i, n) cin >> x[i];
        REP(i, m) cin >> a[i] >> b[i] >> y[i], a[i]--, b[i]--;

        vector<ll> idx(m);
        iota(ALL(idx), 0);
        sort(ALL(idx), [&](ll l, ll r){
            return y[l] < y[r];
        });

        dynamicConnectivity dc(n, 2*m);
        ll id = 0;
        for(auto i: idx) dc.insert(id++, {a[i], b[i]});
        reverse(ALL(idx));
        for(auto i: idx) dc.erase(id++, {a[i], b[i]});
        dc.build();

        ll ans = 0;
        UnionFind uf(n);
        vector<bool> mark(n);
        REP(i, n) uf.cost[i] = x[i];
        auto add = [&](edge e){
            uf.unite(e.first, e.second);
        };
        auto undo = [&](){
            ll x = uf.st.top().first;
            bool flag = mark[uf.find(x)];
            PII p = uf.undo();
            if(flag) {
                mark[uf.find(p.first)] = true;
                mark[uf.find(p.second)] = true;
            }
        };
        auto f = [&](ll t) {
            if(m-1 <= t && t < 2*m-1) {
                if(!mark[uf.find(a[idx[t-m+1]])] && y[idx[t-m+1]] > uf.cost[uf.find(a[idx[t-m+1]])]) {
                    ans++;
                }
                // 連結成分に含まれる辺は消さないようにマーク
                else {
                    mark[uf.find(a[idx[t-m+1]])] = true;
                    mark[uf.find(b[idx[t-m+1]])] = true;
                }
            }
        };
        dc.execute(f, add, undo);
        cout << ans << endl;
    }
}
