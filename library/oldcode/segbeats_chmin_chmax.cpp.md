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


# :warning: oldcode/segbeats_chmin_chmax.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#bf50ccff88ac9b2562bee63cf804278c">oldcode</a>
* <a href="{{ site.github.repository_url }}/blob/master/oldcode/segbeats_chmin_chmax.cpp">View this file on GitHub</a>
    - Last commit date: 2019-10-03 22:20:29+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<typename node>
struct segtreebeats {
    ll n;
    vector<node> dat;
    vector<PII> lazy;
    node dt;
    PII de;

    segtreebeats() : n(-1) {}
    segtreebeats(int n_) : de({LLINF, 0}) {
        n = 1; while(n < n_) n *= 2;
        dat.assign(n*2-1, dt);
        lazy.assign(n*2-1, de);
    }
    void build(vector<node> v) {
        REP(i, v.size()) dat[i+n-1] = v[i];
        for(int i=n-2; i>=0; --i) dat[i] = merge(dat[i*2+1], dat[i*2+2]);
    }

    node query(int a, int b, int k, int l, int r) {
        if(b <= l || r <= a) return dt;
        if(a <= l && r <= b) return dat[k];
        push(k);
        const int m=(l+r)>>1;
        node vl = query(a, b, 2*k+1, l, m);
        node vr = query(a, b, 2*k+2, m, r);
        return merge(vl, vr);
    }
    node query(int a, int b) { return query(a, b, 0, 0, n); }

    node merge(node a, node b) {
        node ret;
        if(a.max < b.max) {
            ret.max = b.max;
            ret.maxc = b.maxc;
            ret.smax = max(a.max, b.smax);
        } else if(a.max > b.max) {
            ret.max = a.max;
            ret.maxc = a.maxc;
            ret.smax = max(a.smax, b.max);
        } else {
            ret.max = a.max;
            ret.maxc = a.maxc + b.maxc;
            ret.smax = max(a.smax, b.smax);
        }
        if(a.min < b.min) {
            ret.min = a.min;
            ret.minc = a.minc;
            ret.smin = min(a.smin, b.min);
        } else if(a.min > b.min) {
            ret.min = b.min;
            ret.minc = b.minc;
            ret.smin = min(a.min, b.smin);
        } else {
            ret.min = a.min;
            ret.minc = a.minc + b.minc;
            ret.smin = min(a.smin, b.smin);
        }
        ret.sum = a.sum + b.sum;
        ret.len = a.len + b.len;
        return ret;
    }

    void push(int k) {
        if(n-1 <= k) return;
        if(lazy[k].first != LLINF) {
            update_set_put(2*k+1, lazy[k].first);
            update_set_put(2*k+2, lazy[k].first);
            lazy[k].first = LLINF;
            return;
        }
        if(lazy[k].second != 0) {
            update_add_put(2*k+1, lazy[k].second);
            update_add_put(2*k+2, lazy[k].second);
            lazy[k].second = 0;
        }
        if(dat[k].max < dat[2*k+1].max) {
            update_min_put(2*k+1, dat[k].max);
        }
        if(dat[k].max < dat[2*k+2].max) {
            update_min_put(2*k+2, dat[k].max);
        }
        if(dat[k].min > dat[2*k+1].min) {
            update_max_put(2*k+1, dat[k].min);
        }
        if(dat[k].min > dat[2*k+2].min) {
            update_max_put(2*k+2, dat[k].min);
        }
    }

    void update_set_put(int k, ll x) {
        dat[k].max = dat[k].min = x;
        dat[k].smax = -LLINF;
        dat[k].smin = LLINF;
        dat[k].maxc = dat[k].minc = dat[k].len;
        dat[k].sum = x * dat[k].len;
        lazy[k].first = x; lazy[k].second = 0;
    }
    void update_set(int a, int b, ll x, int k, int l, int r) {
        if(b <= l || r <= a) return;
        if(a <= l && r <= b) {
            lazy[k] = update_set_put(k, x);
            return;
        }
        push(k);
        int m = (l+r)>>1;
        update_set(a, b, x, 2*k+1, l, m);
        update_set(a, b, x, 2*k+2, m, r);
        dat[k] = merge(dat[2*k+1], dat[2*k+2]);
    }
    void update_set(int a, int b, ll x) { update_set(a, b, x, 0, 0, n); }

