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


# :warning: data_structure/segtree_range_freq.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/segtree_range_freq.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 04:35:05+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct segTreeRangeFreq {
    int n;
    vector<vector<ll>> dat;
    // 初期化 O(NlogN)
    segTreeRangeFreq() {}
    segTreeRangeFreq(vector<vector<ll>> v) {
        n = 1; while(n < (ll)v.size()) n *= 2;
        dat.resize(2*n-1);
        REP(i, v.size()) dat[i+n-1] = v[i];
        for(int i=n-2; i>=0; --i) {
            dat[i].resize(dat[i*2+1].size() + dat[i*2+2].size());
            merge(ALL(dat[i*2+1]), ALL(dat[i*2+2]), dat[i].begin());
        }
    }
    // [a, b) のx以下の個数を返す O(log^2N)
    int query(int a, int b, ll x, int k, int l, int r) {
        if(b <= l || r <= a) return 0;
        if(a <= l && r <= b) return upper_bound(ALL(dat[k]), x) - dat[k].begin();
        int vl = query(a, b, x, k*2+1, l, (l+r)/2);
        int vr = query(a, b, x, k*2+2, (l+r)/2, r);
        return vl + vr;
    }
    int query(int a, int b, ll x) { return query(a, b, x, 0, 0, n); }
};

// 2次元平面上の点集合 矩形中に何個点があるかのクエリに答えることが可能
// (x[i], y[i]) をxでソートしてyをセグ木に乗せるとrangefreqになる
// wavelet matrixじゃなくてセグ木でO(log^2N)でok

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/segtree_range_freq.cpp"
struct segTreeRangeFreq {
    int n;
    vector<vector<ll>> dat;
    // 初期化 O(NlogN)
    segTreeRangeFreq() {}
    segTreeRangeFreq(vector<vector<ll>> v) {
        n = 1; while(n < (ll)v.size()) n *= 2;
        dat.resize(2*n-1);
        REP(i, v.size()) dat[i+n-1] = v[i];
        for(int i=n-2; i>=0; --i) {
            dat[i].resize(dat[i*2+1].size() + dat[i*2+2].size());
            merge(ALL(dat[i*2+1]), ALL(dat[i*2+2]), dat[i].begin());
        }
    }
    // [a, b) のx以下の個数を返す O(log^2N)
    int query(int a, int b, ll x, int k, int l, int r) {
        if(b <= l || r <= a) return 0;
        if(a <= l && r <= b) return upper_bound(ALL(dat[k]), x) - dat[k].begin();
        int vl = query(a, b, x, k*2+1, l, (l+r)/2);
        int vr = query(a, b, x, k*2+2, (l+r)/2, r);
        return vl + vr;
    }
    int query(int a, int b, ll x) { return query(a, b, x, 0, 0, n); }
};

// 2次元平面上の点集合 矩形中に何個点があるかのクエリに答えることが可能
// (x[i], y[i]) をxでソートしてyをセグ木に乗せるとrangefreqになる
// wavelet matrixじゃなくてセグ木でO(log^2N)でok

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

