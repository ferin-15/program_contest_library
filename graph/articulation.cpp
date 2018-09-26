// BEGIN CUT
// hecさんの写経 自分ではverifyしてない
// 関節点を求める
VI articulation;
vector<bool> is_articulation(n, false);
auto articulation_point = [&]() {
  REP(i, n) {
    if(root[i]) {
      int d = 0;
      for(auto e: g[i]) if(par[e.first] == i) d++;
      if(d >= 2) articulation.PB(i), is_articulation[i] = true;
    } else {
      for(auto e: g[i]) {
        if(i == par[e.first] && ord[i] <= low[e.first]) {
          articulation.PB(i);
          is_articulation[i] = true;
          break;
        }
      }
    }
  }
};
articulation_point();
// END CUT
