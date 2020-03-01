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


# :warning: geometry/rational_modulo.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed7daeb157cd9b31e53896ad3c771a26">geometry</a>
* <a href="{{ site.github.repository_url }}/blob/master/geometry/rational_modulo.cpp">View this file on GitHub</a>
    - Last commit date: 2018-09-27 01:44:20+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// jag2018day2F で使った 
// 誤差がやばいときに有理数で幾何をやろう 
// 有理数がオーバーフローしないように剰余体で考えよう
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define int ll
using PII = pair<int, int>;
template <typename T> using V = vector<T>;
template <typename T> using VV = vector<V<T>>;
template <typename T> using VVV = vector<VV<T>>;

#define FOR(i, a, n) for (ll i = (ll)a; i < (ll)n; ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(x) x.begin(), x.end()
#define PB push_back

const ll INF = (1LL<<60);
const int MOD = 1000000007;

template <typename T> T &chmin(T &a, const T &b) { return a = min(a, b); }
template <typename T> T &chmax(T &a, const T &b) { return a = max(a, b); }
template <typename T> bool IN(T a, T b, T x) { return a<=x&&x<b; }
template<typename T> T ceil(T a, T b) { return a/b + !!(a%b); }
template<class S,class T>
ostream &operator <<(ostream& out,const pair<S,T>& a){
  out<<'('<<a.first<<','<<a.second<<')';
  return out;
}
template<class T>
ostream &operator <<(ostream& out,const vector<T>& a){
  out<<'[';
  REP(i, a.size()) {out<<a[i];if(i!=a.size()-1)out<<',';}
  out<<']';
  return out;
}

int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

int add(int a, int b) {
  a += b;
  if(a >= MOD) a -= MOD;
  return a;
}
int sub(int a, int b) { 
  a -= b;
  if(a < 0) a += MOD;
  return a;
}
int mul(int a, int b) {
  return a*b%MOD;
}
int pow(int x, int e) {
  int a = 1, p = x;
  while(e > 0) {
    if(e%2 == 0) {p = (p*p) % MOD; e /= 2;}
    else {a = (a*p) % MOD; e--;}
  }
  return a;
}
int inv(int x, int mo=MOD) {
  return pow(x, mo-2);
}

struct P {
  int x, y;
  P(int x_ = 0, int y_ = 0) : x(x_), y(y_) {
    if(x < 0) x = ((x%MOD)+MOD)%MOD;
    if(y < 0) y = ((y%MOD)+MOD)%MOD;
  }

  P operator+(const P a) const { return P(add(x,a.x), add(y,a.y)); }
  P operator-(const P a) const { return P(sub(x,a.x), sub(y,a.y)); }
  P operator*(const int a) const { return P(mul(x,a), mul(y,a)); }
  bool operator==(const P a) const { return x==a.x && y==a.y; }
};
using L = pair<P,P>;

int dot(const P& a, const P& b) {
  return add(mul(a.x, b.x), mul(a.y, b.y));
}
int det(const P& a, const P& b) {
  return sub(mul(a.x, b.y), mul(a.y, b.x));
}
P vec(const L& l) {return l.second - l.first;}
bool intersect(const L& l1, const L& l2) {
  return det(vec(l1),vec(l2)) != 0 || l1 == l2;
}
P crosspoint(const L& l1, const L& l2) {
  int ratio = mul(det(vec(l2), l2.first-l1.first), inv(det(vec(l2),vec(l1))));
  return l1.first + vec(l1)*ratio;
}

