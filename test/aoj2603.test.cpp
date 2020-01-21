#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2603"
#include "../memo/macro.hpp"
#include "../DP/monotone_minima.cpp"

int main(void) {
    ll s, n, m;
    cin >> s >> n >> m;
    vector<ll> x(s), t(n), p(n);
    REP(i, s) cin >> x[i];
    REP(i, n) cin >> t[i] >> p[i], p[i]--;

    vector<ll> v(n);
    REP(i, n) v[i] = t[i] - x[p[i]];
    sort(ALL(v));
    vector<ll> rui(n+1);
    REP(i, n) rui[i+1] = rui[i]+v[i];

    vector<ll> dp(n+1, INF);
    dp[0] = 0;
    REP(k, m) {
        auto f = [&](ll i, ll j) {
            return i<j ? INF : dp[j]+(i?v[i-1]:0)*(i-j)-(rui[i]-rui[j]);
        };
        auto ndp = monotone_minima<ll>(n+1, n+1, f); 
        REP(i, n+1) dp[i] = ndp[i].second;
    }
    cout << dp[n] << endl;

    return 0;
}