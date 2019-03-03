// 階段行列を求める O(HW^2/64)
// 列に応じてbitsetのbit長を変えろ
using mat = vector<bitset<64>>;
mat gauss_jordan(mat a) {
    const int h = a.size(), w = a[0].size();
    int rank = 0;
    REP(i, min(w, h)) {
        int pivot = -1;
        FOR(j, rank, h) if(a[j][i]) {pivot = j; break;}
        if(pivot == -1) continue;
        swap(a[rank], a[pivot]);
        REP(j, h) if(j != rank && a[j][i]) a[j] ^= a[rank];
        rank++;
    }
    return a;
}

// 行列式を求める todo:verify
int determinant(mat a) {
    const int h = a.size(), w = a[0].size();
    assert(h==w);
    ll ret = 1;
    mat b = gauss_jordan(a);
    REP(i, h) ret *= b[i][i];
} 