class SCC {
public:
  int V,K;    // 頂点数, scc後の頂点数
  vector<vector<int>> G;      // グラフの隣接リストの表現
  vector<vector<int>> rG;     // 辺の向きを逆にしたグラフ
  vector<vector<int>> DAG;    // scc後のグラフの隣接リストの表現
  vector<vector<int>> rDAG;   // scc後の辺の向きを逆にしたグラフ
  vector<int> vs;             // 帰りがけ順の並び
  vector<int> used;           // すでに調べたか
  vector<int> cmp;            // 属する強連結成分のトポロジカル順
  vector<vector<int>> member; // scc後の同一ノードの集合
  // vector<double> weight;   // i番目の連結成分が持つ情報
  // 初期化
  SCC() { V=K=-1; }
  SCC(int V_): V(V_) {
    G.assign(V_, vector<int>());
    rG.assign(V_, vector<int>());
    used.assign(V_, false);
    cmp.assign(V_, false);
    // weight.assign(V_, 1);
  }
  // 辺を追加
  void add_edge(int from,int to) {
    assert(from<V && to<V);
    G[from].push_back(to);
    rG[to].push_back(from);
  }
  // dfs
  void dfs(int v) {
    used[v]=true;
    for(int nx: G[v]) if(!used[nx]) dfs(nx);
    vs.push_back(v);
  }
  // 逆順dfs
  void rdfs(int v,int k) {
    used[v]=true;
    cmp[v]=k;
    // weight[k] *= p[v];
    for(int nx: rG[v]) if(!used[nx]) rdfs(nx,k);
  }
  // 2回dfsをする O(|V|+|E|)
  int scc() {
    // dfsする
    used.assign(V,0);
    vs.clear();
    for(int v=0;v<V;v++) if(!used[v]) dfs(v);
    // 逆順でdfs
    used.assign(V,0);
    int k=0;
    for(int i=vs.size()-1;i>=0;i--) if(!used[vs[i]]) rdfs(vs[i],k++);
    // i番目の連結成分について
    member.resize(k);
    for(int i=0;i<V;i++) member[cmp[i]].push_back(i);
    // weight.resize(k);
    return K=k;
  }
  // O(ElogE)
  vector<vector<int>> getDAG() {
    assert(K>=0);
    vector<vector<int>> res(K);
    for(int from=0;from<V;from++) {
      for(int to:G[from]) if(cmp[from]!=cmp[to]) res[cmp[from]].push_back(cmp[to]);
    }
    for(int i=0;i<K;i++){
      sort(res[i].begin(),res[i].end());
      res[i].erase(unique(res[i].begin(),res[i].end()),res[i].end());
    }
    return res;
  }
};