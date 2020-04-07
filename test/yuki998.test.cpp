#define PROBLEM "https://yukicoder.me/problems/no/998"
#include "../memo/macro.hpp"

signed main(void) {
    vector<ll> v(4);
    REP(i, 4) cin >> v[i];
    sort(ALL(v));

    bool flag = true;
    FOR(i, 1, 4) if(v[i] != v[i-1]+1) flag = false;
    if(flag) cout << "Yes" << endl;
    else cout << "No" << endl;

    return 0;
}