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


# :heavy_check_mark: test/GRL6A_1.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/GRL6A_1.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_A">https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_A</a>


## Depends on

* :heavy_check_mark: <a href="../../library/graph/ford_fulkerson.cpp.html">graph/ford_fulkerson.cpp</a>
* :question: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_A"
#include "../memo/macro.hpp"
#include "../graph/ford_fulkerson.cpp"

signed main(void) {
    ll v, e;
    cin >> v >> e;
    FordFulkerson flow(v);
    REP(i, e) {
        ll u, v, c;
        cin >> u >> v >> c;
        flow.add_edge(u, v, c);
    }

    cout << flow.max_flow(0, v-1) << endl;

    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/GRL6A_1.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_A"
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
#line 1 "graph/ford_fulkerson.cpp"
// BEGIN CUT
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
// END CUT
#line 4 "test/GRL6A_1.test.cpp"

signed main(void) {
    ll v, e;
    cin >> v >> e;
    FordFulkerson flow(v);
    REP(i, e) {
        ll u, v, c;
        cin >> u >> v >> c;
        flow.add_edge(u, v, c);
    }

    cout << flow.max_flow(0, v-1) << endl;

    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

