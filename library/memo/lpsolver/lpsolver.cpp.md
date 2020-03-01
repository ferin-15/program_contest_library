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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :warning: memo/lpsolver/lpsolver.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#afa89dc4856c832f73813c3922fede93">memo/lpsolver</a>
* <a href="{{ site.github.repository_url }}/blob/master/memo/lpsolver/lpsolver.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-03 21:48:44+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PII = pair<ll, ll>;
#define FOR(i, a, n) for (ll i = (ll)a; i < (ll)n; ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(x) x.begin(), x.end()
template<typename T> void chmin(T &a, const T &b) { a = min(a, b); }
template<typename T> void chmax(T &a, const T &b) { a = max(a, b); }
struct FastIO {FastIO() { cin.tie(0); ios::sync_with_stdio(0); }}fastiofastio;
#ifdef DEBUG_ 
#include "../program_contest_library/memo/dump.hpp"
#else
#define dump(...)
#endif
const ll INF = 1LL<<60;

using R = double;
const R EPS = 1e-8;
int sgn(const R &r) { return (r>EPS) - (r<-EPS); }
int sgn(const R &a, const R &b) { return sgn(a-b); }

template<typename T>
struct lpSolver {
    T simplex(vector<vector<T>> &t) {
        const int m = t.size()-1, n = t[0].size()-m-1;
        while(1) {
            dump("-----------------------");
            REP(i, t.size()) dump(t[i]);
            // y = t[m][0…n+m-1] を転置したやつ
            // idx1 を t[m][k]<0 となる最小の k とする
            int idx1 = -1;
            bool isopt = true;
            REP(i, n+m) if(sgn(t[m][i]) < 0) {
                isopt = false;
                if(idx1 == -1) idx1 = i;
                break;
            }
            // y >= 0 なら終了する 最適解
            if(isopt) return t[m][n+m];
            
            // Aw = y[0…m-1][idx1]
            // λ = min(y[i][n+m]/y[i][idx1] : 0<=j<m, y[i][idx1]>0)
            // j = argmin(y[i][n+m]/y[i][idx1] : 0<=j<m, y[i][idx1]>0)
            T l = INF;
            int idx2 = -1;
            bool isunbound = true;
            REP(i, m) if(sgn(t[i][idx1]) > 0) {
                isunbound = false;
                if(sgn(l, t[i][n+m] / t[i][idx1]) > 0) {
                    l = t[i][n+m] / t[i][idx1];
                    idx2 = i;
                }
            }
            // Aw <= 0 なら終了する 非有界
            if(isunbound) return INF; // maximize だしとりあえず INF 返す
            dump(idx1, idx2);

            // J = (J \ {idx1}) \cup {idx2} とするときの t を求める
            // 列idx1 が 行idx2以外で全て0になるように，行idx2 を定数倍して足す
            const T inv = 1.0 / t[idx2][idx1];
            REP(i, m+1) {
                if(i == idx2) continue;
                const T coff = t[i][idx1] * inv;
                REP(j, n+m+1) t[i][j] -= t[idx2][j] * coff;
            }
        }
    }
    T solve(vector<vector<T>> &a, vector<T> &b, vector<T> &c) {
        const int n = c.size(), m = b.size();
        vector<vector<T>> t(m+1, vector<T>(n+m+1));
        REP(i, m) REP(j, n) t[i][j] = a[i][j];
        REP(i, m) t[i][n+i] = 1, t[i][n+m] = b[i];
        REP(i, n) t[m][i] = -c[i];
        T ret = simplex(t);
        return ret;

        // T sum = 0;
        // vector<int> ord1, ord2;
        // REP(i, m) {
        //     if(sgn(b[i]) >= 0) ord1.push_back(i);
        //     else ord2.push_back(i), sum += b[i];
        // }
        // const int m1 = ord1.size(), m2 = ord2.size();
        // vector<vector<T>> t(m+1, vector<T>(n+m+m2+1));       
        // REP(i, m) t[i][n+m2+i] = 1;
        // REP(i, m1) {
        //     t[i][n+m1+2*m2] = b[ord1[i]];
        //     REP(j, n) t[i][j] = a[ord1[i]][j];
        // }
        // REP(i, m2) {
        //     t[m][n+i] = 1;
        //     t[m1+i][n+i] = -1;
        //     t[m1+i][n+m1+2*m2] = -b[ord2[i]];
        //     REP(j, n) {
        //         t[m][j] += a[ord2[i]][j];
        //         t[m1+i][j] = -a[ord2[i]][j];
        //     }
        // }
        // REP(i, t.size()) dump(t[i]);
        // dump("-----------------------");
        // T ret = simplex(t);
        // REP(i, t.size()) dump(t[i]);
        // dump(ret, sum);
        // dump("-----------------------");
        // // 実行不可能
        // if(sgn(ret, sum) != 0) return -1;    

        // vector<vector<T>> t2(m+1, vector<T>(n+m+1));
        // REP(i, m+1) REP(j, n+m) t2[i][j] = t[i][j];
        // REP(i, m+1) t2[i][n+m] = t[i][n+m1+2*m2];
        // REP(i, n) t2[m][i] = -c[i];
        // REP(i, t2.size()) dump(t2[i]);
        // dump("-----------------------");
        // ret = simplex(t2);
        // REP(i, t2.size()) dump(t2[i]);
        // dump(ret);
        // dump("-----------------------");
        // return ret;
    }
};

/*
8 5
94 49 53 10 35 0 0 0
-40 80 4 9 -91 0 0 0
50 -63 96 56 39 -1 0 0
-63 98 29 -53 19 0 -1 0
69 70 11 87 82 0 0 -1
10 52 32 94 1
56 105 136 90 140 -1 -1 -1
とかの n > m のケースで最適解を返してくれない

n <= m で x_i = 0 が初期解として使えるなら多分動く
*/

int main(void) {
    cerr << setprecision(8);

    ll n, m;
    cin >> n >> m;
    vector<vector<R>> a(m, vector<R>(n));
    vector<R> b(m), c(n);
    REP(i, m) REP(j, n) cin >> a[i][j];
    REP(i, m) cin >> b[i];
    REP(i, n) cin >> c[i];

    REP(i, m) dump(a[i], b[i]);
    dump(c);

    lpSolver<R> solver;
    cout << fixed << setprecision(9) << solver.solve(a, b, c) << endl;

    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 347, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=self.cpp_source_path)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 68, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 181, in update
    raise BundleError(path, i + 1, "unable to process #include in #if / #ifdef / #ifndef other than include guards")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: memo/lpsolver/lpsolver.cpp: line 12: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

