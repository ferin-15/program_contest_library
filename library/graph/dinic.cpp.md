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


# :heavy_check_mark: graph/dinic.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/dinic.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 04:35:05+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/GRL6A_0.test.cpp.html">test/GRL6A_0.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class T>
struct dinic {
    struct edge{
        int to;
        T cap;
        int rev;
        bool isrev;
    };

    vector<vector<edge>> G;
    vector<int> level, iter;

    void bfs(int s) {
        level.assign(G.size(), -1);
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

    T dfs(int v, const int t, T f) {
        if(v == t) return f;
        for(int &i = iter[v]; i<(ll)G[v].size(); ++i) {
            edge &e = G[v][i];
            if(e.cap > 0 && level[v] < level[e.to]) {
                T d = dfs(e.to, t, min(f, e.cap));
                if(d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    dinic() {}
    dinic(int n) : G(n), level(n), iter(n) {}

    void add_edge(int from, int to, T cap) {
        G[from].push_back({to, cap, (int)G[to].size(), false});
        G[to].push_back({from, 0, (int)G[from].size()-1, true});
    }

    // sからtへ流量fを流す
    T maxflow(int s, int t, T f = 1LL<<30) {
        T flow = 0;
        while(1) {
            bfs(s);
            if(level[t] < 0) return flow;
            iter.assign(G.size(), 0);
            T tmp;
            while((tmp = dfs(s, t, f)) > 0) flow += tmp;
        }
    }

    // sからtへ1流す
    T flow(int s, int t) {
        bfs(s);
        if(level[t] < 0) return 0;
        iter.assign(G.size(), 0);
        return dfs(s, t, 1);
    }
    // 始点，終点tのフローで辺e=(from,to)の容量を1増やしたときの最大流の変化
    // 並列辺はたぶんバグる
    T add(int from, int to, int s, int t) {
        for(auto &e: G[from]) {
            if(e.to == to && !e.isrev) {
                e.cap++;
                break;
            }
        }
        return flow(s, t);
    }
    // 始点s，終点tのフローで辺e=(from,to)の容量を1減らしたときの最大流の変化
    // 並列辺はたぶんバグる
    T sub(int from, int to, int s, int t) {
        for(auto &e: G[from]) {
            if(e.to == to && !e.isrev) {
                T diff = 0;
                // 辺(from,to)で容量いっぱいに流れている
                if(e.cap == 0) {
                    // 残余グラフでfrom→toのパスがない
                    if(flow(from, to) == 0) {
                        flow(t, to);
                        flow(from, s);
                        diff = -1;
                    }
                    G[e.to][e.rev].cap--;
                } else {
                    e.cap--;
                }
                return diff;
            }
        }
        assert(false); // 存在しない辺を減らそうとした
    }

    friend ostream &operator <<(ostream& out, const dinic& a){
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

template<class F>
struct dinic_with_lowerlimit {
    int S, T;
    F sum_lb;
    dinic<F> flow;

    dinic_with_lowerlimit() {}
    dinic_with_lowerlimit(int n) : S(n), T(n+1), sum_lb(0), flow(n+2) {}

    void add_edge(int from, int to, F ub) {
        flow.add_edge(from, to, ub);
    }
    void add_edge(int from, int to, F lb, F ub) {
        flow.add_edge(from, to, ub-lb);
        flow.add_edge(S, to, lb);
        flow.add_edge(from, T, lb);
        sum_lb += lb;
    }

    // sからtへ最小流量を満たすフローが存在しなければ-1
    F maxflow(int s, int t) {
        F a = flow.maxflow(S, T);
        F b = flow.maxflow(s, T);
        F c = flow.maxflow(S, t);
        F d = flow.maxflow(s, t);
        return (a+b==sum_lb && a+c==sum_lb) ? b+d : -1;
    }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/dinic.cpp"
template<class T>
struct dinic {
    struct edge{
        int to;
        T cap;
        int rev;
        bool isrev;
    };

    vector<vector<edge>> G;
    vector<int> level, iter;

    void bfs(int s) {
        level.assign(G.size(), -1);
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

    T dfs(int v, const int t, T f) {
        if(v == t) return f;
        for(int &i = iter[v]; i<(ll)G[v].size(); ++i) {
            edge &e = G[v][i];
            if(e.cap > 0 && level[v] < level[e.to]) {
                T d = dfs(e.to, t, min(f, e.cap));
                if(d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    dinic() {}
    dinic(int n) : G(n), level(n), iter(n) {}

    void add_edge(int from, int to, T cap) {
        G[from].push_back({to, cap, (int)G[to].size(), false});
        G[to].push_back({from, 0, (int)G[from].size()-1, true});
    }

    // sからtへ流量fを流す
    T maxflow(int s, int t, T f = 1LL<<30) {
        T flow = 0;
        while(1) {
            bfs(s);
            if(level[t] < 0) return flow;
            iter.assign(G.size(), 0);
            T tmp;
            while((tmp = dfs(s, t, f)) > 0) flow += tmp;
        }
    }

    // sからtへ1流す
    T flow(int s, int t) {
        bfs(s);
        if(level[t] < 0) return 0;
        iter.assign(G.size(), 0);
        return dfs(s, t, 1);
    }
    // 始点，終点tのフローで辺e=(from,to)の容量を1増やしたときの最大流の変化
    // 並列辺はたぶんバグる
    T add(int from, int to, int s, int t) {
        for(auto &e: G[from]) {
            if(e.to == to && !e.isrev) {
                e.cap++;
                break;
            }
        }
        return flow(s, t);
    }
    // 始点s，終点tのフローで辺e=(from,to)の容量を1減らしたときの最大流の変化
    // 並列辺はたぶんバグる
    T sub(int from, int to, int s, int t) {
        for(auto &e: G[from]) {
            if(e.to == to && !e.isrev) {
                T diff = 0;
                // 辺(from,to)で容量いっぱいに流れている
                if(e.cap == 0) {
                    // 残余グラフでfrom→toのパスがない
                    if(flow(from, to) == 0) {
                        flow(t, to);
                        flow(from, s);
                        diff = -1;
                    }
                    G[e.to][e.rev].cap--;
                } else {
                    e.cap--;
                }
                return diff;
            }
        }
        assert(false); // 存在しない辺を減らそうとした
    }

    friend ostream &operator <<(ostream& out, const dinic& a){
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

template<class F>
struct dinic_with_lowerlimit {
    int S, T;
    F sum_lb;
    dinic<F> flow;

    dinic_with_lowerlimit() {}
    dinic_with_lowerlimit(int n) : S(n), T(n+1), sum_lb(0), flow(n+2) {}

    void add_edge(int from, int to, F ub) {
        flow.add_edge(from, to, ub);
    }
    void add_edge(int from, int to, F lb, F ub) {
        flow.add_edge(from, to, ub-lb);
        flow.add_edge(S, to, lb);
        flow.add_edge(from, T, lb);
        sum_lb += lb;
    }

    // sからtへ最小流量を満たすフローが存在しなければ-1
    F maxflow(int s, int t) {
        F a = flow.maxflow(S, T);
        F b = flow.maxflow(s, T);
        F c = flow.maxflow(S, t);
        F d = flow.maxflow(s, t);
        return (a+b==sum_lb && a+c==sum_lb) ? b+d : -1;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

