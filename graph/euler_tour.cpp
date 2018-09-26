// オイラーツアー
int cnt = 0;
vector<PII> idx(n);
function<void(int,int)> dfs = [&](int x, int p) {
  idx[x].first = cnt;
  for(int i: g[x]) {
    if(i == p) continue;
    dfs(i, x);
  }
  idx[x].second = ++cnt;
};
dfs(0, -1);