    void update_add_put(int k, ll x) {
        dat[k].max += x;
        if(dat[k].smax != -LLINF) dat[k].smax += x;
        dat[k].min += x;
        if(dat[k].smin != LLINF) dat[k].smin += x;
        dat[k].sum += dat[k].len * x;
        if(lazy[k].first != LLINF) lazy[k].first += x;
        else lazy[k].second += x;
    }
    void update_add(int a, int b, ll x, int k, int l, int r) {
        if(b <= l || r <= a) return;
        if(a <= l && r <= b) {
            lazy[k] = update_add_put(k, x);
            return;
        }
        push(k);
        const int m = (l+r)>>1;
        update_add(a, b, x, 2*k+1, l, m);
        update_add(a, b, x, 2*k+2, m, r);
        dat[k] = merge(dat[2*k+1], dat[2*k+2]);
    }
    void update_add(int a, int b, ll x) { update_add(a, b, x, 0, 0, n); }

    void update_min_put(int k, ll x) {
        dat[k].sum += (x - dat[k].max) * dat[k].maxc;
        if(dat[k].max == dat[k].min) {
            dat[k].max = dat[k].min = x;
        } else if(dat[k].max == dat[k].smin) {
            dat[k].max = dat[k].smin = x;
        } else {
            dat[k].max = x;
        }
        if(lazy[k].first != LLINF && x < lazy[k].first) {
            lazy[k].first = x;
        }
    }
    void update_min(int a, int b, ll x, int k, int l, int r) {
        if(b <= l || r <= a || dat[k].max <= x) return;
        if(a <= l && r <= b && dat[k].smax < x) {
            update_min_put(k, x);
            return;
        }
        push(k);
        const int m = (l+r)>>1;
        update_min(a, b, x, 2*k+1, l, m);
        update_min(a, b, x, 2*k+2, m, r);
        dat[k] = merge(dat[2*k+1], dat[2*k+2]);
    }
    void update_min(int a, int b, ll x) { update_min(a, b, x, 0, 0, n); }

    void update_max_put(int k, ll x) {
        dat[k].sum += (x-dat[k].min) * dat[k].minc;
        if(dat[k].max == dat[k].min) {
            dat[k].max = dat[k].min = x;
        } else if(dat[k].smax == dat[k].min) {
            dat[k].smax = dat[k].min = x;
        } else {
            dat[k].min = x;
        }
        if(lazy[k].first != LLINF && x > lazy[k].first) {
            lazy[k].first = x;
        }
    }
    void update_max(int a, int b, ll x, int k, int l, int r) {
        if(b <= l || r <= a || dat[k].min >= x) return;
        if(a <= l && r <= b && dat[k].smin > x) {
            update_max_put(k, x);
            return;
        }
        push(k);
        const int m = (l+r)>>1;
        update_max(a, b, x, 2*k+1, l, m);
        update_max(a, b, x, 2*k+2, m, r);
        dat[k] = merge(dat[2*k+1], dat[2*k+2]);
    }
    void update_max(int a, int b, ll x) { update_max(a, b, x, 0, 0, n); }

    // デバッグ出力
    void debug() {
        cout << "---------------------" << endl;
        int cnt = 0;
        for(int i=1; i<=n; i*=2) {
        REP(j, i) {
            cout << "([" << dat[cnt].sum << "," << dat[cnt].max << "," << dat[cnt].smax << "," <<  dat[cnt].maxc << "]," << lazy[cnt] << ") ";
            cnt++;
        }
        cout << endl;
        }
        cout << "---------------------" << endl;
    }
};

