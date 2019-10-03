#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2659
#include "../math/CRT.cpp"

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n, m, d;
    cin >> n >> m >> d;
    vector<ll> a(m);
    REP(i, m) cin >> a[i];
    REP(i, d) {
        vector<ll> x, y;
        REP(j, m) {
            ll r;
            cin >> r;
            if(r == -1) continue;
            x.push_back(r);
            y.push_back(a[j]);
        }

        vector<ll> v(x.size(), 1);
        PII p = crt(v, x, y);
        // p.second * k + p.first <= n である最大の整数
        if(p.first == -1 || n < p.first) {
            cout << -1 << endl;
            return 0;
        }
        ll k = (n-p.first) / p.second;
        n = p.second * k + p.first;
    }
    cout << n << endl;

    return 0;
}