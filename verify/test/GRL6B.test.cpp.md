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


# :heavy_check_mark: test/GRL6B.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/GRL6B.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_B">https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_B</a>


## Depends on

* :heavy_check_mark: <a href="../../library/graph/min_cost_flow_dijkstra.cpp.html">graph/min_cost_flow_dijkstra.cpp</a>
* :heavy_check_mark: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_B"
#include "../memo/macro.hpp"
#include "../graph/min_cost_flow_dijkstra.cpp"

signed main(void) {
    ll n, m, f;
    cin >> n >> m >> f;
    min_cost_max_flow mcf(n);
    REP(i, m) {
        ll u, v, c, d;
        cin >> u >> v >> c >> d;
        mcf.add_edge(u, v, c, d);
    }
    cout << mcf.flow(0, n-1, f) << endl;

    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/GRL6B.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_B"
#line 1 "memo/macro.hpp"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PII = pair<ll, ll>;
#define FOR(i, a, n) for (ll i = (ll)a; i < (ll)n; ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(x) x.begin(), x.end()
template<typename T> void chmin(T &a, const T &b) { a = min(a, b); }
template<typename T> void chmax(T &a, const T &b) { a = max(a, b); }
struct FastIO {FastIO() { cin.tie(0); ios::sync_with_stdio(0); }}fastiofastio;
const ll INF = 1LL<<60;
#line 1 "graph/min_cost_flow_dijkstra.cpp"
// BEGIN CUT
struct min_cost_max_flow {
    struct edge {
        int to;
        ll cap, cost;
        int rev;
        bool isrev;
    };

    int n, s, t;
    ll neg;
    vector<vector<edge>> g;
    vector<ll> d, h, dist, prevv, preve;

    ll flow(vector<ll> d0) {
        ll res = 0;
        priority_queue<PII, vector<PII>, greater<PII>> que;
        h.assign(n, 0);
        preve.assign(n, -1);
        prevv.assign(n, -1);
        ll f = 0;
        REP(i, d.size()) {
            if(i < (ll)d0.size()) d[i] += d0[i];
            if(d[i] > 0) add_edge(s, i, d[i], 0), f += d[i];
            else if(d[i] < 0) add_edge(i, t, -d[i], 0);
        }
        while(f > 0) {
            dist.assign(n, INF);
            dist[s] = 0;
            que.push({0, s});
            while(que.size()) {
                PII p = que.top(); que.pop();
                int v = p.second;
                if(dist[v] < p.first) continue;
                REP(i, g[v].size()) {
                    edge &e = g[v][i];
                    if(e.cap>0 && dist[e.to]>dist[v]+e.cost+h[v]-h[e.to]) {
                        dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        que.push({dist[e.to], e.to});
                    }
                }
            }
            if(dist[t] == INF) return -1;
            REP(v, n) h[v] += dist[v];
            ll d = f;
            for(int v = t; v != s; v = prevv[v]) {
                chmin(d, g[prevv[v]][preve[v]].cap);
            }
            f -= d; res += d * h[t];
            for(int v = t; v != s; v = prevv[v]) {
                edge &e = g[prevv[v]][preve[v]];
                e.cap -= d;
                g[v][e.rev].cap += d;
            }
        }
        return neg + res;
    }

    min_cost_max_flow(int n0) : n(n0+2), s(n0), t(n0+1), neg(0), g(n0+2), d(n0+2) {}

    void add_edge(int from, int to, ll cap, ll cost) {
        if(cost >= 0) {
            g[from].push_back({to, cap, cost, (int)g[to].size(), false});
            g[to].push_back({from, 0, -cost, (int)g[from].size()-1, true});
        } else {
            d[from] -= cap;
            d[to] += cap;
            neg += cap * cost;
            add_edge(to, from, cap, -cost);
        }
    }
    // SからTに流量fを流す 流せないなら-1
    // F'を負辺の容量の和とすると O((f+F')ElogV) 
    ll flow(int S, int T, ll f) {
        vector<ll> d0(n);
        d0[S] = f, d0[T] = -f;
        return flow(d0);
    }

    friend ostream &operator <<(ostream& out, const min_cost_max_flow& a){
        out << endl;
        for(int i = 0; i < (int)a.g.size(); i++) {
            for(auto &e : a.g[i]) {
                if(e.isrev) continue;
                auto &rev_e = a.g[e.to][e.rev];
                out << i << "->" << e.to << " (flow: " << rev_e.cap << "/" << e.cap + rev_e.cap << ") cost:" << e.cost << endl;
            }
        }
        return out;
    }
};
// END CUT
#line 4 "test/GRL6B.test.cpp"

signed main(void) {
    ll n, m, f;
    cin >> n >> m >> f;
    min_cost_max_flow mcf(n);
    REP(i, m) {
        ll u, v, c, d;
        cin >> u >> v >> c >> d;
        mcf.add_edge(u, v, c, d);
    }
    cout << mcf.flow(0, n-1, f) << endl;

    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

