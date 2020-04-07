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


# :heavy_check_mark: string/z_algorithm.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b45cffe084dd3d20d928bee85e7b0f21">string</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/z_algorithm.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 12:39:31+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/yuki599.test.cpp.html">test/yuki599.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// BEGIN CUT
// 「SとS[i:|S|-1]の最長共通接頭辞の長さ」を記録した配列AをO(|S|)で構築する
// aaabaaaab
// 921034210
vector<ll> Zalgo(string s) {
    vector<ll> v(s.size());
    v[0] = s.size();
    int i = 1, j = 0;
    while (i < s.size()) {
        while (i+j < s.size() && s[j] == s[i+j]) ++j;
        v[i] = j;
        if (j == 0) { ++i; continue;}
        int k = 1;
        while (i+k < s.size() && k+v[k] < j) v[i+k] = v[k], ++k;
        i += k; j -= k;
    }
	return v;
}
// END CUT
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "string/z_algorithm.cpp"
// BEGIN CUT
// 「SとS[i:|S|-1]の最長共通接頭辞の長さ」を記録した配列AをO(|S|)で構築する
// aaabaaaab
// 921034210
vector<ll> Zalgo(string s) {
    vector<ll> v(s.size());
    v[0] = s.size();
    int i = 1, j = 0;
    while (i < s.size()) {
        while (i+j < s.size() && s[j] == s[i+j]) ++j;
        v[i] = j;
        if (j == 0) { ++i; continue;}
        int k = 1;
        while (i+k < s.size() && k+v[k] < j) v[i+k] = v[k], ++k;
        i += k; j -= k;
    }
	return v;
}
// END CUT

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

