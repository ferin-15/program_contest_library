#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1501"
#include "../memo/macro.hpp"
#include "../math/modint.cpp"
#include "../math/combination.cpp"

signed main(void) {
    ll h, w, ax, ay, bx, by;
    cin >> h >> w >> ay >> ax >> by >> bx;

    mint ans = 0;
    ll mi = INF;
    auto func = [&](ll gx, ll gy) {
        if(abs(ax-gx)+abs(ay-gy) < mi) {
            mi = abs(ax-gx) + abs(ay-gy);
            ans = combi(abs(ax-gx)+abs(ay-gy), abs(ax-gx));
        } else if(abs(ax-gx)+abs(ay-gy) == mi) {
            ans += combi(abs(ax-gx)+abs(ay-gy), abs(ax-gx));
        }
    };

    func(bx-w, by-h);
    func(bx-w, by);
    func(bx-w, by+h);
    func(bx, by-h);
    func(bx, by);
    func(bx, by+h);
    func(bx+w, by-h);
    func(bx+w, by);
    func(bx+w, by+h);

    cout << ans << endl;

    return 0;
}