struct node {
    ll max, smax, maxc, min, smin, minc, sum, len;
    node() : max(-LLINF), smax(-LLINF), maxc(0), min(LLINF), smin(LLINF), minc(0), sum(0), len(0) {}
    node(ll v) : max(v), smax(-LLINF), maxc(1), min(v), smin(LLINF), minc(1), sum(v), len(1) {}
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "oldcode/segbeats_chmin_chmax.cpp"
template<typename node>
struct segtreebeats {
    ll n;
    vector<node> dat;
    vector<PII> lazy;
    node dt;
    PII de;

    segtreebeats() : n(-1) {}
    segtreebeats(int n_) : de({LLINF, 0}) {
        n = 1; while(n < n_) n *= 2;
        dat.assign(n*2-1, dt);
        lazy.assign(n*2-1, de);
    }
    void build(vector<node> v) {
        REP(i, v.size()) dat[i+n-1] = v[i];
        for(int i=n-2; i>=0; --i) dat[i] = merge(dat[i*2+1], dat[i*2+2]);
    }

    node query(int a, int b, int k, int l, int r) {
        if(b <= l || r <= a) return dt;
        if(a <= l && r <= b) return dat[k];
        push(k);
        const int m=(l+r)>>1;
        node vl = query(a, b, 2*k+1, l, m);
        node vr = query(a, b, 2*k+2, m, r);
        return merge(vl, vr);
    }
    node query(int a, int b) { return query(a, b, 0, 0, n); }

    node merge(node a, node b) {
        node ret;
        if(a.max < b.max) {
            ret.max = b.max;
            ret.maxc = b.maxc;
            ret.smax = max(a.max, b.smax);
        } else if(a.max > b.max) {
            ret.max = a.max;
            ret.maxc = a.maxc;
            ret.smax = max(a.smax, b.max);
        } else {
            ret.max = a.max;
            ret.maxc = a.maxc + b.maxc;
            ret.smax = max(a.smax, b.smax);
        }
        if(a.min < b.min) {
            ret.min = a.min;
            ret.minc = a.minc;
            ret.smin = min(a.smin, b.min);
        } else if(a.min > b.min) {
            ret.min = b.min;
            ret.minc = b.minc;
            ret.smin = min(a.min, b.smin);
        } else {
            ret.min = a.min;
            ret.minc = a.minc + b.minc;
            ret.smin = min(a.smin, b.smin);
        }
        ret.sum = a.sum + b.sum;
        ret.len = a.len + b.len;
        return ret;
    }

    void push(int k) {
        if(n-1 <= k) return;
        if(lazy[k].first != LLINF) {
            update_set_put(2*k+1, lazy[k].first);
            update_set_put(2*k+2, lazy[k].first);
            lazy[k].first = LLINF;
            return;
        }
        if(lazy[k].second != 0) {
            update_add_put(2*k+1, lazy[k].second);
            update_add_put(2*k+2, lazy[k].second);
            lazy[k].second = 0;
        }
        if(dat[k].max < dat[2*k+1].max) {
            update_min_put(2*k+1, dat[k].max);
        }
        if(dat[k].max < dat[2*k+2].max) {
            update_min_put(2*k+2, dat[k].max);
        }
        if(dat[k].min > dat[2*k+1].min) {
            update_max_put(2*k+1, dat[k].min);
        }
        if(dat[k].min > dat[2*k+2].min) {
            update_max_put(2*k+2, dat[k].min);
        }
    }

    void update_set_put(int k, ll x) {
        dat[k].max = dat[k].min = x;
        dat[k].smax = -LLINF;
        dat[k].smin = LLINF;
        dat[k].maxc = dat[k].minc = dat[k].len;
        dat[k].sum = x * dat[k].len;
        lazy[k].first = x; lazy[k].second = 0;
    }
    void update_set(int a, int b, ll x, int k, int l, int r) {
        if(b <= l || r <= a) return;
        if(a <= l && r <= b) {
            lazy[k] = update_set_put(k, x);
            return;
        }
        push(k);
        int m = (l+r)>>1;
        update_set(a, b, x, 2*k+1, l, m);
        update_set(a, b, x, 2*k+2, m, r);
        dat[k] = merge(dat[2*k+1], dat[2*k+2]);
    }
    void update_set(int a, int b, ll x) { update_set(a, b, x, 0, 0, n); }

