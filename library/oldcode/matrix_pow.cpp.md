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


# :warning: oldcode/matrix_pow.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#bf50ccff88ac9b2562bee63cf804278c">oldcode</a>
* <a href="{{ site.github.repository_url }}/blob/master/oldcode/matrix_pow.cpp">View this file on GitHub</a>
    - Last commit date: 2019-10-03 22:20:29+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
using vec = vector<ll>;
using mat = vector<vec>;

// A*Bを計算
mat mul(mat &A, mat &B) {
  mat C(A.size(), vec(B[0].size()));
  for(int i=0; i<(int)A.size(); ++i) {
    for(int k=0; k<(int)B.size(); ++k) {
      for(int j=0; j<(int)B[0].size(); ++j) {
        C[i][j] = (C[i][j] + A[i][k]*B[k][j]) % MOD;
      }
    }
  }
  return C;
}

// A*Bを計算
vec mul(mat &A, vec &B) {
  vec C(A.size());
  for(int i=0; i<(int)A.size(); ++i) {
    for(int j=0; j<(int)B.size(); ++j) {
      C[i] = (C[i] + A[i][j]*B[j]) % MOD;
    }
  }
  return C;
}

// A^nを計算 m*m行列のn乗はO(m^3logn)
mat pow(mat A, ll n) {
  mat B(A.size(), vec(A.size()));
  for(int i=0; i<(int)A.size(); ++i) B[i][i] = 1;
  while(n > 0) {
    if(n & 1) B = mul(B, A);
    A = mul(A, A);
    n >>= 1;
  }
  return B;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "oldcode/matrix_pow.cpp"
using vec = vector<ll>;
using mat = vector<vec>;

// A*Bを計算
mat mul(mat &A, mat &B) {
  mat C(A.size(), vec(B[0].size()));
  for(int i=0; i<(int)A.size(); ++i) {
    for(int k=0; k<(int)B.size(); ++k) {
      for(int j=0; j<(int)B[0].size(); ++j) {
        C[i][j] = (C[i][j] + A[i][k]*B[k][j]) % MOD;
      }
    }
  }
  return C;
}

// A*Bを計算
vec mul(mat &A, vec &B) {
  vec C(A.size());
  for(int i=0; i<(int)A.size(); ++i) {
    for(int j=0; j<(int)B.size(); ++j) {
      C[i] = (C[i] + A[i][j]*B[j]) % MOD;
    }
  }
  return C;
}

// A^nを計算 m*m行列のn乗はO(m^3logn)
mat pow(mat A, ll n) {
  mat B(A.size(), vec(A.size()));
  for(int i=0; i<(int)A.size(); ++i) B[i][i] = 1;
  while(n > 0) {
    if(n & 1) B = mul(B, A);
    A = mul(A, A);
    n >>= 1;
  }
  return B;
}
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

