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


# :x: test/yosupo-maximumIndependentSet.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo-maximumIndependentSet.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00


* see: <a href="https://judge.yosupo.jp/problem/maximum_independent_set">https://judge.yosupo.jp/problem/maximum_independent_set</a>


## Depends on

* :x: <a href="../../library/graph/max_independent_set.cpp.html">graph/max_independent_set.cpp</a>
* :heavy_check_mark: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/maximum_independent_set"
#include "../memo/macro.hpp"
#include "../graph/max_independent_set.cpp"

int main() {
    ll n, m;
    cin >> n >> m;
    maxIndependentSet graph(n);
    REP(i, m) {
        ll u, v;
        cin >> u >> v;
        graph.add_edge(u, v);
    }
    auto ans = graph.get();
    cout << ans.size() << "\n";
    REP(i, ans.size()) cout << ans[i] << (i+1==ans.size() ? "\n" : " ");
    cout << flush;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo-maximumIndependentSet.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/maximum_independent_set"
#line 1 "test/../memo/macro.hpp"
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
#line 1 "test/../graph/max_independent_set.cpp"
// BEGIN CUT
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
// END CUT

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
#line 4 "test/yosupo-maximumIndependentSet.test.cpp"

int main() {
    ll n, m;
    cin >> n >> m;
    maxIndependentSet graph(n);
    REP(i, m) {
        ll u, v;
        cin >> u >> v;
        graph.add_edge(u, v);
    }
    auto ans = graph.get();
    cout << ans.size() << "\n";
    REP(i, ans.size()) cout << ans[i] << (i+1==ans.size() ? "\n" : " ");
    cout << flush;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

