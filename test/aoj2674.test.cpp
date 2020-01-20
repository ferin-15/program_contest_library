#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2674"
#include "../memo/macro.hpp"
#include "../data_structure/wavelet_matrix.cpp"

int main() {
    ll n;
    cin >> n;
    array<int, 100000> x;
    const int offset = 2e8;
    REP(i, n) cin >> x[i], x[i] += offset;
    wavelet<int, 100000, 30> wm(n, x);

    ll q;
    cin >> q;
    vector<ll> ans(q);
    REP(i, q) {
        ll l, r, e;
        cin >> l >> r >> e;
        l--, r--;
        ll a = min(x[l], x[r]), b = max(x[l], x[r]);
        cout << r-l+1 - wm.rangefreq(l, r+1, a-e, b+e+1) << "\n";
    }
    cout << flush;
}