#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1308"
#include "../memo/macro.hpp"
#include "../math/binary_matrix.cpp"

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    while(true) { 
        ll h, w, d;
        cin >> w >> h >> d;
        if(!w) break;
        vector<vector<ll>> s(h, vector<ll>(w));
        REP(i, h) REP(j, w) cin >> s[i][j];

        matrix<630> mat(h*w);
        REP(y, h) REP(x, w) {
            mat.dat[y*w+x][y*w+x] = 1;
            REP(i, h) REP(j, w) {
                if(abs(y-i)+abs(x-j) != d) continue;
                mat.dat[y*w+x][i*w+j] = 1;
            }
            mat.dat[y*w+x][h*w] = 1 - s[y][x];
        }

        bool ans = true;
        gauss_jordan(mat);
        REP(i, h*w) {
            bool flag = true;
            REP(j, h*w) if(mat.dat[i][j]) { flag = false; break; } 
            if(flag && mat.dat[i][h*w] == 1) ans = false; 
        }

        if(ans) cout << 1 << endl;
        else cout << 0 << endl;
    }

    return 0;
}