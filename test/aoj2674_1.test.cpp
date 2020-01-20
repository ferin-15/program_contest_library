#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2674"
#include "../memo/macro.hpp"
#include "../data_structure/segtree_range_freq.cpp"

int main() {
    ll n;
    cin >> n;
    vector<vector<ll>> x(n);
    REP(i, n) x[i].resize(1), cin >> x[i][0];
    segTreeRangeFreq seg(x);

    ll q;
    cin >> q;
    vector<ll> ans(q);
    REP(i, q) {
        ll l, r, e;
        cin >> l >> r >> e;
        l--, r--;
        ll a = min(x[l][0], x[r][0]), b = max(x[l][0], x[r][0]);
        cout << r-l+1 - (seg.query(l, r+1, b+e) - seg.query(l, r+1, a-e-1)) << "\n";
    }
    cout << flush;
}