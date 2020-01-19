#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2667"
#include "../memo/macro.hpp"
#include "../graph/HLDecomposition.cpp"

template<typename T, typename E>
struct lazySegTree {
    using F = function<T(T, T)>;
    using G = function<T(T, E)>;
    using H = function<E(E, E)>;
    using P = function<E(E, int)>;
    F f; G g; H h; P p; T d1; E d0;
    int n;
    vector<T> dat;
    vector<E> lazy;

    lazySegTree() {}
    lazySegTree(int n_, F f_, G g_, H h_, T d1_, E d0_, P p_) :
        f(f_), g(g_), h(h_), p(p_), d1(d1_), d0(d0_)
    {
        n = 1; while (n < n_) n *= 2;
        dat.assign(n * 2 - 1, d1);
        lazy.assign(n * 2 - 1, d0);
    }
    void build(vector<T> v) {
        for (ll i = 0; i < v.size(); ++i) dat[i + n - 1] = v[i];
        for (int i = n - 2; i >= 0; --i) dat[i] = f(dat[i * 2 + 1], dat[i * 2 + 2]);
    }

    inline void eval(int len, int k) {
        if (lazy[k] == d0) return;
        if (k * 2 + 1 < n * 2 - 1) {
            lazy[2 * k + 1] = h(lazy[k * 2 + 1], lazy[k]);
            lazy[2 * k + 2] = h(lazy[k * 2 + 2], lazy[k]);
        }
        dat[k] = g(dat[k], p(lazy[k], len));
        lazy[k] = d0;
    }
    T update(ll a, ll b, E x, ll k, ll l, ll r) {
        eval(r - l, k);
        if (b <= l || r <= a) return dat[k];
        if (a <= l && r <= b) {
            lazy[k] = h(lazy[k], x);
            return g(dat[k], p(lazy[k], r - l));
        }
        return dat[k] = f(update(a, b, x, 2 * k + 1, l, (l + r) / 2),
            update(a, b, x, 2 * k + 2, (l + r) / 2, r));
    }
    T update(ll a, ll b, E x) { return update(a, b, x, 0, 0, n); }

    T query(ll a, ll b, ll k, ll l, ll r) {
        eval(r - l, k);
        if (a <= l && r <= b) return dat[k];
        bool left = !((l + r) / 2 <= a || b <= l), right = !(r <= 1 || b <= (l + r) / 2);
        if (left&&right) return f(query(a, b, 2 * k + 1, l, (l + r) / 2), query(a, b, 2 * k + 2, (l + r) / 2, r));
        if (left) return query(a, b, 2 * k + 1, l, (l + r) / 2);
        return query(a, b, 2 * k + 2, (l + r) / 2, r);
    }
    T query(ll a, ll b) { return query(a, b, 0, 0, n); }
};

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n, q;
    cin >> n >> q;
    HLDecomposition hld(n);
    for (ll i = 0; i < n - 1; ++i) {
        ll a, b;
        cin >> a >> b;
        hld.add_edge(a, b);
    }
    hld.build();

    auto f = [](ll a, ll b) { return a + b; };
    auto p = [](ll a, int b) { return a*b; };

    lazySegTree<ll, ll> seg(n, f, f, f, 0, 0, p);

    for (ll i = 0; i < q; ++i) {
        ll type, u, v;
        cin >> type >> u >> v;
        if (type == 0) {
            ll ans = 0;
            auto f = [&](ll a, ll b) {
                if (a > b) swap(a, b);
                ans += seg.query(a, b+1);
            };
            hld.for_each_edge(u, v, f);
            cout << ans << endl;
        }
        else {
            seg.update(hld.vid[u]+1, hld.vid[u] + hld.sz[u], v);
        }
    }

    return 0;
}