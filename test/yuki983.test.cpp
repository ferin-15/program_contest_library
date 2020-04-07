#define PROBLEM "https://yukicoder.me/problems/no/983"
#include "../memo/macro.hpp"
#include "../math/fzt_fmt.cpp"

int main(void) {
    ll n;
    cin >> n;
    vector<ll> a(n);
    REP(i, n) {
        cin >> a[i];
        if(a[i]==-1) a[i] = 0;
    }

    if(n <= 20) {
        auto v = convAND(a, a);
        ll g = 0;
        REP(i, n) g = gcd(g, v[i]);
        cout << (g==0 ? -1 : g) << endl;
    } else {
        ll g = 0;
        REP(i, n) g = gcd(g, a[i]);
        cout << (g==0 ? -1 : g*g) << endl;
    }

    return 0;
}