    void update_add_put(int k, ll x) {
        dat[k].max += x;
        if(dat[k].smax != -LLINF) dat[k].smax += x;
        dat[k].min += x;
        if(dat[k].smin != LLINF) dat[k].smin += x;
        dat[k].sum += dat[k].len * x;
        if(lazy[k].first != LLINF) lazy[k].first += x;
        else lazy[k].second += x;
    }
    void update_add(int a, int b, ll x, int k, int l, int r) {
        if(b <= l || r <= a) return;
        if(a <= l && r <= b) {
            lazy[k] = update_add_put(k, x);
            return;
        }
        push(k);
        const int m = (l+r)>>1;
        update_add(a, b, x, 2*k+1, l, m);
        update_add(a, b, x, 2*k+2, m, r);
        dat[k] = merge(dat[2*k+1], dat[2*k+2]);
    }
    void update_add(int a, int b, ll x) { update_add(a, b, x, 0, 0, n); }

    void update_min_put(int k, ll x) {
        dat[k].sum += (x - dat[k].max) * dat[k].maxc;
        if(dat[k].max == dat[k].min) {
            dat[k].max = dat[k].min = x;
        } else if(dat[k].max == dat[k].smin) {
            dat[k].max = dat[k].smin = x;
        } else {
            dat[k].max = x;
        }
        if(lazy[k].first != LLINF && x < lazy[k].first) {
            lazy[k].first = x;
        }
    }
    void update_min(int a, int b, ll x, int k, int l, int r) {
        if(b <= l || r <= a || dat[k].max <= x) return;
        if(a <= l && r <= b && dat[k].smax < x) {
            update_min_put(k, x);
            return;
        }
        push(k);
        const int m = (l+r)>>1;
        update_min(a, b, x, 2*k+1, l, m);
        update_min(a, b, x, 2*k+2, m, r);
        dat[k] = merge(dat[2*k+1], dat[2*k+2]);
    }
    void update_min(int a, int b, ll x) { update_min(a, b, x, 0, 0, n); }

    void update_max_put(int k, ll x) {
        dat[k].sum += (x-dat[k].min) * dat[k].minc;
        if(dat[k].max == dat[k].min) {
            dat[k].max = dat[k].min = x;
        } else if(dat[k].smax == dat[k].min) {
            dat[k].smax = dat[k].min = x;
        } else {
            dat[k].min = x;
        }
        if(lazy[k].first != LLINF && x > lazy[k].first) {
            lazy[k].first = x;
        }
    }
    void update_max(int a, int b, ll x, int k, int l, int r) {
        if(b <= l || r <= a || dat[k].min >= x) return;
        if(a <= l && r <= b && dat[k].smin > x) {
            update_max_put(k, x);
            return;
        }
        push(k);
        const int m = (l+r)>>1;
        update_max(a, b, x, 2*k+1, l, m);
        update_max(a, b, x, 2*k+2, m, r);
        dat[k] = merge(dat[2*k+1], dat[2*k+2]);
    }
    void update_max(int a, int b, ll x) { update_max(a, b, x, 0, 0, n); }

    // デバッグ出力
    void debug() {
        cout << "---------------------" << endl;
        int cnt = 0;
        for(int i=1; i<=n; i*=2) {
        REP(j, i) {
            cout << "([" << dat[cnt].sum << "," << dat[cnt].max << "," << dat[cnt].smax << "," <<  dat[cnt].maxc << "]," << lazy[cnt] << ") ";
            cnt++;
        }
        cout << endl;
        }
        cout << "---------------------" << endl;
    }
};

struct node {
    ll max, smax, maxc, min, smin, minc, sum, len;
    node() : max(-LLINF), smax(-LLINF), maxc(0), min(LLINF), smin(LLINF), minc(0), sum(0), len(0) {}
    node(ll v) : max(v), smax(-LLINF), maxc(1), min(v), smin(LLINF), minc(1), sum(v), len(1) {}
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

