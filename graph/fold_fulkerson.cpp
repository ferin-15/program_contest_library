struct foldFulkerson {
  struct edge {int to, cap, rev;};
  int n;
  VV<edge> g;
  V<int> used;

  foldFulkerson(){}
  foldFulkerson(int n_) : n(n_) {
    g.assign(n, V<edge>());
  }

  void add_edge(int from, int to, int cap) {
    g[from].push_back({to, cap, (int)g[to].size()});
    g[to].push_back({from, 0, (int)g[from].size()-1});
  }

  int dfs(int v, int t, int f) {
    if(v == t) return f;
    used[v] = 1;
    for(auto &e: g[v]) {
      if(!used[e.to] && e.cap > 0) {
        int d = dfs(e.to, t, min(f, e.cap));
        if(d > 0) {
          e.cap -= d;
          g[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }

  int max_flow(int s, int t) {
    int flow = 0;
    while(true) {
      used.assign(n, 0);
      int f = dfs(s, t, INF);
      if(f == 0) return flow;
      flow += f;
    }
  }
};