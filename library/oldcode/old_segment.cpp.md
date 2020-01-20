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


# :warning: oldcode/old_segment.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#bf50ccff88ac9b2562bee63cf804278c">oldcode</a>
* <a href="{{ site.github.repository_url }}/blob/master/oldcode/old_segment.cpp">View this file on GitHub</a>
    - Last commit date: 2019-10-03 22:20:29+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <typename T>
struct segtree {
    using F = function<T(T,T)>;
    int n;
    vector<T> dat;
    F f, g;
    T d;

    segtree(int n_, F f_, F g_, T d_) : f(f_), g(g_), d(d_) {
        n = 1;
        while(n < n_) n *= 2;
        dat.assign(n*2, d);
    }
    void build(vector<T> v) {
        REP(i, v.size()) dat[i+n-1] = v[i];
        for(int i=n-2; i>=0; --i) dat[i] = f(dat[i*2+1], dat[i*2+2]);
    }

    T query(int a, int b, int k, int l, int r) {
        if(r <= a || b <= l) return d;
        if(a <= l && r <= b) return dat[k];
        return f(query(a, b, 2*k+1, l, (l+r)/2),
                query(a, b, 2*k+2, (l+r)/2, r));
    }
    T query(int a, int b) {return query(a, b, 0, 0, n);}
    void update(int i, T v) {
        i += n-1;
        dat[i] = g(dat[i], v);
            while(i > 0) {
            i = (i-1)/2;
            dat[i] = f(dat[i*2+1], dat[i*2+2]);
        }
    }

    void debug() {
        cout << "---------------------" << endl;
        int cnt = 0;
        for(int i=1; i<=n; i*=2) {
            REP(j, i) {
                cout << dat[cnt] << " ";
                cnt++;
            }
            cout << endl;
        }
        cout << "---------------------" << endl;
    }
};
/**
* 点更新区間min d=INF, f=min(a,b), g=b
* 点更新区間max d=-INF, f=max(a,b), g=b
* 点加算区間和  d=0, f=a+b, g+=b
*/

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "oldcode/old_segment.cpp"
template <typename T>
struct segtree {
    using F = function<T(T,T)>;
    int n;
    vector<T> dat;
    F f, g;
    T d;

    segtree(int n_, F f_, F g_, T d_) : f(f_), g(g_), d(d_) {
        n = 1;
        while(n < n_) n *= 2;
        dat.assign(n*2, d);
    }
    void build(vector<T> v) {
        REP(i, v.size()) dat[i+n-1] = v[i];
        for(int i=n-2; i>=0; --i) dat[i] = f(dat[i*2+1], dat[i*2+2]);
    }

    T query(int a, int b, int k, int l, int r) {
        if(r <= a || b <= l) return d;
        if(a <= l && r <= b) return dat[k];
        return f(query(a, b, 2*k+1, l, (l+r)/2),
                query(a, b, 2*k+2, (l+r)/2, r));
    }
    T query(int a, int b) {return query(a, b, 0, 0, n);}
    void update(int i, T v) {
        i += n-1;
        dat[i] = g(dat[i], v);
            while(i > 0) {
            i = (i-1)/2;
            dat[i] = f(dat[i*2+1], dat[i*2+2]);
        }
    }

    void debug() {
        cout << "---------------------" << endl;
        int cnt = 0;
        for(int i=1; i<=n; i*=2) {
            REP(j, i) {
                cout << dat[cnt] << " ";
                cnt++;
            }
            cout << endl;
        }
        cout << "---------------------" << endl;
    }
};
/**
* 点更新区間min d=INF, f=min(a,b), g=b
* 点更新区間max d=-INF, f=max(a,b), g=b
* 点加算区間和  d=0, f=a+b, g+=b
*/

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

