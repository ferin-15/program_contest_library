#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1617&lang=jp"
#include "../memo/macro.hpp"
#include "../string/string_split.cpp"

int main(void) {
    while(1) {
        string s, t;
        cin >> s;
        if(s == ".") break;
        cin >> t;

        if(s == t) {
            cout << "IDENTICAL\n";
            continue;
        }

        auto vs = split(s, '\"'), vt = split(t, '\"');
        if(vs.size() != vt.size()) {
            cout << "DIFFERENT\n";
            continue;
        }
        
        ll cnt = 0;
        bool diff = false;
        const ll sz = vs.size();
        REP(i, sz) {
            if(i%2==0) {
                if(vs[i] != vt[i]) {
                    diff = true;
                    break;
                }
            } else if(vs[i] != vt[i]) {
                cnt++;
            }
        }
        if(cnt > 1) diff = true;

        if(diff) cout << "DIFFERENT\n";
        else cout << "CLOSE\n";
    }

    return 0;
}