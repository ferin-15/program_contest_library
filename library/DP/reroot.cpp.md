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


# :warning: DP/reroot.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e2fca8135c2fadca093abd79a6b1c0d2">DP</a>
* <a href="{{ site.github.repository_url }}/blob/master/DP/reroot.cpp">View this file on GitHub</a>
    - Last commit date: 2019-09-13 21:29:38+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template< typename Data, typename T >
class ReRooting {
private:
    struct edge {
        int to, rev;
        Data data;
    };

    using F1 = function<T(T,T)>;
    using F2 = function<T(T,Data)>;

    vector<vector<edge>> g;
    vector<vector<T>> ldp, rdp;
    vector<int> lptr, rptr;
    const F1 f1;
    const F2 f2;
    const T ident;

    T dfs(int idx, int par) {
        while(lptr[idx] != par && lptr[idx] < (ll)g[idx].size()) {
            auto &e = g[idx][lptr[idx]];
            ldp[idx][lptr[idx]+1] = f1(ldp[idx][lptr[idx]], f2(dfs(e.to, e.rev), e.data));
            ++lptr[idx];
        }
        while(rptr[idx] != par && rptr[idx] >= 0) {
            auto &e = g[idx][rptr[idx]];
            rdp[idx][rptr[idx]] = f1(rdp[idx][rptr[idx]+1], f2(dfs(e.to, e.rev), e.data));
            --rptr[idx];
        }
        if(par < 0) return rdp[idx][0];
        return f1(ldp[idx][par], rdp[idx][par + 1]);
    }

public:
    ReRooting(int n, const F1 &f1, const F2 &f2, const T &ident) :
    g(n), ldp(n), rdp(n), lptr(n), rptr(n), f1(f1), f2(f2), ident(ident) {}

    void add_edge(int u, int v, const Data &d) {
        g[u].emplace_back((edge){v, (int)g[v].size(), d});
        g[v].emplace_back((edge){u, (int)g[u].size()-1, d});
    }
    void add_edge_bi(int u, int v, const Data &d, const Data &e) {
        g[u].emplace_back((edge){v, (int)g[v].size(), d});
        g[v].emplace_back((edge){u, (int)g[u].size()-1, e});
    }

    vector<T> solve() {
        REP(i, g.size()) {
            ldp[i].assign(g[i].size()+1, ident);
            rdp[i].assign(g[i].size()+1, ident);
            lptr[i] = 0;
            rptr[i] = (int)g[i].size()-1;
        }
        vector<T> ret(g.size());
        REP(i, g.size()) ret[i] = dfs(i, -1);
        return ret;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "DP/reroot.cpp"
template< typename Data, typename T >
class ReRooting {
private:
    struct edge {
        int to, rev;
        Data data;
    };

    using F1 = function<T(T,T)>;
    using F2 = function<T(T,Data)>;

    vector<vector<edge>> g;
    vector<vector<T>> ldp, rdp;
    vector<int> lptr, rptr;
    const F1 f1;
    const F2 f2;
    const T ident;

    T dfs(int idx, int par) {
        while(lptr[idx] != par && lptr[idx] < (ll)g[idx].size()) {
            auto &e = g[idx][lptr[idx]];
            ldp[idx][lptr[idx]+1] = f1(ldp[idx][lptr[idx]], f2(dfs(e.to, e.rev), e.data));
            ++lptr[idx];
        }
        while(rptr[idx] != par && rptr[idx] >= 0) {
            auto &e = g[idx][rptr[idx]];
            rdp[idx][rptr[idx]] = f1(rdp[idx][rptr[idx]+1], f2(dfs(e.to, e.rev), e.data));
            --rptr[idx];
        }
        if(par < 0) return rdp[idx][0];
        return f1(ldp[idx][par], rdp[idx][par + 1]);
    }

public:
    ReRooting(int n, const F1 &f1, const F2 &f2, const T &ident) :
    g(n), ldp(n), rdp(n), lptr(n), rptr(n), f1(f1), f2(f2), ident(ident) {}

    void add_edge(int u, int v, const Data &d) {
        g[u].emplace_back((edge){v, (int)g[v].size(), d});
        g[v].emplace_back((edge){u, (int)g[u].size()-1, d});
    }
    void add_edge_bi(int u, int v, const Data &d, const Data &e) {
        g[u].emplace_back((edge){v, (int)g[v].size(), d});
        g[v].emplace_back((edge){u, (int)g[u].size()-1, e});
    }

    vector<T> solve() {
        REP(i, g.size()) {
            ldp[i].assign(g[i].size()+1, ident);
            rdp[i].assign(g[i].size()+1, ident);
            lptr[i] = 0;
            rptr[i] = (int)g[i].size()-1;
        }
        vector<T> ret(g.size());
        REP(i, g.size()) ret[i] = dfs(i, -1);
        return ret;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

