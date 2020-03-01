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


# :heavy_check_mark: graph/dinic_with_cost_scalling.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/dinic_with_cost_scalling.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-17 16:02:55+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/GRL6A_2.test.cpp.html">test/GRL6A_2.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class T>
class dinicWithCostScalling {
    struct edge{
        int to;
        T cap;
        int rev;
        bool isrev;
    };

    vector<vector<edge>> G;
    vector<int> level, iter;

    void bfs(int s, const T base) {
        level.assign(G.size(), -1);
        queue<int> que;
        level[s] = 0;
        que.push(s);
        while(que.size()) {
            int v = que.front(); que.pop();
            for(auto i: G[v]) {
                if(i.cap >= base && level[i.to] < 0) {
                    level[i.to] = level[v] + 1;
                    que.push(i.to);
                }
            }
        }
    }
    T dfs(int v, const int t, T f, const T base) {
        if(v == t) return f;
        for(int &i = iter[v]; i<(ll)G[v].size(); ++i) {
            edge &e = G[v][i];
            if(e.cap >= base && level[v] < level[e.to]) {
                T d = dfs(e.to, t, min(f, e.cap), base);
                if(d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

public:
    dinicWithCostScalling() {}
    dinicWithCostScalling(int n) : G(n), level(n), iter(n) {}

    void add_edge(int from, int to, T cap) {
        G[from].push_back({to, cap, (int)G[to].size(), false});
        G[to].push_back({from, 0, (int)G[from].size()-1, true});
    }

    // max_capは辺の最大容量
    T maxflow(int s, int t, T max_cap = 1LL<<30) {
        T flow = 0;
        const int tmp = __builtin_ctzll(max_cap);
        for(T base = 1LL<<tmp; base >= 1;) {
            bfs(s, base);
            if(level[t] < 0) {
                base >>= 1;
                continue;
            }
            iter.assign(G.size(), 0);
            flow += dfs(s, t, 1LL<<60, base);
        }
        return flow;
    }

    friend ostream &operator <<(ostream& out, const dinicWithCostScalling& a){
        out << endl;
        for(int i = 0; i < (int)a.G.size(); i++) {
            for(auto &e : a.G[i]) {
                if(e.isrev) continue;
                auto &rev_e = a.G[e.to][e.rev];
                out << i << "->" << e.to << " (flow: " << rev_e.cap << "/" << e.cap + rev_e.cap << ")" << endl;
            }
        }
        return out;
    }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/dinic_with_cost_scalling.cpp"
template<class T>
class dinicWithCostScalling {
    struct edge{
        int to;
        T cap;
        int rev;
        bool isrev;
    };

    vector<vector<edge>> G;
    vector<int> level, iter;

    void bfs(int s, const T base) {
        level.assign(G.size(), -1);
        queue<int> que;
        level[s] = 0;
        que.push(s);
        while(que.size()) {
            int v = que.front(); que.pop();
            for(auto i: G[v]) {
                if(i.cap >= base && level[i.to] < 0) {
                    level[i.to] = level[v] + 1;
                    que.push(i.to);
                }
            }
        }
    }
    T dfs(int v, const int t, T f, const T base) {
        if(v == t) return f;
        for(int &i = iter[v]; i<(ll)G[v].size(); ++i) {
            edge &e = G[v][i];
            if(e.cap >= base && level[v] < level[e.to]) {
                T d = dfs(e.to, t, min(f, e.cap), base);
                if(d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

public:
    dinicWithCostScalling() {}
    dinicWithCostScalling(int n) : G(n), level(n), iter(n) {}

    void add_edge(int from, int to, T cap) {
        G[from].push_back({to, cap, (int)G[to].size(), false});
        G[to].push_back({from, 0, (int)G[from].size()-1, true});
    }

    // max_capは辺の最大容量
    T maxflow(int s, int t, T max_cap = 1LL<<30) {
        T flow = 0;
        const int tmp = __builtin_ctzll(max_cap);
        for(T base = 1LL<<tmp; base >= 1;) {
            bfs(s, base);
            if(level[t] < 0) {
                base >>= 1;
                continue;
            }
            iter.assign(G.size(), 0);
            flow += dfs(s, t, 1LL<<60, base);
        }
        return flow;
    }

    friend ostream &operator <<(ostream& out, const dinicWithCostScalling& a){
        out << endl;
        for(int i = 0; i < (int)a.G.size(); i++) {
            for(auto &e : a.G[i]) {
                if(e.isrev) continue;
                auto &rev_e = a.G[e.to][e.rev];
                out << i << "->" << e.to << " (flow: " << rev_e.cap << "/" << e.cap + rev_e.cap << ")" << endl;
            }
        }
        return out;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

