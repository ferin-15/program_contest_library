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


# :heavy_check_mark: test/GRL2A.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/GRL2A.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 07:11:31+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/unionfind.cpp.html">data_structure/unionfind.cpp</a>
* :heavy_check_mark: <a href="../../library/graph/boruvka.cpp.html">graph/boruvka.cpp</a>
* :heavy_check_mark: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=ja"
#include "../memo/macro.hpp"
#include "../data_structure/unionfind.cpp"
#include "../graph/boruvka.cpp"

signed main(void) {
    ll n, m;
    cin >> n >> m;
    vector<vector<PII>> g(n);
    REP(i, m) {
        ll a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }

    // O(fの計算量 * logV)
    // 各頂点から最小のコストの辺を求める
    // sz=連結成分数 belong[i]=i番目の頂点が属する連結成分
    function<vector<PII>(ll,vector<ll>)> f = [&](ll sz, vector<ll> belong) {
        // ret[i] = (連結成分iからコスト最小の辺の(コスト, i以外の端点の連結成分))
        // iがufの親以外ならsecondは-1として連結成分ごとに管理
        vector<PII> ret(sz, PII(INF, -1));

        REP(i, n) for(auto to: g[i]) {
            if(belong[i] == belong[to.first]) continue;
            chmin(ret[belong[i]], PII(to.second, belong[to.first]));
        }
        return ret;
    };
    cout << boruvka<ll, decltype(f)>(n, f) << endl;

    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 340, in write_contents
    bundler.update(self.file_class.file_path)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/bundle.py", line 154, in update
    self.update(self._resolve(included, included_from=path))
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/bundle.py", line 153, in update
    raise BundleError(path, i + 1, "unable to process #include in #if / #ifdef / #ifndef other than include guards")
onlinejudge_verify.bundle.BundleError: memo/macro.hpp: line 12: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

