/**
* @file zenhoui.cpp
* @brief 全方位木DP
* @detail verify: 色々
* @author ferin
*/

// BEGIN CUT
// 頂点iから最も遠い頂点を求める全方位木DP
// dist[i] = iの高さ
VI dist(n);
function<void(int,int)> dfs1 = [&](int v, int p) {
  for(int &i: g[v]) if(i != p) {
    dfs1(i, v);
    chmax(dist[v], dist[i] + 1);
  }
};

dfs1(0, -1);

// ans[i] = (頂点iから最も遠い頂点)
VI ans(n);
function<void(int,int,int)> dfs2 = [&](int v, int d_par, int p) {
  // vの子の情報を集める
  vector<PII> d_child;
  // d_child[0], d_child[1]が存在しないのを防ぐ
  d_child.PB({0, -1});
  for(int &i: g[v]) {
    if(i == p) d_child.PB({d_par+1, i});
    else d_child.PB({dist[i]+1, i});
  }
  sort(ALL(d_child), greater<>());
  ans[v] = d_child[0].first;
  for(int &i: g[v]) if(i != p) {
    // pvalはd_childの最大が基本
    // 最大が頂点iの部分木ならそれがpvalにはならないので次に大きいのをpvalにする
    dfs2(i, d_child[d_child[0].second == i].first, v);
  }
};

dfs2(0, 0, -1);
// END CUT
