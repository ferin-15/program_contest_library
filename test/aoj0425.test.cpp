#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0425"
#include "../memo/macro.hpp"
#include "../data_structure/Mo.cpp"

int main(void) {
    ll n, k, q;
    cin >> n >> k >> q;
    vector<ll> a(k), b(k);
    REP(i, k) cin >> a[i] >> b[i], a[i]--, b[i]--;
    vector<ll> type(q), s(q), t(q), x(q);
    REP(i, q) cin >> type[i] >> s[i] >> t[i] >> x[i], s[i]--, t[i]--, x[i]--;

    vector<ll> c(n), d(n);
    iota(ALL(c), 0); 
    iota(ALL(d), 0);
    auto moveL = [&](ll v) {
        ll p1 = d[a[v]], p2 = d[b[v]];
        swap(c[p1], c[p2]);
        swap(d[c[p1]], d[c[p2]]);
    };
    auto moveR = [&](ll v) {
        ll p1 = a[v], p2 = b[v];
        swap(c[p1], c[p2]);
        swap(d[c[p1]], d[c[p2]]);
    };
    Mo mo(k, moveL, moveR, moveL, moveR);
    REP(i, q) mo.insert(s[i], t[i]+1);
    mo.build();

    vector<ll> ans(q);
    REP(i, q) {
        ll idx = mo.process();
        if(type[idx] == 1) ans[idx] = c[x[idx]];
        else ans[idx] = d[x[idx]];
    }

    REP(i, q) cout << ans[i]+1 << "\n";
    cout << flush;

    return 0;
}