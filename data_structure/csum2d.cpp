// BEGIN CUT
template<class T>
class csum2d {
    ll h, w;
    vector<vector<T>> rui;
public:
    csum2d(vector<vector<T>> v) : h(v.size()), w(v[0].size()), rui(v) {
        REP(i, h) REP(j, w) {
            if(!i && !j) {}
            else if(!i) rui[i][j] += rui[i][j-1];
            else if(!j) rui[i][j] += rui[i-1][j];
            else rui[i][j] += rui[i-1][j]+rui[i][j-1]-rui[i-1][j-1];
        }
    }
    T get(ll sx, ll sy, ll gx, ll gy) {
        if(!sx && !sy) return rui[gy][gx];
        if(!sx) return rui[gy][gx]-rui[sy-1][gx];
        if(!sy) return rui[gy][gx]-rui[gy][sx-1];
        return rui[gy][gx]-rui[sy-1][gx]-rui[gy][sx-1]+rui[sy-1][sx-1];
    };
};
// END CUT