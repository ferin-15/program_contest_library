// 頂点iから最も遠い頂点を求める全方位木DP
// dist[i] = iの高さ
vector<ll> dist(n);
function<void(ll,ll)> dfs1 = [&](ll v, ll p) {
  for(auto i: g[v]) if(i != p) {
    dfs1(i, v);
    chmax(dist[v], dist[i] + 1);
  }
};

dfs1(0, -1);

// ans[i] = (頂点iから最も遠い頂点)
vector<ll> ans(n);
function<void(ll,ll,ll)> dfs2 = [&](ll v, ll d_par, ll p) {
  // vの子の情報を集める
  vector<PII> d_child;
  // d_child[0], d_child[1]が存在しないのを防ぐ
  d_child.PB({0, -1});
  for(auto i: g[v]) {
    if(i == p) d_child.PB({d_par+1, i});
    else d_child.PB({dist[i]+1, i});
  }
  // 隣接する頂点からの遷移について最大を取る
  sort(ALL(d_child), greater<>());
  ans[v] = d_child[0].first;
  for(auto i: g[v]) if(i != p) {
    // d_parはd_childの最大が基本、最大が頂点iの部分木なら次に大きいのをd_parにする
    dfs2(i, d_child[d_child[0].second == i].first, v);
  }
};

dfs2(0, 0, -1);