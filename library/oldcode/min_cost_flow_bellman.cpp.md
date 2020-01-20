---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: oldcode/min_cost_flow_bellman.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#bf50ccff88ac9b2562bee63cf804278c">oldcode</a>
* <a href="{{ site.github.repository_url }}/blob/master/oldcode/min_cost_flow_bellman.cpp">View this file on GitHub</a>
    - Last commit date: 2019-10-03 22:20:29+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "oldcode/min_cost_flow_bellman.cpp"
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
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

