#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2580
#include "../DP/convex_hull_trick.cpp"

ll dp[105][10010];
signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n, m, d, x;
    cin >> n >> m >> d >> x;
    vector<ll> p(n), a(m), b(m);
    REP(i, n) cin >> p[i];
    REP(i, m) cin >> a[i] >> b[i];

    REP(i, d) REP(j, n) dp[i][j] = LLINF;

    {
        ll num = 0;
        REP(j, m) {
            ll pos;
            if(b[j] >= 0) {
                pos = a[j]-b[j];
            } else {
                pos = a[j]+b[j];
            }
            if(pos >= p[0]) num++;
            a[j] += x;
        }
        REP(i, n) dp[0][i] = num * (p[i] - p[0]);
    }

    FOR(i, 1, d) {
        vector<ll> num(n);
        REP(j, m) {
            ll pos;
            if(b[j] >= 0) {
                pos = a[j]-b[j];
            } else {
                pos = a[j]+b[j];
            }
            ll tmp = upper_bound(ALL(p), pos) - p.begin() - 1;
            if(tmp >= 0) num[tmp]++;
            a[j] += x;
        }
        for(ll j=n-2; j>=0; --j) num[j] += num[j+1];

        ConvexHullTrick cht;
        REP(j, n) {
            cht.insert(num[j], dp[i-1][j]-num[j]*p[j]);
            dp[i][j] = cht.query(p[j]);
        }
    }

    ll ret = LLINF;
    REP(i, d) chmin(ret, dp[i][n-1]);
    cout << ret << endl;

    return 0;
}