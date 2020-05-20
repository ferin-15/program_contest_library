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


# :heavy_check_mark: DP/convex_hull_trick.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e2fca8135c2fadca093abd79a6b1c0d2">DP</a>
* <a href="{{ site.github.repository_url }}/blob/master/DP/convex_hull_trick.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-20 15:31:47+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj2580_0.test.cpp.html">test/aoj2580_0.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
// 最小を求めてるので最大ならinsert(-a,-b), -get(x)
struct ConvexHullTrick {
    deque<PII> que;

    bool isright(const PII &p1, const PII &p2, int x) {
        return (p1.second-p2.second) >= x * (p2.first-p1.first);
    }
    bool check(const PII &a, const PII &b, const PII &c) {
        return (b.first-a.first)*(c.second-b.second)>=(b.second-a.second)*(c.first-b.first);
    }
    ll f(const PII &p, ll x) { return p.first * x + p.second; }

    // ax+bを追加 (aについて降順にすること)
    void insert(ll a, ll b) {
        PII p(a, b);
        while(que.size() >= 2 && check(que[que.size()-2], que.back(), p)) {
            que.pop_back();
        }
        que.push_back(p);
    }
    // 単調性がある xの位置での最小のy
    ll incl_query(ll x) {
        assert(que.size());
        while(que.size() >= 2 && f(que[0],x) >= f(que[1],x)) {
            que.pop_front();
        }
        return que[0].first * x + que[0].second;
    }
    // 単調性なし
    ll query(ll x) {
        ll lb = -1, ub = (ll)que.size()-1;
        while(ub-lb > 1) {
            ll mid = (lb+ub)/2;
            if(isright(que[mid], que[mid+1], x)) lb = mid;
            else ub = mid;
        }
        return f(que[ub], x);
    }
};
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "DP/convex_hull_trick.cpp"
// BEGIN CUT
// 最小を求めてるので最大ならinsert(-a,-b), -get(x)
struct ConvexHullTrick {
    deque<PII> que;

    bool isright(const PII &p1, const PII &p2, int x) {
        return (p1.second-p2.second) >= x * (p2.first-p1.first);
    }
    bool check(const PII &a, const PII &b, const PII &c) {
        return (b.first-a.first)*(c.second-b.second)>=(b.second-a.second)*(c.first-b.first);
    }
    ll f(const PII &p, ll x) { return p.first * x + p.second; }

    // ax+bを追加 (aについて降順にすること)
    void insert(ll a, ll b) {
        PII p(a, b);
        while(que.size() >= 2 && check(que[que.size()-2], que.back(), p)) {
            que.pop_back();
        }
        que.push_back(p);
    }
    // 単調性がある xの位置での最小のy
    ll incl_query(ll x) {
        assert(que.size());
        while(que.size() >= 2 && f(que[0],x) >= f(que[1],x)) {
            que.pop_front();
        }
        return que[0].first * x + que[0].second;
    }
    // 単調性なし
    ll query(ll x) {
        ll lb = -1, ub = (ll)que.size()-1;
        while(ub-lb > 1) {
            ll mid = (lb+ub)/2;
            if(isright(que[mid], que[mid+1], x)) lb = mid;
            else ub = mid;
        }
        return f(que[ub], x);
    }
};
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

