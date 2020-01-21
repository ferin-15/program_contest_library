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


# :heavy_check_mark: test/GRL5D.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/GRL5D.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 08:29:19+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_D">https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_D</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/lazysegtree.cpp.html">data_structure/lazysegtree.cpp</a>
* :heavy_check_mark: <a href="../../library/graph/HLDecomposition.cpp.html">graph/HLDecomposition.cpp</a>
* :heavy_check_mark: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_D"
#include "../memo/macro.hpp"
#include "../graph/HLDecomposition.cpp"
#include "../data_structure/lazysegtree.cpp"

signed main(void) {
    ll n;
    cin >> n;
    HLDecomposition hld(n);
    vector<ll> p(n, -1);
    REP(i, n) {
        ll k;
        cin >> k;
        REP(j, k) {
            ll c;
            cin >> c;
            hld.add_edge(i, c);
            p[c] = i;
        }
    }
    hld.build();

    lazysegtree<linear_exp> seg(n);
    vector<node> init(n);
    REP(i, n) init[i] = node(0);
    seg.build(init);

    ll q;
    cin >> q;
    while(q--) {
        ll type;
        cin >> type;
        if(type == 0) {
            ll v, w;
            cin >> v >> w;
            hld.for_each_edge(v, p[v], [&](ll a, ll b){
                seg.update(a, b+1, PII(1, w));
            });
        } else {
            ll v;
            cin >> v;
            ll ans = 0;
            hld.for_each_edge(v, 0, [&](ll a, ll b){
                ans += seg.query(a, b+1).sum;
            });
            cout << ans << endl;
        }
    }

    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/main.py", line 173, in main
    subcommand_run(paths=[], jobs=parsed.jobs)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/main.py", line 66, in subcommand_run
    onlinejudge_verify.verify.main(paths, marker=marker, timeout=timeout, jobs=jobs)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/verify.py", line 129, in main
    raise Exception('{} test failed'.format(len(failed_test_paths)))
Exception: 1 test failed

During handling of the above exception, another exception occurred:

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