signed main(void)
{
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  cin >> n;
  vector<P> a(n), b(n), c(n);
  P d; 
  cin >> d.x >> d.y;
  REP(i, n) cin >> a[i].x >> a[i].y >> b[i].x >> b[i].y >> c[i].x >> c[i].y;

  REP(i, n) {
    L l1({a[i], b[i]}), l2({c[i], d});
    if(!intersect(l1, l2)) {
      cout << i << endl;
      return 0;
    }
    d = crosspoint(l1, l2);
  }
  cout << n << endl;

  return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "geometry/rational_modulo.cpp"
// jag2018day2F で使った 
// 誤差がやばいときに有理数で幾何をやろう 
// 有理数がオーバーフローしないように剰余体で考えよう
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define int ll
using PII = pair<int, int>;
template <typename T> using V = vector<T>;
template <typename T> using VV = vector<V<T>>;
template <typename T> using VVV = vector<VV<T>>;

#define FOR(i, a, n) for (ll i = (ll)a; i < (ll)n; ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(x) x.begin(), x.end()
#define PB push_back

const ll INF = (1LL<<60);
const int MOD = 1000000007;

template <typename T> T &chmin(T &a, const T &b) { return a = min(a, b); }
template <typename T> T &chmax(T &a, const T &b) { return a = max(a, b); }
template <typename T> bool IN(T a, T b, T x) { return a<=x&&x<b; }
template<typename T> T ceil(T a, T b) { return a/b + !!(a%b); }
template<class S,class T>
ostream &operator <<(ostream& out,const pair<S,T>& a){
  out<<'('<<a.first<<','<<a.second<<')';
  return out;
}
template<class T>
ostream &operator <<(ostream& out,const vector<T>& a){
  out<<'[';
  REP(i, a.size()) {out<<a[i];if(i!=a.size()-1)out<<',';}
  out<<']';
  return out;
}

int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

int add(int a, int b) {
  a += b;
  if(a >= MOD) a -= MOD;
  return a;
}
int sub(int a, int b) { 
  a -= b;
  if(a < 0) a += MOD;
  return a;
}
int mul(int a, int b) {
  return a*b%MOD;
}
int pow(int x, int e) {
  int a = 1, p = x;
  while(e > 0) {
    if(e%2 == 0) {p = (p*p) % MOD; e /= 2;}
    else {a = (a*p) % MOD; e--;}
  }
  return a;
}
int inv(int x, int mo=MOD) {
  return pow(x, mo-2);
}

struct P {
  int x, y;
  P(int x_ = 0, int y_ = 0) : x(x_), y(y_) {
    if(x < 0) x = ((x%MOD)+MOD)%MOD;
    if(y < 0) y = ((y%MOD)+MOD)%MOD;
  }

  P operator+(const P a) const { return P(add(x,a.x), add(y,a.y)); }
  P operator-(const P a) const { return P(sub(x,a.x), sub(y,a.y)); }
  P operator*(const int a) const { return P(mul(x,a), mul(y,a)); }
  bool operator==(const P a) const { return x==a.x && y==a.y; }
};
using L = pair<P,P>;

int dot(const P& a, const P& b) {
  return add(mul(a.x, b.x), mul(a.y, b.y));
}
int det(const P& a, const P& b) {
  return sub(mul(a.x, b.y), mul(a.y, b.x));
}
P vec(const L& l) {return l.second - l.first;}
bool intersect(const L& l1, const L& l2) {
  return det(vec(l1),vec(l2)) != 0 || l1 == l2;
}
P crosspoint(const L& l1, const L& l2) {
  int ratio = mul(det(vec(l2), l2.first-l1.first), inv(det(vec(l2),vec(l1))));
  return l1.first + vec(l1)*ratio;
}

signed main(void)
{
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n;
  cin >> n;
  vector<P> a(n), b(n), c(n);
  P d; 
  cin >> d.x >> d.y;
  REP(i, n) cin >> a[i].x >> a[i].y >> b[i].x >> b[i].y >> c[i].x >> c[i].y;

  REP(i, n) {
    L l1({a[i], b[i]}), l2({c[i], d});
    if(!intersect(l1, l2)) {
      cout << i << endl;
      return 0;
    }
    d = crosspoint(l1, l2);
  }
  cout << n << endl;

  return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

