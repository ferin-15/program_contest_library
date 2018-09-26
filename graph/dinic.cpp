// BEGIN CUT
#define MAX_N 10000
struct edge{ int to, cap, rev; };

vector<edge> G[MAX_N];
int level[MAX_N]; // sからの距離
int iter[MAX_N];  // どこまで調べ終わったか

void add_edge(int from, int to, int cap) {
  G[from].PB({to, cap, (int)G[to].size()});
  G[to].PB({from, 0, (int)G[from].size()-1});
}

void bfs(int s) {
  memset(level, -1, sizeof(level));
  queue<int> que;
  level[s] = 0;
  que.push(s);
  while(que.size()) {
    int v = que.front(); que.pop();
    for(auto i: G[v]) {
      if(i.cap > 0 && level[i.to] < 0) {
        level[i.to] = level[v] + 1;
        que.push(i.to);
      }
    }
  }
}

int dfs(int v, int t, int f) {
  if(v == t) return f;
  for(int &i = iter[v]; i<(int)G[v].size(); ++i) {
    edge &e = G[v][i];
    if(e.cap > 0 && level[v] < level[e.to]) {
      int d = dfs(e.to, t, min(f, e.cap));
      if(d > 0) {
        e.cap -= d;
        G[e.to][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

int max_flow(int s, int t) {
  int flow = 0;
  while(1) {
    bfs(s);
    if(level[t] < 0) return flow;
    memset(iter, 0, sizeof(iter));
    int f;
    while((f = dfs(s, t, INF)) > 0) flow += f;
  }
}
// END CUT