#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/3/DPL_3_B"
#include "../memo/macro.hpp"
#include "../DP/largest_Rectangle.cpp"

signed main(void) {
    ll h, w;
    cin >> h >> w;
    vector<vector<ll>> c(h, vector<ll>(w));
    REP(i, h) REP(j, w) cin >> c[i][j];

    cout << largeest_rectangle(c) << endl;

    return 0;
}