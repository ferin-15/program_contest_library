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


# :heavy_check_mark: graph/ford_fulkerson.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/ford_fulkerson.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 04:35:05+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/GRL6A_1.test.cpp.html">test/GRL6A_1.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct FordFulkerson {
    struct edge {
        int to;
        ll cap;
        int rev;
        bool isrev;
    };

    vector<vector<edge>> g;
    vector<int> used;
    int timestamp;

    ll dfs(int idx, const int t, ll flow) {
        if(idx == t) return flow;
        used[idx] = timestamp;
        for(auto &e : g[idx]) {
            if(e.cap > 0 && used[e.to] != timestamp) {
                ll d = dfs(e.to, t, min(flow, e.cap));
                if(d > 0) {
                    e.cap -= d;
                    g[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    FordFulkerson() {}
    FordFulkerson(int n) : timestamp(0), g(n), used(n, -1) {}

    void add_edge(int from, int to, ll cap) {
        g[from].emplace_back((edge){to, cap, (int)g[to].size(), false});
        g[to].emplace_back((edge){from, 0, (int)g[from].size()-1, true});
    }

    ll max_flow(int s, int t) {
        ll flow = 0;
        ++timestamp;
        for(ll f; (f = dfs(s, t, INF)) > 0; timestamp++) {
            flow += f;
        }
        return flow;
    }

    friend ostream &operator <<(ostream& out, const FordFulkerson& a){
        out << "-----" << endl;
        for(int i = 0; i < (int)a.g.size(); i++) {
            for(auto &e : a.g[i]) {
                if(e.isrev) continue;
                auto &rev_e = a.g[e.to][e.rev];
                out << i << "->" << e.to << " (flow: " << rev_e.cap << "/" << e.cap + rev_e.cap << ")" << endl;
            }
        }
        out << "-----" << endl;
        return out;
    }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/ford_fulkerson.cpp"
struct FordFulkerson {
    struct edge {
        int to;
        ll cap;
        int rev;
        bool isrev;
    };

    vector<vector<edge>> g;
    vector<int> used;
    int timestamp;

    ll dfs(int idx, const int t, ll flow) {
        if(idx == t) return flow;
        used[idx] = timestamp;
        for(auto &e : g[idx]) {
            if(e.cap > 0 && used[e.to] != timestamp) {
                ll d = dfs(e.to, t, min(flow, e.cap));
                if(d > 0) {
                    e.cap -= d;
                    g[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    FordFulkerson() {}
    FordFulkerson(int n) : timestamp(0), g(n), used(n, -1) {}

    void add_edge(int from, int to, ll cap) {
        g[from].emplace_back((edge){to, cap, (int)g[to].size(), false});
        g[to].emplace_back((edge){from, 0, (int)g[from].size()-1, true});
    }

    ll max_flow(int s, int t) {
        ll flow = 0;
        ++timestamp;
        for(ll f; (f = dfs(s, t, INF)) > 0; timestamp++) {
            flow += f;
        }
        return flow;
    }

    friend ostream &operator <<(ostream& out, const FordFulkerson& a){
        out << "-----" << endl;
        for(int i = 0; i < (int)a.g.size(); i++) {
            for(auto &e : a.g[i]) {
                if(e.isrev) continue;
                auto &rev_e = a.g[e.to][e.rev];
                out << i << "->" << e.to << " (flow: " << rev_e.cap << "/" << e.cap + rev_e.cap << ")" << endl;
            }
        }
        out << "-----" << endl;
        return out;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

