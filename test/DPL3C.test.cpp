#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/3/DPL_3_C"
#include "../memo/macro.hpp"
#include "../DP/largest_Rectangle.cpp"

signed main(void) {
    ll n;
    cin >> n;
    vector<ll> h(n);
    REP(i, n) cin >> h[i];

    cout << largest_rectangle_histogram(h) << endl;

    return 0;
}