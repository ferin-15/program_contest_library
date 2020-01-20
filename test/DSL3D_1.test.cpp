#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D&lang=ja"
#include "../memo/macro.hpp"
#include "../data_structure/sliding_window_aggregation.cpp"

int main() {
    ll n, l;
    cin >> n >> l;
    vector<ll> a(n);
    REP(i, n) cin >> a[i];

    auto f = [&](ll x, ll y) { return min(x, y); };
    SWAG<ll,ll,decltype(f)> swag(f, INF);

    REP(i, l-1) swag.push_back(a[i]);
    FOR(i, l-1, n) {
        swag.push_back(a[i]);
        ll ret;
        auto ask = [&](ll x, ll y) { ret = min(x, y); };
        swag.fold(ask);
        cout << ret << (i==n-1?'\n':' ');
        swag.pop_front();
    }
}