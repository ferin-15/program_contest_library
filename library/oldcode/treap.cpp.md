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


# :warning: oldcode/treap.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#bf50ccff88ac9b2562bee63cf804278c">oldcode</a>
* <a href="{{ site.github.repository_url }}/blob/master/oldcode/treap.cpp">View this file on GitHub</a>
    - Last commit date: 2019-10-03 22:20:29+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
using ull = unsigned long long;
ull randxor(){
    static ull x=123456789,y=362436069,z=521288629,w=88675123;
    ull t=(x^(x<<11));
    x=y; y=z; z=w;
    return w=(w^(w>>19))^(t^(t>>8));
}

struct node {
    int val;
    node *ch[2];
    double pri;
    int cnt; //部分木のサイズ
    int sum; //部分木の値の和

    node(int v, double p): val(v),pri(p),cnt(1),sum(v) {
        ch[0] = ch[1] = nullptr;
    }
};

int count(node *t) {return t == nullptr ? 0: t->cnt;}
int sum(node *t) {return t == nullptr ? 0: t->sum;}

node *update(node *t) {
    t->cnt = count(t->ch[0]) + count(t->ch[1]) + 1;
    t->sum = sum(t->ch[0]) + sum(t->ch[1]) + t->val;
    return t;
}

// b=0で左回転、b=1で右回転
node *rotate(node *t, int b) {
    node *s = t->ch[1-b];
    t->ch[1-b] = s->ch[b];
    s->ch[b] = t;
    update(t);
    update(s);
    return s;
}

node *insert(node *t, int val, double pri) {
    if(t == nullptr) return new node(val, pri);
    else if(val == t->val) return t;
    else if(val < t->val) {
        t->ch[0] = insert(t->ch[0], val, pri);
        if(t->pri > t->ch[0]->pri) {
            t = rotate(t, 1);
        }
    } else{
        t->ch[1] = insert(t->ch[1], val, pri);
        if(t->pri > t->ch[1]->pri) {
            t = rotate(t, 0);
        }
    }
    return update(t);
}

node *erase(node *t, int x) {
    if (t->val == x) {
        if (t->ch[0] && t->ch[1]) {
            if (t->ch[0]->pri < t->ch[1]->pri) {
                t = rotate(t, 1);
                t->ch[1] = erase(t->ch[1], x);
                return update(t);
            } else {
                t = rotate(t, 0);
                t->ch[0] = erase(t->ch[0], x);
                return update(t);
            }
        } else {
            return t->ch[0] ? t->ch[0] : t->ch[1];
        }
    } else if (x < t->val) {
        t->ch[0] = erase(t->ch[0], x);
    } else {
        t->ch[1] = erase(t->ch[1], x);
    }
    return update(t);
}

int level(node *t, int k) {
    if(k < count(t->ch[0])) return level(t->ch[0], k);
    if(k == count(t->ch[0])) return t->val;
    return level(t->ch[1], k-count(t->ch[0])-1);
}

signed main(void)
{
    int q;
    cin >> q;

    node *root = nullptr;
    REP(i, q) {
        int t, x;
        cin >> t >> x;
        if(t == 1) {
            const int R = 100000;
            double r = randxor() % R / (double)R;
            root = insert(root, x, r);
        } else {
            int k = level(root, x-1);
            root = erase(root, k);
            cout << k << endl;
        }
    }

    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "oldcode/treap.cpp"
using ull = unsigned long long;
ull randxor(){
    static ull x=123456789,y=362436069,z=521288629,w=88675123;
    ull t=(x^(x<<11));
    x=y; y=z; z=w;
    return w=(w^(w>>19))^(t^(t>>8));
}

struct node {
    int val;
    node *ch[2];
    double pri;
    int cnt; //部分木のサイズ
    int sum; //部分木の値の和

    node(int v, double p): val(v),pri(p),cnt(1),sum(v) {
        ch[0] = ch[1] = nullptr;
    }
};

int count(node *t) {return t == nullptr ? 0: t->cnt;}
int sum(node *t) {return t == nullptr ? 0: t->sum;}

node *update(node *t) {
    t->cnt = count(t->ch[0]) + count(t->ch[1]) + 1;
    t->sum = sum(t->ch[0]) + sum(t->ch[1]) + t->val;
    return t;
}

// b=0で左回転、b=1で右回転
node *rotate(node *t, int b) {
    node *s = t->ch[1-b];
    t->ch[1-b] = s->ch[b];
    s->ch[b] = t;
    update(t);
    update(s);
    return s;
}

node *insert(node *t, int val, double pri) {
    if(t == nullptr) return new node(val, pri);
    else if(val == t->val) return t;
    else if(val < t->val) {
        t->ch[0] = insert(t->ch[0], val, pri);
        if(t->pri > t->ch[0]->pri) {
            t = rotate(t, 1);
        }
    } else{
        t->ch[1] = insert(t->ch[1], val, pri);
        if(t->pri > t->ch[1]->pri) {
            t = rotate(t, 0);
        }
    }
    return update(t);
}

node *erase(node *t, int x) {
    if (t->val == x) {
        if (t->ch[0] && t->ch[1]) {
            if (t->ch[0]->pri < t->ch[1]->pri) {
                t = rotate(t, 1);
                t->ch[1] = erase(t->ch[1], x);
                return update(t);
            } else {
                t = rotate(t, 0);
                t->ch[0] = erase(t->ch[0], x);
                return update(t);
            }
        } else {
            return t->ch[0] ? t->ch[0] : t->ch[1];
        }
    } else if (x < t->val) {
        t->ch[0] = erase(t->ch[0], x);
    } else {
        t->ch[1] = erase(t->ch[1], x);
    }
    return update(t);
}

int level(node *t, int k) {
    if(k < count(t->ch[0])) return level(t->ch[0], k);
    if(k == count(t->ch[0])) return t->val;
    return level(t->ch[1], k-count(t->ch[0])-1);
}

signed main(void)
{
    int q;
    cin >> q;

    node *root = nullptr;
    REP(i, q) {
        int t, x;
        cin >> t >> x;
        if(t == 1) {
            const int R = 100000;
            double r = randxor() % R / (double)R;
            root = insert(root, x, r);
        } else {
            int k = level(root, x-1);
            root = erase(root, k);
            cout << k << endl;
        }
    }

    return 0;
}
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

