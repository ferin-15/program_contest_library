// hecさんの写経 自分ではverifyしてない
// n頂点のグラフgについてlow_linkを求める
VI ord(n, -1), low(n, -1), par(n, -1);
vector<bool> root(n, false);
auto low_link = [&]() {
  int k = 0;

  function<void(int,int,int&)> dfs = [&](int v, int p, int &k) {
    ord[v] = k++, low[v] = ord[v], par[v] = p;
    for(auto e: g[v]) {
      if(e.first == p) continue;
      if(ord[e.first] == -1) {
        dfs(e.first, v, k);
        chmin(low[v], low[e.first]);
      } else {
        chmin(low[v], low[e.first]);
      }
    }
  };

  REP(i, n) if(ord[i] == -1) dfs(i, -1, k), root[i] = true;
};
low_link();