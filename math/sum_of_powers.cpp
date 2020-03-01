// \sum_{i=0}^{n-1} i^k O(k^2)
// kが固定でクエリがいっぱいならベルヌーイ数を前計算で高速化
mint sum_of_powers(ll n, ll k) {
    vector<mint> b(k+1), po(k+2);
    b[0] = po[0] = 1;
    FOR(i, 1, k+2) po[i] = po[i-1] * n;
    FOR(i, 1, k+1) {
        REP(j, i) b[i] += combi(i+1, j) * b[j];
        b[i] /= -(i+1);
    }
    mint sum = 0;
    REP(i, k+1) sum += combi(k+1, i) * b[i] * po[k+1-i];
    return sum / (k+1);
}

// FPSとかでベルヌーイ数をklogkとかあるっぽい…？