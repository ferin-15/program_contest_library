struct Mo {
    int width;
    int nl, nr, ptr;
    vector<bool> used;
    vector<int> left, right, order;
    using F = function<void(int)>;
    F expandL, expandR, shrinkL, shrinkR;

    // クエリの区間 \subseteq [0,n) 
    Mo(int n, F el, F er, F sl, F sr) : width((int)sqrt(n)), nl(0), nr(0), ptr(0), used(n), expandL(el), expandR(er), shrinkL(sl), shrinkR(sr) {}

    // [l, r)
    void insert(int l, int r) {
        left.push_back(l);
        right.push_back(r);
    }
    void build() {
        order.resize(left.size());
        iota(ALL(order), 0);
        sort(ALL(order), [&](int a, int b) {
            if(left[a] / width != left[b] / width) return left[a] < left[b];
            return right[a] < right[b];
        });
    }
    // クエリを1つ進め、クエリのidを返す
    int process() {
        if(ptr == (ll)order.size()) return -1;
        const auto id = order[ptr];
        while(nl > left[id]) expandL(--nl);
        while(nr < right[id]) expandR(nr++);
        while(nl < left[id]) shrinkL(nl++);
        while(nr > right[id]) shrinkR(--nr);
        return order[ptr++];
    }
};

namespace cf221div1d {
    // 部分木クエリを行きがけ順に並べることで数列に置き換えてMo
    void solve() {
        ll n, m;
        cin >> n >> m;
        vector<ll> c(n);
        REP(i, n) cin >> c[i];
        vector<vector<ll>> g(n);
        REP(i, n-1) {
            ll a, b;
            cin >> a >> b;
            a--, b--;
            g[a].push_back(b);
            g[b].push_back(a);
        }

        ll ptr = 0;
        vector<ll> in(n), out(n), rev(n);
        function<void(ll,ll)> dfs = [&](ll v, ll p) {
            rev[ptr] = v;
            in[v] = ptr++;
            for(auto to: g[v]) if(to != p) dfs(to, v);
            out[v] = ptr;
        };
        dfs(0, -1);

        vector<ll> color(100000), sum(100001);
        auto add = [&](ll idx) {
            ++color[c[rev[idx]]];   // idxに対応する頂点の分
            ++sum[color[c[rev[idx]]]];
        };
        auto del = [&](ll idx) {
            --sum[color[c[rev[idx]]]];
            --color[c[rev[idx]]];
        };
        Mo mo(n, add, add, del, del);
        vector<ll> v(m), k(m);
        REP(i, m) {
            cin >> v[i] >> k[i];
            --v[i];
            mo.insert(in[v[i]], out[v[i]]);
        }
        mo.build();

        vector<ll> ans(m);
        REP(i, m) {
            ll idx = mo.process();
            ans[idx] = sum[k[idx]];
        }
        REP(i, m) cout << ans[i] << "\n";
    }
}

namespace ABC014D {
    // 辺属性のパスクエリはオイラーツアーして数列に置き換える
    // 辺を奇数回目に訪れるときに追加，偶数回目で削除をする
    void solve() {
        ll n;
        cin >> n;
        vector<vector<ll>> g(n);
        REP(i, n-1) {
            ll x, y;
            cin >> x >> y;
            x--, y--;
            g[x].push_back(y);
            g[y].push_back(x);
        }

        // オイラーツアー
        ll ptr = 1;
        vector<ll> tour(2*n-1), in(n);
        function<void(ll,ll)> euler_tour = [&](ll v, ll p) {
            in[v] = ptr-1;
            for(auto to: g[v]) {
                if(to == p) continue;
                tour[ptr++] = to;
                euler_tour(to, v);
            }
            if(p != -1) tour[ptr++] = p;
        };
        euler_tour(0, -1);

        // mapでやるとlogが重かったので辺→intの前計算をしてO(1)にした
        ll mp_idx = 0;
        map<PII,int> mp;
        FOR(i, 1, 2*n-1) {
            PII e({tour[i-1], tour[i]});
            if(e.first > e.second) swap(e.first, e.second);
            if(mp.find(e) == mp.end()) mp[e] = mp_idx++;
        }
        vector<ll> v_edge(2*n-2);
        FOR(i, 1, 2*n-1) {
            PII e(tour[i-1], tour[i]);
            if(e.first > e.second) swap(e.first, e.second);
            v_edge[i-1] = mp[e];
        }

        // add,delのidxではなく辺(tour[idx+1],tour[idx])の訪問回数を見る
        ll sum = 0;
        vector<bool> parity(n-1);
        auto add = [&](ll idx) {
            ll e = v_edge[idx];
            parity[e] = !parity[e];
            if(parity[e]) {
                sum++;
            } else {
                sum--;
            }
        };
        auto del = [&](ll idx) {
            ll e = v_edge[idx];
            parity[e] = !parity[e];
            if(parity[e]) {
                sum++;
            } else {
                sum--;
            }
        };
        Mo mo(2*n-1, add, add, del, del);

        ll q;
        cin >> q;
        REP(i, q) {
            ll a, b;
            cin >> a >> b;
            a--, b--;
            ll ta = in[a], tb = in[b];
            if(ta > tb) swap(ta, tb);
            // パスa,bについてのクエリは[in[a],in[b])を見る
            mo.insert(ta, tb);
        }
        mo.build();
        vector<ll> ans(q);
        REP(i, q) {
            ll idx = mo.process();
            ans[idx] = sum;
        }
        REP(i, q) cout << ans[i]+1 << "\n";
    }
};