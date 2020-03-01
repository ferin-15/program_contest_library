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


# :heavy_check_mark: data_structure/persistent_uf.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/persistent_uf.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj0575_1.test.cpp.html">test/aoj0575_1.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
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

    void build(const vector<T> &v) {
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

struct persistentUnionFind {
    persistentArray<int> data;

    persistentUnionFind() {}
    persistentUnionFind(int sz) { data.build(vector<int>(sz, -1)); }

    int find(int k) {
        int p = data[k];
        return p >= 0 ? find(p) : k;
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y) return;
        auto u = data[x];
        auto v = data[y];
        if(u < v) {
            auto a = data.mutable_get(x); *a += v;
            auto b = data.mutable_get(y); *b = x;
        } else {
            auto a = data.mutable_get(y); *a += u;
            auto b = data.mutable_get(x); *b = y;
        }
    }
    bool same(int x, int y) { return find(x) == find(y); }
    int size(int x) { return -data[find(x)]; }
};
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/persistent_uf.cpp"
// BEGIN CUT
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

    void build(const vector<T> &v) {
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

struct persistentUnionFind {
    persistentArray<int> data;

    persistentUnionFind() {}
    persistentUnionFind(int sz) { data.build(vector<int>(sz, -1)); }

    int find(int k) {
        int p = data[k];
        return p >= 0 ? find(p) : k;
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y) return;
        auto u = data[x];
        auto v = data[y];
        if(u < v) {
            auto a = data.mutable_get(x); *a += v;
            auto b = data.mutable_get(y); *b = x;
        } else {
            auto a = data.mutable_get(y); *a += u;
            auto b = data.mutable_get(x); *b = y;
        }
    }
    bool same(int x, int y) { return find(x) == find(y); }
    int size(int x) { return -data[find(x)]; }
};
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

