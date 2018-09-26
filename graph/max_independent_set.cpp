// BEGIN CUT
// n頂点m辺のグラフの最大独立集合を求める
// O(n*1.466^n) n=40くらいまで大丈夫
// CODE THANKS FESTIVAL 2017 G - Mixture Drug で verify
int n, m;
VI g[40];

int func(int v, VI& used) {
  if(v == n) return 0;

  int ret = 0;
  if(!used[v]) {
    VI n = {v};
    for(int i: g[v]) if(!used[i]) n.PB(i);
    for(int i: n) used[i] = 1;
    chmax(ret, func(v+1, used) + 1);
    for(int i: n) used[i] = 0;
  }

  int d = 0;
  for(int i: g[v]) if(!used[i]) d++;
  if(d > 1 || used[v]) {
    if(!used[v]) {
      used[v] = 1;
      chmax(ret, func(v+1, used));
      used[v] = 0;
    } else {
      chmax(ret, func(v+1, used));
    }
  }

  return ret;
}

signed main(void)
{
  cin >> n >> m;
  REP(i, m) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    g[a].PB(b);
    g[b].PB(a);
  }
  VI used(n, 0);
  cout << func(0, used) << endl;

  return 0;
}
// END CUT