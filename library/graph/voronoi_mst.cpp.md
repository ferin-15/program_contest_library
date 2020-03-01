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


# :warning: graph/voronoi_mst.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/voronoi_mst.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
// http://tokoharuland.hateblo.jp/entry/2018/04/01/155743
// 距離行列を仮想頂点とか使ってグラフで表してこれに渡すと最小全域木になる
// initで渡すのは元のグラフの頂点集合
template<bool istree = true>
ll voronoiMst(vector<vector<PII>> g, vector<ll> init) {
    const ll n = g.size();
    ll ret = 0;
    vector<pair<ll,PII>> edges;
    vector<ll> dist(n, LLINF), col(n, -1);
    struct node {
        ll dist, vertex, col;
        node() {}
        node(ll a, ll b, ll c) : dist(a), vertex(b), col(c) {}
        bool operator<(node nd) const { return dist > nd.dist; }
    };
    priority_queue<node> que;
    for(auto i: init) que.push(node(0, i, i));
    while(que.size()) {
        node p = que.top(); que.pop();
        if(dist[p.vertex] == LLINF) {
            dist[p.vertex] = p.dist;
            col[p.vertex] = p.col;
            for(auto to: g[p.vertex]) {
                que.push(node(p.dist+to.second, to.first, p.col));
            }
        } else {
            if(p.col != col[p.vertex]) {
                if(istree) ret += dist[p.vertex] + p.dist;
                else edges.push_back({dist[p.vertex]+p.dist, {col[p.vertex], p.col}});
            }
        }
    }
    if(istree) return ret/2;
    sort(ALL(edges));
    UnionFind uf(2*n);
    REP(i, edges.size()) {
        if(uf.same(edges[i].second.first, edges[i].second.second)) continue;
        uf.unite(edges[i].second.first, edges[i].second.second);
        ret += edges[i].first;
    }
    return ret;
}
// END CUT

// https://codeforces.com/problemset/problem/1095/F
namespace cf529div3F {
    void solve() {
        ll n, m;
        cin >> n >> m;
        vector<vector<PII>> g(n+1);
        REP(i, n) {
            ll a;
            cin >> a;
            g[n].push_back({i, a});
            g[i].push_back({n, a});
        }
        REP(i, m) {
            ll u, v, w;
            cin >> u >> v >> w;
            u--, v--;
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }

        vector<ll> init(n);
        iota(ALL(init), 0);
        cout << voronoiMst<false>(g, init) << endl;
    }
}

// https://atcoder.jp/contests/cf17-final/tasks/cf17_final_j
namespace codefestival2017finalJ {
    void solve() {
        ll n;
        cin >> n;
        vector<vector<PII>> g(2*n);
        REP(i, n) {
          ll x;
          cin >> x;
          g[i].push_back({i+n, x});
          g[i+n].push_back({i, x});
        }
        REP(i, n-1) {
          ll a, b, c;
          cin >> a >> b >> c;
          a--, b--;
          g[a+n].push_back({b+n, c});
          g[b+n].push_back({a+n, c});
        }

        vector<ll> init(n);
        iota(ALL(init), 0);
        cout << voronoiMst<false>(g, init) << endl;
    }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/voronoi_mst.cpp"
// BEGIN CUT
// http://tokoharuland.hateblo.jp/entry/2018/04/01/155743
// 距離行列を仮想頂点とか使ってグラフで表してこれに渡すと最小全域木になる
// initで渡すのは元のグラフの頂点集合
template<bool istree = true>
ll voronoiMst(vector<vector<PII>> g, vector<ll> init) {
    const ll n = g.size();
    ll ret = 0;
    vector<pair<ll,PII>> edges;
    vector<ll> dist(n, LLINF), col(n, -1);
    struct node {
        ll dist, vertex, col;
        node() {}
        node(ll a, ll b, ll c) : dist(a), vertex(b), col(c) {}
        bool operator<(node nd) const { return dist > nd.dist; }
    };
    priority_queue<node> que;
    for(auto i: init) que.push(node(0, i, i));
    while(que.size()) {
        node p = que.top(); que.pop();
        if(dist[p.vertex] == LLINF) {
            dist[p.vertex] = p.dist;
            col[p.vertex] = p.col;
            for(auto to: g[p.vertex]) {
                que.push(node(p.dist+to.second, to.first, p.col));
            }
        } else {
            if(p.col != col[p.vertex]) {
                if(istree) ret += dist[p.vertex] + p.dist;
                else edges.push_back({dist[p.vertex]+p.dist, {col[p.vertex], p.col}});
            }
        }
    }
    if(istree) return ret/2;
    sort(ALL(edges));
    UnionFind uf(2*n);
    REP(i, edges.size()) {
        if(uf.same(edges[i].second.first, edges[i].second.second)) continue;
        uf.unite(edges[i].second.first, edges[i].second.second);
        ret += edges[i].first;
    }
    return ret;
}
// END CUT

// https://codeforces.com/problemset/problem/1095/F
namespace cf529div3F {
    void solve() {
        ll n, m;
        cin >> n >> m;
        vector<vector<PII>> g(n+1);
        REP(i, n) {
            ll a;
            cin >> a;
            g[n].push_back({i, a});
            g[i].push_back({n, a});
        }
        REP(i, m) {
            ll u, v, w;
            cin >> u >> v >> w;
            u--, v--;
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }

        vector<ll> init(n);
        iota(ALL(init), 0);
        cout << voronoiMst<false>(g, init) << endl;
    }
}

// https://atcoder.jp/contests/cf17-final/tasks/cf17_final_j
namespace codefestival2017finalJ {
    void solve() {
        ll n;
        cin >> n;
        vector<vector<PII>> g(2*n);
        REP(i, n) {
          ll x;
          cin >> x;
          g[i].push_back({i+n, x});
          g[i+n].push_back({i, x});
        }
        REP(i, n-1) {
          ll a, b, c;
          cin >> a >> b >> c;
          a--, b--;
          g[a+n].push_back({b+n, c});
          g[b+n].push_back({a+n, c});
        }

        vector<ll> init(n);
        iota(ALL(init), 0);
        cout << voronoiMst<false>(g, init) << endl;
    }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

