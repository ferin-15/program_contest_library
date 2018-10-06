struct edge{int to, cost;};

int n, d[100010];
vector<edge> g[100010];

void dijkstra(int s) {
  priority_queue<PII, vector<PII>, greater<PII>> que;
  fill(d, d+n, INF);
  d[s] = 0;
  que.push(PII{0, s});

  while(que.size()) {
    PII p = que.top(); que.pop();
    int v = p.second;
    if(d[v] < p.first) continue;
    for(edge e: g[v]) {
      if(d[e.to] > d[v] + e.cost) {
        d[e.to] = d[v] + e.cost;
        que.push(PII{d[e.to], e.to});
      }
    }
  }
}
