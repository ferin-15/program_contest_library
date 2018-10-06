#include <bits/stdc++.h>
using namespace std;

// 頂点数、変数
int v, e;
const int MAX_N = 10010;
// 隣接リスト
vector<int> g[MAX_N];
bool used[MAX_N];
// トポロジカルソートされた数列
vector<int> ans;

void dfs(int u) {
  if(used[u]) return;
  used[u] = true;
  for(auto& i: g[u]) dfs(i);
  // 帰りがけ順で追加
  ans.push_back(u);
}

void tsort() {
  for(int i=0; i<v; ++i) dfs(i);
  reverse(ans.begin(), ans.end());
}

signed main(void)
{
  cin >> v >> e;
  for(int i=0; i<e; ++i) {
    int s, t;
    cin >> s >> t;
    g[s].push_back(t);
  }

  tsort();
  for(int i: ans) cout << i << endl;

  return 0;
}
