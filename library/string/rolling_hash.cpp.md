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


# :x: string/rolling_hash.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b45cffe084dd3d20d928bee85e7b0f21">string</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/rolling_hash.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00




## Verified with

* :x: <a href="../../verify/test/aoj2444.test.cpp.html">test/aoj2444.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
template<ll MOD, ll B>
struct rollingHash{
    vector<ll> hash,p;
    rollingHash(){}
    rollingHash(const string &s){
        const int n=s.size();
        hash.assign(n+1,0); p.assign(n+1,1);
        for(int i=0;i<n;i++){
            hash[i+1]=(hash[i]*B+s[i])%MOD;
            p[i+1]=p[i]*B%MOD;
        }
    }
    // [l,r)
    ll get(int l,int r){
        ll res=hash[r]+MOD-hash[l]*p[r-l]%MOD;
        return res>=MOD?res-MOD:res;
    }
};
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "string/rolling_hash.cpp"
// BEGIN CUT
template<ll MOD, ll B>
struct rollingHash{
    vector<ll> hash,p;
    rollingHash(){}
    rollingHash(const string &s){
        const int n=s.size();
        hash.assign(n+1,0); p.assign(n+1,1);
        for(int i=0;i<n;i++){
            hash[i+1]=(hash[i]*B+s[i])%MOD;
            p[i+1]=p[i]*B%MOD;
        }
    }
    // [l,r)
    ll get(int l,int r){
        ll res=hash[r]+MOD-hash[l]*p[r-l]%MOD;
        return res>=MOD?res-MOD:res;
    }
};
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

