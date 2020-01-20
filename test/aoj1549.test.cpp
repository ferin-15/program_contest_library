#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1549"
#include "../memo/macro.hpp"
#include "../data_structure/wavelet_matrix.cpp"

int main() {
    ll n;
    cin >> n;
    const int offset = 1000000;
    array<int, 100000> a;
    REP(i, n) cin >> a[i], a[i] += offset;
    wavelet<int, 100000, 30> wm(n, a);

    ll q;
    cin >> q;
    REP(i, q) {
        ll l, r, d;
        cin >> l >> r >> d;
        d += offset;
        ll num = wm.rank_lt(l, r+1, d), ret = INF;
        ll v1 = wm.kthnumber(l, r+1, num-1);
        if(v1 != -1) chmin(ret, d - v1);
        ll v2 = wm.kthnumber(l, r+1, num);
        if(v2 != -1) chmin(ret, v2 - d);
        cout << ret << "\n";
    }
    cout << flush;
}