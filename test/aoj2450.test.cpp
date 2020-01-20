#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2450"
#include "../memo/macro.hpp"
#include "../data_structure/linkcuttree.cpp"

struct submax { 
    ll lsum, rsum, max, sum;
    submax() {}
    submax(ll a, ll b, ll c, ll d) : lsum(a), rsum(b), max(c), sum(d) {}
};
struct monoid {
    using T = submax;
    using E = ll;
    static T T0() { return submax(-INF, -INF, -INF, 0); }
    static constexpr E E0() { return INF; }
    static T f(const T &x, const T &y) { 
        T ret;
        ret.lsum = max(x.lsum, x.sum+y.lsum);
        ret.rsum = max(y.rsum, x.rsum+y.sum);
        ret.max = max({x.max, y.max, x.rsum+y.lsum});
        ret.sum = x.sum + y.sum;
        return ret; 
    }
    static T g(const T &x, const E &y, int sz) { 
        T ret;
        ret.max = max(y, y*sz);
        ret.sum = y * sz;
        ret.lsum = ret.max;
        ret.rsum = ret.max;
        return ret;
    }
    static E h(const E &x, const E &y) { 
        return y;
    }
    static T s(const T &x) { 
        T ret(x);
        swap(ret.lsum, ret.rsum);
        return ret;
    }
};

int main(void) {
    ll n, q;
    cin >> n >> q;
    vector<ll> w(n);
    REP(i, n) cin >> w[i];
    vector<submax> init(n);
    REP(i, n) init[i] = submax(w[i], w[i], w[i], w[i]);
    LinkCutTree<monoid> lct(init);
    REP(i, n-1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        lct.link(u, v);
    }
    REP(i, q) {
        ll t, a, b, c;
        cin >> t >> a >> b >> c;
        a--, b--;
        if(t == 1) {
            lct.range(a, b, c);
        } else {
            cout << lct.query(a, b).max << "\n";
        }
    }

    return 0;
}