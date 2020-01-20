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


# :warning: data_structure/segment_tree_beats.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/segment_tree_beats.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 04:35:05+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// 更新が区間chmin クエリが区間和と区間max
template<typename dat_type, typename lazy_type>
struct segtree {
    ll n;
    vector<dat_type> dat;
    dat_type dat_d;
    vector<lazy_type> lazy;
    lazy_type lazy_d;

    using F = function<dat_type(dat_type,dat_type)>;
    F merge_dat;

    segtree() {}
    segtree(int n_, F md, dat_type dd, ll ld)
        : dat_d(dd), lazy_d(ld), merge_dat(md)
    {
        n = 1; while(n < n_) n *= 2;
        dat.assign(n*2, dat_d);
        lazy.assign(n*2, lazy_d);
    }

    void build(vector<dat_type> v) {
        REP(i, v.size()) dat[i+n-1] = v[i];
        for(int i=n-2; i>=0; --i) {
            dat[i] = merge_dat(dat[i*2+1], dat[i*2+2]);
        }
    }

    void eval(int k, int l, int r) {
        if(lazy[k] == lazy_d) return;
        // dat[k] に lazy[k] を作用させる
        if(dat[k].max > lazy[k]) {
            dat[k].sum -= (dat[k].max - lazy[k]) * dat[k].cnt;
            dat[k].max = lazy[k];
        }
        if(k*2+1 < n*2-1) {
            // lazy[k] を下に伝播させる
            chmin(lazy[2*k+1], lazy[k]);
            chmin(lazy[2*k+2], lazy[k]);
        }
        lazy[k] = lazy_d;
    }

    void update(int a, int b, ll x, int k, int l, int r) {
        eval(k, l, r);
        // break_condition
        if(b <= l || r <= a || dat[k].max <= x) return;
        // tag_condition
        if(a <= l && r <= b && dat[k].second < x) {
            // lazyへ値を代入
            lazy[k] = x;
            eval(k, l, r);
            return;
        }
        int m = (l+r)>>1;
        update(a, b, x, 2*k+1, l, m);
        update(a, b, x, 2*k+2, m, r);
        dat[k] = merge_dat(dat[2*k+1], dat[2*k+2]);
    }
    void update(int a, int b, ll x) { update(a, b, x, 0, 0, n); }

    dat_type query(int a, int b, int k, int l, int r) {
        eval(k, l, r);
        if(b <= l || r <= a) return dat_d;
        if(a <= l && r <= b) return dat[k];

        int m=(l+r)>>1;
        dat_type vl = query(a, b, 2*k+1, l, m);
        dat_type vr = query(a, b, 2*k+2, m, r);
        return merge_dat(vl, vr);
    }
    dat_type query(int a, int b) { return query(a, b, 0, 0, n); }

    // デバッグ出力
    void debug() {
        cout << "---------------------" << endl;
        int cnt = 0;
        for(int i=1; i<=n; i*=2) {
        REP(j, i) {
            cout << "([" << dat[cnt].sum << "," << dat[cnt].max << "," << dat[cnt].second << "," <<  dat[cnt].cnt << "]," << lazy[cnt] << ") ";
            cnt++;
        }
        cout << endl;
        }
        cout << "---------------------" << endl;
    }
};

signed main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll t;
    cin >> t;

    struct node {
        ll sum, max, second, cnt;
        node(ll v=0) : sum(v), max(v), second(-LLINF), cnt(1) {}
    };
    auto merge_dat = [](node l, node r) {
        node ret;
        ret.sum = l.sum + r.sum;
        ret.max = max(l.max, r.max);
        if(ret.max == l.max && ret.max == r.max) {
            ret.second = max(l.second, r.second);
            ret.cnt = l.cnt + r.cnt;
        } else {
            ret.cnt = l.max > r.max ? l.cnt : r.cnt;
            ret.second = max({min(l.max, r.max), l.second, r.second});
        }
        assert(ret.max != ret.second);
        return ret;
    };

    while(t--) {
        ll n, m;
        cin >> n >> m;

        segtree<node,ll> seg(n, merge_dat, node(), LLINF);

        REP(i, n) {
            ll a;
            cin >> a;
            seg.dat[i+seg.n-1] = node(a);
        }
        for(int i=seg.n-2; i>=0; --i) {
            seg.dat[i] = merge_dat(seg.dat[i*2+1], seg.dat[i*2+2]);
        }
        REP(i, m) {
            ll t;
            cin >> t;
            if(t == 0) {
                ll l, r, x;
                cin >> l >> r >> x;
                seg.update(l-1, r, x);
            } else if(t == 1) {
                ll l, r;
                cin >> l >> r;
                cout << seg.query(l-1, r).max << endl;
            } else if(t == 2) {
                ll l, r;
                cin >> l >> r;
                cout << seg.query(l-1, r).sum << endl;
            }
        }
    }

    return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/segment_tree_beats.cpp"
