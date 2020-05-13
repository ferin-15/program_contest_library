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


# :warning: string/rolling_hash.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b45cffe084dd3d20d928bee85e7b0f21">string</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/rolling_hash.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-13 12:24:02+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
class rollingHash {
private:
    static constexpr ll mod = (1LL<<61) - 1;
    static ll base;
    vector<ll> hash, p;

    ll mul(ll a, ll b) {
        ll au = a>>31, ad = a & ((1LL<<31)-1);
        ll bu = b>>31, bd = b & ((1LL<<31)-1);
        ll mid = ad*bu+au*bd, midu = mid>>30, midd = mid & ((1LL<<30)-1);
        return au*bu*2 + midu + (midd<<31) + ad*bd;
    }
    ll calcmod(ll x) {
        ll ret = (x>>61) + (x & mod);
        if(ret >= mod) ret -= mod;
        return ret;
    }

public:
    rollingHash(const string &s) : hash(s.size()+1), p(s.size()+1, 1) {
        if(base == -1) base = rnd(2, 100000);
        REP(i, s.size()) {
            hash[i+1] = calcmod(mul(hash[i], base)+s[i]);
            p[i+1] = calcmod(mul(p[i], base));
        }
    }
    // [l,r)
    ll get(int l,int r) {
        return calcmod(hash[r] + 3*mod - mul(hash[l], p[r-l]));
    }
    ll concat(ll h1, ll h2, ll h2len) {
        return calcmod(mul(h1, p[h2len]) + h2);
    }
};
ll rollingHash::base = -1;
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "string/rolling_hash.cpp"
// BEGIN CUT
class rollingHash {
private:
    static constexpr ll mod = (1LL<<61) - 1;
    static ll base;
    vector<ll> hash, p;

    ll mul(ll a, ll b) {
        ll au = a>>31, ad = a & ((1LL<<31)-1);
        ll bu = b>>31, bd = b & ((1LL<<31)-1);
        ll mid = ad*bu+au*bd, midu = mid>>30, midd = mid & ((1LL<<30)-1);
        return au*bu*2 + midu + (midd<<31) + ad*bd;
    }
    ll calcmod(ll x) {
        ll ret = (x>>61) + (x & mod);
        if(ret >= mod) ret -= mod;
        return ret;
    }

public:
    rollingHash(const string &s) : hash(s.size()+1), p(s.size()+1, 1) {
        if(base == -1) base = rnd(2, 100000);
        REP(i, s.size()) {
            hash[i+1] = calcmod(mul(hash[i], base)+s[i]);
            p[i+1] = calcmod(mul(p[i], base));
        }
    }
    // [l,r)
    ll get(int l,int r) {
        return calcmod(hash[r] + 3*mod - mul(hash[l], p[r-l]));
    }
    ll concat(ll h1, ll h2, ll h2len) {
        return calcmod(mul(h1, p[h2len]) + h2);
    }
};
ll rollingHash::base = -1;
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

