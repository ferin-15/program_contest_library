// BEGIN CUT
#define MAX_V 10000
struct edge { int to, cap, cost, rev; };

int V;  // 頂点数
vector<edge> G[MAX_V];
int h[MAX_V];
int dist[MAX_V];
int prevv[MAX_V], preve[MAX_V];

void add_edge(int from, int to, int cap, int cost) {
  G[from].PB({to, cap, cost, (int)G[to].size()});
  G[to].PB({from, 0, -cost, (int)G[from].size()-1});
}

// sからtへの流量fの最小費用流
int min_cost_flow(int s, int t, int f) {
  int res = 0;
  fill(h, h+V, 0);
  while(f > 0) {
    priority_queue<PII, vector<PII>, greater<PII>> que;
    fill(dist, dist+V, INF);
    dist[s] = 0;
    que.push({0, s});
    while(que.size()) {
      PII p = que.top(); que.pop();
      int v = p.second;
      if(dist[v] < p.first) continue;
      for(int i=0; i<(int)G[v].size(); ++i) {
        edge &e = G[v][i];
        if(e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
          dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
          prevv[e.to] = v;
          preve[e.to] = i;
          que.push({dist[e.to], e.to});
        }
      }
    }
    // これ以上流せない
    if(dist[t] == INF) return -1;
    REP(v, V) h[v] += dist[v];

    int d = f;
    for(int v = t; v != s; v = prevv[v]) {
      d = min(d, G[prevv[v]][preve[v]].cap);
    }
    f -= d;
    res += d * h[t];
    for(int v = t; v != s; v = prevv[v]) {
      edge &e = G[prevv[v]][preve[v]];
      e.cap -= d;
      G[v][e.rev].cap += d;
    }
  }
  return res;
}
// END CUT