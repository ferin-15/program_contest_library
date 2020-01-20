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


# :warning: graph/max_independent_set.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/max_independent_set.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 04:35:05+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// O(n*1.466^n) n<=40で16ms
struct maxIndependentSet {
    ll n;
    vector<vector<ll>> g;

    ll dfs(ll v, vector<ll>& used) {
        if(v == n) return 0;
        ll ret = 0;
        if(!used[v]) {
            vector<ll> nv(1, v);
            for(ll i: g[v]) if(!used[i]) nv.push_back(i);
            for(ll i: nv) used[i] = 1;
            chmax(ret, dfs(v+1, used) + 1);
            for(ll i: nv) used[i] = 0;
        }
        ll d = 0;
        for(ll i: g[v]) if(!used[i]) d++;
        if(d > 1 || used[v]) {
            if(!used[v]) {
                used[v] = 1;
                chmax(ret, dfs(v+1, used));
                used[v] = 0;
            } else {
                chmax(ret, dfs(v+1, used));
            }
        }
        return ret;
    }

    maxIndependentSet() {}
    maxIndependentSet(ll n) : n(n), g(n) {}

    void add_edge(ll a, ll b) {
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int get() {
        vector<ll> used(n);
        return dfs(0, used);
    }
};

namespace thanks2017G {
    void solve() {
        ll n, m;
        cin >> n >> m;
        maxIndependentSet graph(n);
        REP(i, m) {
            int a, b;
            cin >> a >> b;
            graph.add_edge(a-1, b-1);
        }
        cout << graph.get() << endl;
    }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/max_independent_set.cpp"
// O(n*1.466^n) n<=40で16ms
struct maxIndependentSet {
    ll n;
    vector<vector<ll>> g;

    ll dfs(ll v, vector<ll>& used) {
        if(v == n) return 0;
        ll ret = 0;
        if(!used[v]) {
            vector<ll> nv(1, v);
            for(ll i: g[v]) if(!used[i]) nv.push_back(i);
            for(ll i: nv) used[i] = 1;
            chmax(ret, dfs(v+1, used) + 1);
            for(ll i: nv) used[i] = 0;
        }
        ll d = 0;
        for(ll i: g[v]) if(!used[i]) d++;
        if(d > 1 || used[v]) {
            if(!used[v]) {
                used[v] = 1;
                chmax(ret, dfs(v+1, used));
                used[v] = 0;
            } else {
                chmax(ret, dfs(v+1, used));
            }
        }
        return ret;
    }

    maxIndependentSet() {}
    maxIndependentSet(ll n) : n(n), g(n) {}

    void add_edge(ll a, ll b) {
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int get() {
        vector<ll> used(n);
        return dfs(0, used);
    }
};

namespace thanks2017G {
    void solve() {
        ll n, m;
        cin >> n >> m;
        maxIndependentSet graph(n);
        REP(i, m) {
            int a, b;
            cin >> a >> b;
            graph.add_edge(a-1, b-1);
        }
        cout << graph.get() << endl;
    }
}
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

