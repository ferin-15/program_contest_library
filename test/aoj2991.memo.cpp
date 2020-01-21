#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2991"
#include "../memo/macro.hpp"
#include "../graph/SCC.cpp"
#include "../graph/twosat.cpp"

// これスペシャルジャッジ
int main() {
    ll n, x, a, o;
    cin >> n >> x >> a >> o;

    if(x == 0) {
        cout << "No" << endl;
        return 0;
    }

    const ll m = 1LL<<(n+1);
    twoSAT sat(m);
    // xor
    REP(i, m) {
        sat.add({i, false}, {x^i, false});
        sat.add({i, true}, {x^i, true});
    }
    // and
    REP(i, m) {
        if((i&a)!=a) continue;
        ll sub = (m-1)^i;
        while(true) {
            sat.add({i, false}, {a^sub, false});
            if(sub == 0) break;
            sub = (sub-1) & ((m-1)^i);
        }
    }
    // or
    REP(i, m) {
        if((i|o)!=o) continue;
        ll sub = i;
        while(true) {
            sat.add({i, false}, {((~i)&o)^sub, false});
            if(sub == 0) break;
            sub = (sub-1) & i;
        }
    }

    if(!sat.solve()) {
        cout << "No" << endl;
        return 0;
    }
    cout << "Yes" << endl;
    vector<ll> ret;
    REP(i, m) if(sat.ans[i]) ret.push_back(i);
    REP(i, m/2) cout << ret[i] << (i==m/2-1?'\n':' ');

    return 0;
}