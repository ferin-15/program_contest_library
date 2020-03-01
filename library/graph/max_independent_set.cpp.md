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


# :heavy_check_mark: graph/max_independent_set.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/max_independent_set.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-21 23:36:36+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/yosupo-maximumIndependentSet.test.cpp.html">test/yosupo-maximumIndependentSet.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// O(n*1.466^n) n<=40で16ms
class maxIndependentSet {
public:
    int n;
    vector<int> deg, used, dead, ans;
    vector<vector<int>> g;

private:
    int ret, cnt, alive;
    void dfs() {
        if(cnt+alive <= ret) return;

        int v = -1;
        REP(i, n) if(!used[i] && !dead[i]) {
            if(deg[i] <= 1) { v = i; break; }
            if(v<0 || deg[v]<deg[i]) v=i;
        }
        if(v<0) return;

        if(deg[v] != 1) {
            dead[v] = 1;
            alive--;
            for(auto i: g[v]) deg[i]--;
            dfs();
            dead[v] = 0;
            alive++;
            for(auto i: g[v]) deg[i]++;
        }
        {
            used[v] = 1;
            alive--;
            for(auto i: g[v]) {
                if(dead[i] == 0) alive -= !used[i];
                dead[i]++;
            }
            cnt++;
            if(ret < cnt) ans = used, ret = cnt;
            dfs();
            used[v] = 0;
            alive++;
            for(auto i: g[v]) {
                dead[i]--;
                if(dead[i] == 0) alive += !used[i];
            }
            cnt--;
        }
    }

public:
    maxIndependentSet() {}
    maxIndependentSet(ll n) : n(n), deg(n), used(n), dead(n), ans(n), g(n) {}

    void add_edge(ll a, ll b) {
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<ll> get() {
        REP(i, n) deg[i] = g[i].size();
        ret = cnt = 0, alive = n;
        dfs();
        vector<ll> ans_set;
        REP(i, n) if(ans[i]) ans_set.push_back(i);
        return ans_set;
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
        cout << graph.get().size() << endl;
    }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/max_independent_set.cpp"
// O(n*1.466^n) n<=40で16ms
class maxIndependentSet {
public:
    int n;
    vector<int> deg, used, dead, ans;
    vector<vector<int>> g;

private:
    int ret, cnt, alive;
    void dfs() {
        if(cnt+alive <= ret) return;

        int v = -1;
        REP(i, n) if(!used[i] && !dead[i]) {
            if(deg[i] <= 1) { v = i; break; }
            if(v<0 || deg[v]<deg[i]) v=i;
        }
        if(v<0) return;

        if(deg[v] != 1) {
            dead[v] = 1;
            alive--;
            for(auto i: g[v]) deg[i]--;
            dfs();
            dead[v] = 0;
            alive++;
            for(auto i: g[v]) deg[i]++;
        }
        {
            used[v] = 1;
            alive--;
            for(auto i: g[v]) {
                if(dead[i] == 0) alive -= !used[i];
                dead[i]++;
            }
            cnt++;
            if(ret < cnt) ans = used, ret = cnt;
            dfs();
            used[v] = 0;
            alive++;
            for(auto i: g[v]) {
                dead[i]--;
                if(dead[i] == 0) alive += !used[i];
            }
            cnt--;
        }
    }

public:
    maxIndependentSet() {}
    maxIndependentSet(ll n) : n(n), deg(n), used(n), dead(n), ans(n), g(n) {}

    void add_edge(ll a, ll b) {
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<ll> get() {
        REP(i, n) deg[i] = g[i].size();
        ret = cnt = 0, alive = n;
        dfs();
        vector<ll> ans_set;
        REP(i, n) if(ans[i]) ans_set.push_back(i);
        return ans_set;
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
        cout << graph.get().size() << endl;
    }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

