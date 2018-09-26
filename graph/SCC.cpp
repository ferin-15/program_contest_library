// BEGIN CUT
class SCC {
public:
  int V,K;    // 頂点数, scc後の頂点数
  VVI G;      // グラフの隣接リストの表現
  VVI rG;     // 辺の向きを逆にしたグラフ
  VVI DAG;    // scc後のグラフの隣接リストの表現
  VVI rDAG;   // scc後の辺の向きを逆にしたグラフ
  VI vs;      // 帰りがけ順の並び
  VI used;    // すでに調べたか
  VI cmp;     // 属する強連結成分のトポロジカル順
  VVI member; // scc後の同一ノードの集合
  // vector<double> weight;  // i番目の連結成分が持つ情報
  // 初期化
  SCC() { V=K=-1; }
  SCC(int V_): V(V_) {
    G.assign(V_, VI());
    rG.assign(V_, VI());
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
  VVI getDAG() {
    assert(K>=0);
    VVI res(K);
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
// END CUT