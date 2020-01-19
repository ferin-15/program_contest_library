struct segTreeRangeFreq {
    int n;
    vector<vector<ll>> dat;
    // 初期化 O(NlogN)
    segTreeRangeFreq() {}
    segTreeRangeFreq(vector<vector<ll>> v) {
        n = 1; while(n < (ll)v.size()) n *= 2;
        dat.resize(2*n-1);
        REP(i, v.size()) dat[i+n-1] = v[i];
        for(int i=n-2; i>=0; --i) {
            dat[i].resize(dat[i*2+1].size() + dat[i*2+2].size());
            merge(ALL(dat[i*2+1]), ALL(dat[i*2+2]), dat[i].begin());
        }
    }
    // [a, b) のx以下の個数を返す O(log^2N)
    int query(int a, int b, ll x, int k, int l, int r) {
        if(b <= l || r <= a) return 0;
        if(a <= l && r <= b) return upper_bound(ALL(dat[k]), x) - dat[k].begin();
        int vl = query(a, b, x, k*2+1, l, (l+r)/2);
        int vr = query(a, b, x, k*2+2, (l+r)/2, r);
        return vl + vr;
    }
    int query(int a, int b, ll x) { return query(a, b, x, 0, 0, n); }
};

// 2次元平面上の点集合 矩形中に何個点があるかのクエリに答えることが可能
// (x[i], y[i]) をxでソートしてyをセグ木に乗せるとrangefreqになる
// wavelet matrixじゃなくてセグ木でO(log^2N)でok
