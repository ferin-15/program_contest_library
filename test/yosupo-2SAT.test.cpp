#define PROBLEM "https://judge.yosupo.jp/problem/two_sat"
#include "../memo/macro.hpp"
#include "../graph/SCC.cpp"
#include "../graph/twosat.cpp"

int main () {
    ll n, m;
    string ss;
    cin >> ss >> ss >> n >> m;
    twoSAT graph(n);
    REP(i, m) {
        ll a, b, c;
        cin >> a >> b >> c;
        pair<ll, bool> p1, p2;
        if(a < 0) p1 = {-a-1, false};
        else p1 = {a-1, true};
        if(b < 0) p2 = {-b-1, false};
        else p2 = {b-1, true};
        graph.add(p1, p2);
    }

    if(!graph.solve()) {
        cout << "s UNSATISFIABLE" << endl;
        return 0;
    }

    cout << "s SATISFIABLE" << endl;
    cout << "v ";
    REP(i, n) cout << (graph.ans[i] ? 1 : -1) * (i+1) << " ";
    cout << "0" << endl;
}