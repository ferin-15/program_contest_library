struct segTreeRangeFreq {
  int n;
  VV<int> dat;
  // aとbのマージを行う 
  V<int> f(V<int> a, V<int> b) {
    V<int> ret;
    int idx1 = 0, idx2 = 0;
    while(idx1 < a.size() || idx2 < b.size()) {
      if(idx2 >= b.size() || (idx1 < a.size() && a[idx1] < b[idx2])) ret.push_back(a[idx1]), idx1++;
      else ret.push_back(b[idx2]), idx2++;
    }
    return ret;
  }
  // 初期化 O(NlogN)
  segTreeRangeFreq() {}
  segTreeRangeFreq(V<int> v) {
    n = 1; while(n < v.size()) n *= 2;
    dat.assign(2*n-1, {});
    REP(i, v.size()) dat[i+n-1] = {v[i]};
    for(int i=n-2; i>=0; --i) dat[i] = f(dat[i*2+1], dat[i*2+2]);
  }
  // [a, b) のx以下の個数を返す O(log^2N)
  int query(int a, int b, int x, int k, int l, int r) {
    if(b <= l || r <= a) return 0;
    if(a <= l && r <= b) return upper_bound(ALL(dat[k]), x) - dat[k].begin();
    int vl = query(a, b, x, k*2+1, l, (l+r)/2);
    int vr = query(a, b, x, k*2+2, (l+r)/2, r);
    return vl + vr;
  }
  int query(int a, int b, int x) { return query(a, b, x, 0, 0, n); }
};

// 2次元平面上の点集合 矩形中に何個点があるかのクエリに答えることが可能
// (x[i], y[i]) をxでソートしてyをセグ木に乗せるとrangefreqになる
// wavelet matrixじゃなくてセグ木でO(log^2N)でok