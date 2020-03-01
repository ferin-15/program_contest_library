// BEGIN CUT
struct bfsEulerTour {
    ll n, maxd;
    vector<ll> idx, tour;
    vector<vector<ll>> g, p, l, r;

    bfsEulerTour() {}
    bfsEulerTour(ll n, ll d) : n(n), maxd(d), idx(n+d, -1), g(n+d), p(d+1, vector<ll>(n+d, -1)), l(d+1, vector<ll>(n+d, -1)), r(d+1, vector<ll>(n+d, -1)) {}

    void add_edge(ll a, ll b) {
        g[a].push_back(b);
        g[b].push_back(a);
    }
    void build(ll root=0) {
        REP(i, maxd-1) {
            g[n+i].push_back(n+i+1);
            g[n+i+1].push_back(n+i);
        }
        g[n].push_back(root);
        g[root].push_back(n);

        queue<ll> que;
        que.push(n+maxd-1);
        idx[n+maxd-1] = tour.size();
        tour.push_back(n+maxd-1);
        while(que.size()) {
            ll v = que.front(); que.pop();
            for(auto to: g[v]) {
                if(idx[to] != -1) continue;
                que.push(to);
                idx[to] = tour.size();
                tour.push_back(to);

                p[0][to] = to;
                FOR(i, 1, maxd+1) p[i][to] = p[i-1][v];

                REP(i, maxd+1) {
                    if(p[i][to] == -1) continue;
                    if(l[i][p[i][to]] == -1) l[i][p[i][to]] = idx[to];
                    r[i][p[i][to]] = idx[to]+1;
                }
            }
        }
    }
    // WMに乗せるとupdateなしオンラインクエリでdが大きい場合でもいけるらしい
    // 頂点vからの距離がd以下の頂点に対応する区間を列挙 O(d)
    void for_each(ll v, ll d, function<void(ll,ll)> f) {
        for(ll i=d; i>=0; --i) {
            if(p[i][v] == -1) continue;
            if(d-1>=i && l[d-1-i][p[i][v]]!=-1 && r[d-1-i][p[i][v]]!=-1) {
                f(l[d-1-i][p[i][v]], r[d-1-i][p[i][v]]);
            }
            if(l[d-i][p[i][v]]!=-1 && r[d-i][p[i][v]]!=-1) {
                f(l[d-i][p[i][v]], r[d-i][p[i][v]]);
            }
        }
    }
};
// END CUT

// verify: 2019/10/05
// https://yukicoder.me/problems/no/899
namespace yukicoder899 {
    template <typename Monoid>
    struct lazysegtree {
        using T = typename Monoid::T;
        using E = typename Monoid::E;
        int n, height;
        vector<T> dat;
        vector<E> lazy;

        lazysegtree() {}
        lazysegtree(int n_) {
            n = 1, height = 0;
            while(n < n_) { n *= 2; height++; }
            dat.assign(n*2, Monoid::dt());
            lazy.assign(n*2, Monoid::de());
        }
        void build(vector<T> v) {
            REP(i, v.size()) dat[i+n] = v[i];
            for(int i=n-1; i>0; --i) dat[i] = Monoid::f(dat[i*2], dat[i*2+1]);
        }

        inline T reflect(int k) { return lazy[k]==Monoid::de()?dat[k]:Monoid::g(dat[k], lazy[k]); }
        inline void eval(int k) {
            if(lazy[k] == Monoid::de()) return;
            lazy[2*k]   = Monoid::h(lazy[k*2],   lazy[k]);
            lazy[2*k+1] = Monoid::h(lazy[k*2+1], lazy[k]);
            dat[k] = reflect(k);
            lazy[k] = Monoid::de();
        }
        inline void thrust(int k) { for(int i=height;i;--i) eval(k>>i); }
        inline void recalc(int k) { while(k>>=1) dat[k] = Monoid::f(reflect(k*2), reflect(k*2+1)); }

        void update(int a, int b, E x) {
            thrust(a+=n);
            thrust(b+=n-1);
            for(int l=a, r=b+1; l<r; l>>=1,r>>=1) {
                if(l&1) lazy[l] = Monoid::h(lazy[l], x), ++l;
                if(r&1) --r, lazy[r] = Monoid::h(lazy[r], x);
            }
            recalc(a);
            recalc(b);
        }
        T query(int a, int b) {
            thrust(a+=n);
            thrust(b+=n-1);
            T vl=Monoid::dt(), vr=Monoid::dt();
            for(int l=a, r=b+1; l<r; l>>=1,r>>=1) {
                if(l&1) vl=Monoid::f(vl, reflect(l++));
                if(r&1) vr=Monoid::f(reflect(--r), vr);
            }
            return Monoid::f(vl, vr);
        }

        friend ostream &operator <<(ostream& out,const lazysegtree<Monoid>& seg) {
            out << "---------------------" << endl;
            int cnt = 1;
            for(int i=1; i<=seg.n; i*=2) {
                REP(j, i) {
                    out << "(" << seg.dat[cnt].sum << "," << seg.lazy[cnt] << ") ";
                    cnt++;
                }
                out << endl;
            }
            out << "---------------------" << endl;
            return out;
        }
    };

    struct node {
        ll sum, max, min, len;
        node() : sum(0), max(-LLINF), min(LLINF), len(0) {}
        node(ll a, ll b, ll c, ll d) : sum(a), max(b), min(c), len(d) {}
    };
    struct linear_exp {
        using T = node;
        using E = PII;
        static T dt() { return node(); }
        static constexpr E de() { return PII(1, 0); }
        static T f(const T &a, const T &b) {
            node ret;
            ret.sum = a.sum + b.sum;
            ret.min = min(a.min, b.min);
            ret.max = max(a.max, b.max);
            ret.len = a.len + b.len;
            return ret;
        }
        static T g(const T &a, const E &b) {
            node ret;
            ret.sum = b.first*a.sum+b.second*a.len;
            ret.min = b.first*a.min+b.second;
            ret.max = b.first*a.max+b.second;
            ret.len = a.len;
            return ret;
        }
        static E h(const E &a, const E &b) {
            return PII(b.first*a.first, b.first*a.second+b.second);
        }
    };

    void solve() {
        cin.tie(0);
        ios::sync_with_stdio(false);

        ll n;
        cin >> n;
        bfsEulerTour tour(n, 2);
        REP(i, n-1) {
            ll u, v;
            cin >> u >> v;
            tour.add_edge(u, v);
        }
        vector<ll> a(n);
        REP(i, n) cin >> a[i];
        tour.build();

        lazysegtree<linear_exp> seg(n+2);
        seg.build(vector<node>(n+2, node(0, 0, 0, 1)));
        REP(i, n) {
            tour.for_each(i, 0, [&](ll u, ll v){
                seg.update(u, v, PII(0, a[i]));
            });
        }

        ll q;
        cin >> q;
        while(q--) {
            ll x;
            cin >> x;

            ll ret = 0;
            tour.for_each(x, 2, [&](ll u, ll v){
                ret += seg.query(u, v).sum;
                seg.update(u, v, PII(0, 0));
            });
            tour.for_each(x, 0, [&](ll u, ll v){
                seg.update(u, v, PII(1, ret));
            });
            cout << ret << endl;
        }
    }
}