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


# :heavy_check_mark: test/yosupo-vertexaddsubtreesum.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo-vertexaddsubtreesum.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-21 01:24:30+09:00


* see: <a href="https://judge.yosupo.jp/problem/vertex_add_subtree_sum">https://judge.yosupo.jp/problem/vertex_add_subtree_sum</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/linkcuttree_subtree.cpp.html">data_structure/linkcuttree_subtree.cpp</a>
* :heavy_check_mark: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
#include "../memo/macro.hpp"
#include "../data_structure/linkcuttree_subtree.cpp"

int main(void) {
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    REP(i, n) cin >> a[i];
    
    struct SUM {
        ll ret, laz, all;
        SUM() : ret(0), laz(0), all(0) {}
        void toggle() {}
        void merge(ll key, const SUM &left, const SUM &right) {
            ret = laz + key + right.all;
            all = ret + left.all;
        }
        void add(const SUM &ch) { laz += ch.all; }
        void erase(const SUM &ch) { laz -= ch.all; }
    };
    LinkCutTreeForSubTree<ll,SUM> lct(a);

    REP(i, n-1) {
        ll p;
        cin >> p;
        lct.link(i+1, p);
    }
    while(q--) {
        ll t;
        cin >> t;
        if(t == 0) {
            ll u, x;
            cin >> u >> x;
            auto g = [](ll p, ll q) { return p+q; };
            lct.update(u, x, g);
        } else {
            ll u;
            cin >> u;
            cout << lct.query(u).ret << endl;
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

