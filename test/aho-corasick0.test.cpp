#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2873&lang=jp"
#include "../memo/macro.hpp"
#include "../string/aho-corasick.cpp"

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int n;
    string s;
    cin >> s >> n;
    vector<string> p(n);
    REP(i, n) cin >> p[i];

    AhoCorasick<26> aho(p);

    int ret = 0, now = aho.root;
    for(auto c: s) {
        now = aho.next(now, c);
        if(aho.nodes[now].matched.size()) {
            ret++;
            now = aho.root;
        }
    }

    cout << ret << endl;

    return 0;
}