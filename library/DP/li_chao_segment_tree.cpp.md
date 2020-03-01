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


# :x: DP/li_chao_segment_tree.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e2fca8135c2fadca093abd79a6b1c0d2">DP</a>
* <a href="{{ site.github.repository_url }}/blob/master/DP/li_chao_segment_tree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00




## Verified with

* :x: <a href="../../verify/test/aoj2580_1.test.cpp.html">test/aoj2580_1.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
// 単調性なしok 動的CHT 各操作O(logN)
template <typename T, const T id = numeric_limits<T>::min()>
class ConvexHullTrick {
private:
    struct line {
        T a, b;
        line(T a_ = 0, T b_ = 0) : a(a_), b(b_) {}
        // ll でも overflow するのに注意
        T get(T x) { return a * x + b; }
    };
    struct node {
        line l;
        node *lch, *rch;
        node(line l_) : l(l_), lch(nullptr), rch(nullptr) {}
    };

    const T minx, maxx;
    node *root = nullptr;

    // [lb, ub]
    node* update(node *p, ll lb, ll ub, line& l) {
        if (!p) return new node(l);
        if (p->l.get(lb) >= l.get(lb) && p->l.get(ub) >= l.get(ub)) return p;
        if (p->l.get(lb) <= l.get(lb) && p->l.get(ub) <= l.get(ub)) {
          p->l = l;
          return p;
        }
        ll mid = (lb + ub) / 2;
        if (p->l.get(mid) < l.get(mid)) swap(p->l, l);
        if (p->l.get(lb) <= l.get(lb)) p->lch = update(p->lch, lb, mid, l);
        else p->rch = update(p->rch, mid + 1, ub, l);
        return p;
    }
    // [lb, ub]
    T query(node *p, ll lb, ll ub, ll t) const {
        if(!p) return id;
        if(ub == lb) return p->l.get(t);
        ll mid = (lb+ub)/2;
        if(t <= mid) return max(p->l.get(t), query(p->lch, lb, mid, t));
        return max(p->l.get(t), query(p->rch, mid + 1, ub, t));
    }
public:
    // getで呼び出しうるxの範囲を指定
    ConvexHullTrick(const T minx_, const T maxx_) : minx(minx_), maxx(maxx_) {}
    // 直線ax+bを追加 最小がほしければ-ax-bを渡してgetの結果に×(-1)する
    void insert(T a, T b) {
        line l(a, b);
        root = update(root, minx, maxx, l);
    }
    // ax+b のうち最大のものを返す
    T get(T x) const { return query(root, minx, maxx, x); }
};
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "DP/li_chao_segment_tree.cpp"
// BEGIN CUT
// 単調性なしok 動的CHT 各操作O(logN)
template <typename T, const T id = numeric_limits<T>::min()>
class ConvexHullTrick {
private:
    struct line {
        T a, b;
        line(T a_ = 0, T b_ = 0) : a(a_), b(b_) {}
        // ll でも overflow するのに注意
        T get(T x) { return a * x + b; }
    };
    struct node {
        line l;
        node *lch, *rch;
        node(line l_) : l(l_), lch(nullptr), rch(nullptr) {}
    };

    const T minx, maxx;
    node *root = nullptr;

    // [lb, ub]
    node* update(node *p, ll lb, ll ub, line& l) {
        if (!p) return new node(l);
        if (p->l.get(lb) >= l.get(lb) && p->l.get(ub) >= l.get(ub)) return p;
        if (p->l.get(lb) <= l.get(lb) && p->l.get(ub) <= l.get(ub)) {
          p->l = l;
          return p;
        }
        ll mid = (lb + ub) / 2;
        if (p->l.get(mid) < l.get(mid)) swap(p->l, l);
        if (p->l.get(lb) <= l.get(lb)) p->lch = update(p->lch, lb, mid, l);
        else p->rch = update(p->rch, mid + 1, ub, l);
        return p;
    }
    // [lb, ub]
    T query(node *p, ll lb, ll ub, ll t) const {
        if(!p) return id;
        if(ub == lb) return p->l.get(t);
        ll mid = (lb+ub)/2;
        if(t <= mid) return max(p->l.get(t), query(p->lch, lb, mid, t));
        return max(p->l.get(t), query(p->rch, mid + 1, ub, t));
    }
public:
    // getで呼び出しうるxの範囲を指定
    ConvexHullTrick(const T minx_, const T maxx_) : minx(minx_), maxx(maxx_) {}
    // 直線ax+bを追加 最小がほしければ-ax-bを渡してgetの結果に×(-1)する
    void insert(T a, T b) {
        line l(a, b);
        root = update(root, minx, maxx, l);
    }
    // ax+b のうち最大のものを返す
    T get(T x) const { return query(root, minx, maxx, x); }
};
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

