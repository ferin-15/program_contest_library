// BEGIN CUT
#define MAX_V 10000
struct edge { int to, cap, cost, rev; };

int V;
vector<edge> G[MAX_V];
int dist[MAX_V], prevv[MAX_V], preve[MAX_V];

void add_edge(int from, int to, int cap, int cost) {
  G[from].PB({to, cap, cost, (int)G[to].size()});
  G[to].PB({from, 0, -cost, (int)G[from].size()-1});
}

int min_cost_flow(int s, int t, int f) {
  int res = 0;
  while(f > 0) {
    fill(dist, dist+V, INF);
    dist[s] = 0;
    bool update = true;
    while(update) {
      update = false;
      REP(v, V) {
        if(dist[v] == INF) continue;
        REP(i, G[v].size()) {
          edge &e = G[v][i];
          if(e.cap > 0 && dist[e.to] > dist[v] + e.cost) {
            dist[e.to] = dist[v] + e.cost;
            prevv[e.to] = v;
            preve[e.to] = i;
            update = true;
          }
        }
      }
    }
    if(dist[t] == INF) return -1;

    int d = f;
    for(int v = t; v != s; v = prevv[v]) {
      chmin(d, G[prevv[v]][preve[v]].cap);
    }
    f -= d;
    res += d * dist[t];
    for(int v = t; v != s; v = prevv[v]) {
      edge &e = G[prevv[v]][preve[v]];
      e.cap -= d;
      G[v][e.rev].cap += d;
    }
  }
  return res;
}
// END CUT