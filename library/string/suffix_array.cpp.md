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


# :warning: string/suffix_array.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b45cffe084dd3d20d928bee85e7b0f21">string</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/suffix_array.cpp">View this file on GitHub</a>
    - Last commit date: 2018-09-27 01:44:20+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct SuffixArray {
  VI SA, rank, tmp;
  string s;
  int n;

  SuffixArray() {}
  SuffixArray(const string& str) { build(str); }

  void build(const string& str) {
    s = str, n = s.size();
    SA.resize(n+1); rank.resize(n+1); tmp.resize(n+1);
    REP(i, n+1) {
      SA[i] = i;
      rank[i] = s[i];
    }
    for(int k=1; k<=n; k*=2) {
      auto comp = [&](int i, int j) -> bool {
        if(rank[i] != rank[j]) return rank[i] < rank[j];
        else {
          int ri = i+k<=n ? rank[i+k] : -1;
          int rj = j+k<=n ? rank[j+k] : -1;
          return ri < rj;
        }
      };
      sort(ALL(SA), comp);

      tmp[SA[0]] = 0;
      FOR(i, 1, n+1) tmp[SA[i]] = tmp[SA[i-1]] + (comp(SA[i-1], SA[i]) ? 1 : 0);
      rank = tmp;
    }
  }

  int operator[](int k) const { return (SA[k]); }
  int size() const { return (SA.size()); }

  void debug() {
    for(int i = 0; i < size(); i++) {
      cout << i << ": " << s.substr(SA[i]) << endl;
    }
  }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "string/suffix_array.cpp"
struct SuffixArray {
  VI SA, rank, tmp;
  string s;
  int n;

  SuffixArray() {}
  SuffixArray(const string& str) { build(str); }

  void build(const string& str) {
    s = str, n = s.size();
    SA.resize(n+1); rank.resize(n+1); tmp.resize(n+1);
    REP(i, n+1) {
      SA[i] = i;
      rank[i] = s[i];
    }
    for(int k=1; k<=n; k*=2) {
      auto comp = [&](int i, int j) -> bool {
        if(rank[i] != rank[j]) return rank[i] < rank[j];
        else {
          int ri = i+k<=n ? rank[i+k] : -1;
          int rj = j+k<=n ? rank[j+k] : -1;
          return ri < rj;
        }
      };
      sort(ALL(SA), comp);

      tmp[SA[0]] = 0;
      FOR(i, 1, n+1) tmp[SA[i]] = tmp[SA[i-1]] + (comp(SA[i-1], SA[i]) ? 1 : 0);
      rank = tmp;
    }
  }

  int operator[](int k) const { return (SA[k]); }
  int size() const { return (SA.size()); }

  void debug() {
    for(int i = 0; i < size(); i++) {
      cout << i << ": " << s.substr(SA[i]) << endl;
    }
  }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

