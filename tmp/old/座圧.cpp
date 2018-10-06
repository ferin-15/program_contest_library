// xx, yy, zzにそれぞれ座圧する元の配列を突っ込むとx, y, zが座圧された配列で返ってくる
// zip[座圧前] = 座圧後、unzip[座圧後] = 座圧前
VL xx, x, unzip(100010);
unordered_map<int, int> zip;
void compress() {
  x = xx;
  sort(ALL(xx));
  xx.erase(unique(ALL(xx)), xx.end());
  REP(i, xx.size()) {zip[xx[i]] = i; unzip[i] = xx[i];}
  REP(i, x.size()) x[i] = zip[x[i]];
}

// 書くのが簡単な座圧
REP(i, n) cin >> aa[i], a[i] = aa[i];

aa.PB(-1);
sort(ALL(aa)); aa.erase(unique(ALL(aa)), aa.end());
REP(i, n) a[i] = lower_bound(ALL(aa), a[i]) - aa.begin();