// 更新が区間chmin クエリが区間和と区間max
template<typename dat_type, typename lazy_type>
struct segtree {
    ll n;
    vector<dat_type> dat;
    dat_type dat_d;
    vector<lazy_type> lazy;
    lazy_type lazy_d;

    using F = function<dat_type(dat_type,dat_type)>;
    F merge_dat;

    segtree() {}
    segtree(int n_, F md, dat_type dd, ll ld)
        : dat_d(dd), lazy_d(ld), merge_dat(md)
    {
        n = 1; while(n < n_) n *= 2;
        dat.assign(n*2, dat_d);
        lazy.assign(n*2, lazy_d);
    }

    void build(vector<dat_type> v) {
        REP(i, v.size()) dat[i+n-1] = v[i];
        for(int i=n-2; i>=0; --i) {
            dat[i] = merge_dat(dat[i*2+1], dat[i*2+2]);
        }
    }

    void eval(int k, int l, int r) {
        if(lazy[k] == lazy_d) return;
        // dat[k] に lazy[k] を作用させる
        if(dat[k].max > lazy[k]) {
            dat[k].sum -= (dat[k].max - lazy[k]) * dat[k].cnt;
            dat[k].max = lazy[k];
        }
        if(k*2+1 < n*2-1) {
            // lazy[k] を下に伝播させる
            chmin(lazy[2*k+1], lazy[k]);
            chmin(lazy[2*k+2], lazy[k]);
        }
        lazy[k] = lazy_d;
    }

    void update(int a, int b, ll x, int k, int l, int r) {
        eval(k, l, r);
        // break_condition
        if(b <= l || r <= a || dat[k].max <= x) return;
        // tag_condition
        if(a <= l && r <= b && dat[k].second < x) {
            // lazyへ値を代入
            lazy[k] = x;
            eval(k, l, r);
            return;
        }
        int m = (l+r)>>1;
        update(a, b, x, 2*k+1, l, m);
        update(a, b, x, 2*k+2, m, r);
        dat[k] = merge_dat(dat[2*k+1], dat[2*k+2]);
    }
    void update(int a, int b, ll x) { update(a, b, x, 0, 0, n); }

    dat_type query(int a, int b, int k, int l, int r) {
        eval(k, l, r);
        if(b <= l || r <= a) return dat_d;
        if(a <= l && r <= b) return dat[k];

        int m=(l+r)>>1;
        dat_type vl = query(a, b, 2*k+1, l, m);
        dat_type vr = query(a, b, 2*k+2, m, r);
        return merge_dat(vl, vr);
    }
    dat_type query(int a, int b) { return query(a, b, 0, 0, n); }

    // デバッグ出力
    void debug() {
        cout << "---------------------" << endl;
        int cnt = 0;
        for(int i=1; i<=n; i*=2) {
        REP(j, i) {
            cout << "([" << dat[cnt].sum << "," << dat[cnt].max << "," << dat[cnt].second << "," <<  dat[cnt].cnt << "]," << lazy[cnt] << ") ";
            cnt++;
        }
        cout << endl;
        }
        cout << "---------------------" << endl;
    }
};

signed main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll t;
    cin >> t;

    struct node {
        ll sum, max, second, cnt;
        node(ll v=0) : sum(v), max(v), second(-LLINF), cnt(1) {}
    };
    auto merge_dat = [](node l, node r) {
        node ret;
        ret.sum = l.sum + r.sum;
        ret.max = max(l.max, r.max);
        if(ret.max == l.max && ret.max == r.max) {
            ret.second = max(l.second, r.second);
            ret.cnt = l.cnt + r.cnt;
        } else {
            ret.cnt = l.max > r.max ? l.cnt : r.cnt;
            ret.second = max({min(l.max, r.max), l.second, r.second});
        }
        assert(ret.max != ret.second);
        return ret;
    };

    while(t--) {
        ll n, m;
        cin >> n >> m;

        segtree<node,ll> seg(n, merge_dat, node(), LLINF);

        REP(i, n) {
            ll a;
            cin >> a;
            seg.dat[i+seg.n-1] = node(a);
        }
        for(int i=seg.n-2; i>=0; --i) {
            seg.dat[i] = merge_dat(seg.dat[i*2+1], seg.dat[i*2+2]);
        }
        REP(i, m) {
            ll t;
            cin >> t;
            if(t == 0) {
                ll l, r, x;
                cin >> l >> r >> x;
                seg.update(l-1, r, x);
            } else if(t == 1) {
                ll l, r;
                cin >> l >> r;
                cout << seg.query(l-1, r).max << endl;
            } else if(t == 2) {
                ll l, r;
                cin >> l >> r;
                cout << seg.query(l-1, r).sum << endl;
            }
        }
    }

    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

