#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/3/DPL_3_C"
#include "../DP/largest_Rectangle.cpp"

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n;
    cin >> n;
    vector<ll> h(n);
    REP(i, n) cin >> h[i];

    cout << largest_rectangle_histogram(h) << endl;

    return 0;
}