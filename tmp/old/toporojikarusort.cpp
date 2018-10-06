//グラフの隣接リスト
VI g[100010];
//頂点の入次数を管理
int h[100010];
signed main(void)
{
  //頂点数v、辺の数e
  int v, e;
  cin >> v >> e;
  REP(i, e) {
    int s, t;
    cin >> s >> t;
    //頂点sから頂点tへの有向辺
    g[s].push_back(t);
    h[t]++;
  }

  //入次数が0の頂点の集合
  stack<int> st;

  //入次数が0の頂点であればstに追加
  REP(i, v) if(h[i] == 0) st.push(i);

  //ソートされた後のグラフ
  VI ans;
  //stがなくなるまでループ
  while(st.size()) {
    //stの集合のから一つ取り出す
    int i = st.top(); st.pop();
    ans.push_back(i);
    for(auto& j: g[i]) {
      //隣接する頂点の入次数をマイナス1
      h[j]--;
      //これによって入次数が0になればstに追加
      if(h[j] == 0) st.push(j);
    }
  }

  //ansを順に出力
  for(int i: ans) cout << i << endl;

  return 0;
}
