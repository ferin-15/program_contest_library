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


# :warning: oldcode/persistentArray.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#bf50ccff88ac9b2562bee63cf804278c">oldcode</a>
* <a href="{{ site.github.repository_url }}/blob/master/oldcode/persistentArray.cpp">View this file on GitHub</a>
    - Last commit date: 2019-10-03 22:20:29+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<typename T, int B = 3>
class persistentArray {
private:
    struct node {
        node *ch[1<<B] = {};
        T val = -1;

        node() {}
        node(const T &v) : val(v) {} 
    };

    node *root;

    node* build(node *x, const T &dat, int a) {
        if(!x) x = new node();
        if(a == 0) {
            x->val = dat;
            return x;
        }
        auto p = build(x->ch[a&((1<<B)-1)], dat, a>>B);
        x->ch[a&((1<<B)-1)] = p;
        return x;
    }
    pair<node*, T*> mutable_get(node* x, int a) {
        x = x ? new node(*x) : new node();
        if(a == 0) return {x, &x->val};
        auto p = mutable_get(x->ch[a&((1<<B)-1)], a >> B);
        x->ch[a&((1<<B)-1)] = p.first;
        return make_pair(x, p.second);
    }
    T immutable_get(int a, node* x) {
        if(a == 0) return x->val;
        return immutable_get(a>>B, x->ch[a & ((1<<B)-1)]);
    }
public:
    persistentArray() : root(nullptr) {}

    void build(const V<T> &v) {
        for(int i=0; i<(int)v.size(); ++i) {
            root = build(root, v[i], i);
        }
    }

    T *mutable_get(const int &k) {
        auto p = mutable_get(root, k);
        root = p.first;
        return p.second;
    }
    T operator[](int k) {
        return immutable_get(k, root);
    }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "oldcode/persistentArray.cpp"
template<typename T, int B = 3>
class persistentArray {
private:
    struct node {
        node *ch[1<<B] = {};
        T val = -1;

        node() {}
        node(const T &v) : val(v) {} 
    };

    node *root;

    node* build(node *x, const T &dat, int a) {
        if(!x) x = new node();
        if(a == 0) {
            x->val = dat;
            return x;
        }
        auto p = build(x->ch[a&((1<<B)-1)], dat, a>>B);
        x->ch[a&((1<<B)-1)] = p;
        return x;
    }
    pair<node*, T*> mutable_get(node* x, int a) {
        x = x ? new node(*x) : new node();
        if(a == 0) return {x, &x->val};
        auto p = mutable_get(x->ch[a&((1<<B)-1)], a >> B);
        x->ch[a&((1<<B)-1)] = p.first;
        return make_pair(x, p.second);
    }
    T immutable_get(int a, node* x) {
        if(a == 0) return x->val;
        return immutable_get(a>>B, x->ch[a & ((1<<B)-1)]);
    }
public:
    persistentArray() : root(nullptr) {}

    void build(const V<T> &v) {
        for(int i=0; i<(int)v.size(); ++i) {
            root = build(root, v[i], i);
        }
    }

    T *mutable_get(const int &k) {
        auto p = mutable_get(root, k);
        root = p.first;
        return p.second;
    }
    T operator[](int k) {
        return immutable_get(k, root);
    }
};
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

