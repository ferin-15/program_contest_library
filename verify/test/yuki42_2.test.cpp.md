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


# :heavy_check_mark: test/yuki42_2.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yuki42_2.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-08 16:27:33+09:00


* see: <a href="https://yukicoder.me/problems/no/42">https://yukicoder.me/problems/no/42</a>


## Depends on

* :heavy_check_mark: <a href="../../library/math/lagrange_interpolation.cpp.html">math/lagrange_interpolation.cpp</a>
* :question: <a href="../../library/math/modint.cpp.html">math/modint.cpp</a>
* :question: <a href="../../library/memo/macro.hpp.html">memo/macro.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://yukicoder.me/problems/no/42"
#include "../memo/macro.hpp"
#include "../math/modint.cpp"
using mint = modint<1000000009>;
#include "../math/lagrange_interpolation.cpp"

signed main(void) {
    vector<ll> c({1, 5, 10, 50, 100, 500});
    vector<mint> dp(3010, 1);
    FOR(i, 1, 6) FOR(j, c[i], 3010) dp[j] += dp[j-c[i]];

    ll t;
    cin >> t;
    while(t--) {
        ll M;
        cin >> M;

        if(M < 3010) {
            cout << dp[M] << endl;
            continue;
        }

        mint m = M/500;
        ll q = M % 500;
        vector<mint> x(6), y(6);
        REP(i, 6) {
            x[i] = i;
            y[i] = dp[i*500+q];
        }
        vector<mint> coff = lagrange_interpolation(x, y);
        mint ans = 0, pw = 1;
        REP(i, 6) {
            ans += coff[i] * pw;
            pw *= m;
        }
        cout << ans << endl;
    }

    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yuki42_2.test.cpp"
#define PROBLEM "https://yukicoder.me/problems/no/42"
#line 1 "memo/macro.hpp"
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
const ll INF = 1LL<<60;
#line 1 "math/modint.cpp"
// BEGIN CUT
template<int MOD>
struct modint {
    int x;
    modint(): x(0) {}
    modint(ll y) : x(y>=0 ? y%MOD : y%MOD+MOD) {}
    static constexpr ll mod() { return MOD; }
    // e乗
    modint pow(ll e) {
        ll a = 1, p = x;
        while(e > 0) {
            if(e%2 == 0) {p = (p*p) % MOD; e /= 2;}
            else {a = (a*p) % MOD; e--;}
        }
        return modint(a);
    }
    modint inv() const {
        ll a=x, b=MOD, u=1, y=1, v=0, z=0;
        while(a) {
            ll q = b/a;
            swap(z -= q*u, u);
            swap(y -= q*v, v);
            swap(b -= q*a, a);
        }
        return z;
    }
    // Comparators
    bool operator <(modint b) { return x < b.x; }
    bool operator >(modint b) { return x > b.x; }
    bool operator<=(modint b) { return x <= b.x; }
    bool operator>=(modint b) { return x >= b.x; }
    bool operator!=(modint b) { return x != b.x; }
    bool operator==(modint b) { return x == b.x; }
    // Basic Operations
    modint operator+(modint r) const { return modint(*this) += r; }
    modint operator-(modint r) const { return modint(*this) -= r; }
    modint operator*(modint r) const { return modint(*this) *= r; }
    modint operator/(modint r) const { return modint(*this) /= r; }
    modint &operator+=(modint r) {
        if((x += r.x) >= MOD) x -= MOD;
        return *this;
    }
    modint &operator-=(modint r) {
        if((x -= r.x) < 0) x += MOD;
        return *this;
    }
    modint &operator*=(modint r) {
    #if !defined(_WIN32) || defined(_WIN64)
        x = (ll)x * r.x % MOD; return *this;
    #endif
        unsigned long long y = (unsigned long long)x * r.x;
        unsigned xh = (unsigned) (y >> 32), xl = (unsigned) y, d, m;
        asm(
            "divl %4; \n\t"
            : "=a" (d), "=d" (m)
            : "d" (xh), "a" (xl), "r" (MOD)
        );
        x = m;
        return *this;
    }
    modint &operator/=(modint r) { return *this *= r.inv(); }
    // increment, decrement
    modint operator++() { x++; return *this; }
    modint operator++(signed) { modint t = *this; x++; return t; }
    modint operator--() { x--; return *this; }
    modint operator--(signed) { modint t = *this; x--; return t; }
    // 平方剰余のうち一つを返す なければ-1
    friend modint sqrt(modint a) {
        if(a == 0) return 0;
        ll q = MOD-1, s = 0;
        while((q&1)==0) q>>=1, s++;
        modint z=2;
        while(1) {
            if(z.pow((MOD-1)/2) == MOD-1) break;
            z++;
        }
        modint c = z.pow(q), r = a.pow((q+1)/2), t = a.pow(q);
        ll m = s;
        while(t.x>1) {
            modint tp=t;
            ll k=-1;
            FOR(i, 1, m) {
                tp *= tp;
                if(tp == 1) { k=i; break; }
            }
            if(k==-1) return -1;
            modint cp=c;
            REP(i, m-k-1) cp *= cp;
            c = cp*cp, t = c*t, r = cp*r, m = k;
        }
        return r.x;
    }

    template<class T>
    friend modint operator*(T l, modint r) { return modint(l) *= r; }
    template<class T>
    friend modint operator+(T l, modint r) { return modint(l) += r; }
    template<class T>
    friend modint operator-(T l, modint r) { return modint(l) -= r; }
    template<class T>
    friend modint operator/(T l, modint r) { return modint(l) /= r; }
    template<class T>
    friend bool operator==(T l, modint r) { return modint(l) == r; }
    template<class T>
    friend bool operator!=(T l, modint r) { return modint(l) != r; }
    // Input/Output
    friend ostream &operator<<(ostream& os, modint a) { return os << a.x; }
    friend istream &operator>>(istream& is, modint &a) { 
        is >> a.x;
        a.x = ((a.x%MOD)+MOD)%MOD;
        return is;
    }
    friend string to_frac(modint v) {
        static map<ll, PII> mp;
        if(mp.empty()) {
            mp[0] = mp[MOD] = {0, 1};
            FOR(i, 2, 1001) FOR(j, 1, i) if(__gcd(i, j) == 1) {
                mp[(modint(i) / j).x] = {i, j};
            }
        }
        auto itr = mp.lower_bound(v.x);
        if(itr != mp.begin() && v.x - prev(itr)->first < itr->first - v.x) --itr;
        string ret = to_string(itr->second.first + itr->second.second * ((int)v.x - itr->first));
        if(itr->second.second > 1) {
            ret += '/';
            ret += to_string(itr->second.second);
        }
        return ret;
    }
};
// END CUT
#line 4 "test/yuki42_2.test.cpp"
using mint = modint<1000000009>;
#line 1 "math/lagrange_interpolation.cpp"
// BEGIN CUT
// verify: https://atcoder.jp/contests/arc033/submissions/6839946
// x座標が相異なるn+1点(x_i,y_i)を通るn次以下の多項式f(T)の値を返す
// x_i = a + i*d 0<=i<=n (等差数列)
// 0割りを起こさないようにTが小さいときに注意
// O(nlog(MOD))
mint lagrange_interpolation_arithmetic(mint a, mint d, vector<mint> y, mint T) {
    const ll n = y.size() - 1;
    mint ret = 0, ft = 1;
    REP(i, n+1) ft *= T-(a+d*i);
    // f_0(x_0)
    mint f = 1;
    FOR(i, 1, n+1) f *= -1*i*d;
    ret += y[0] / f * ft / (T-a);
    // f_i(x_i) → f_{i+1}(x_{i+1})
    REP(i, n) {
        f *= d*(i+1) / (d*(i-n));
        ret += y[i+1] / f * ft / (T-a-d*(i+1));
    }
    return ret;
}

// verify: https://atcoder.jp/contests/arc033/submissions/6839930
// x座標が相異なるn+1点(x_i,y_i)を通るn次以下の多項式f(T)の値を返す
// O(n^2)
mint lagrange_interpolation(vector<mint> x, vector<mint> y, mint T) {
    const ll n = x.size() - 1;
    mint ret = 0;
    REP(i, n+1) {
        mint t = 1;
        REP(j, n+1) {
            if(i == j) continue;
            t *= T-x[j];
            t /= x[i]-x[j];
        }
        ret += t * y[i];
    }
    return ret;
}

// verify: https://atcoder.jp/contests/abc137/submissions/6839902
// x座標が相異なるn+1点(x_i,y_i)を通るn次以下の多項式f(x)を返す
// O(n^2) 定数倍がかなり重い
vector<mint> lagrange_interpolation(vector<mint> x, vector<mint> y) {
    const ll n = x.size() - 1;
    REP(i, n+1) {
        mint t = 1;
        REP(j, n+1) if(i != j) t *= x[i]-x[j];
        y[i] /= t;
    }
    ll cur = 0, nxt = 1;
    vector<vector<mint>> dp(2, vector<mint>(n+2));
    dp[0][0] = -1 * x[0], dp[0][1] = 1;
    FOR(i, 1, n+1) {
        REP(j, n+2) {
            dp[nxt][j] = dp[cur][j] * -1 * x[i];
            if(j >= 1) dp[nxt][j] += dp[cur][j-1];
        }
        swap(nxt, cur);
    }
    REP(i, n+1) x[i] = x[i].inv();
    vector<mint> ret(n+1);  // f(x)
    REP(i, n+1) {
        if(y[i]==0) continue;
        // 0割り対策の場合分け
        if(x[i] == 0) {
            REP(j, n+1) ret[j] += dp[cur][j+1] * y[i];
        } else {
            ret[0] -= dp[cur][0] * x[i] * y[i];
            mint pre = -1 * dp[cur][0] * x[i];
            FOR(j, 1, n+1) {
                ret[j] -= (dp[cur][j] - pre) * x[i] * y[i];
                pre = -1 * (dp[cur][j] - pre) * x[i];
            }
        }
    }
    return ret;
}
// END CUT
#line 6 "test/yuki42_2.test.cpp"

signed main(void) {
    vector<ll> c({1, 5, 10, 50, 100, 500});
    vector<mint> dp(3010, 1);
    FOR(i, 1, 6) FOR(j, c[i], 3010) dp[j] += dp[j-c[i]];

    ll t;
    cin >> t;
    while(t--) {
        ll M;
        cin >> M;

        if(M < 3010) {
            cout << dp[M] << endl;
            continue;
        }

        mint m = M/500;
        ll q = M % 500;
        vector<mint> x(6), y(6);
        REP(i, 6) {
            x[i] = i;
            y[i] = dp[i*500+q];
        }
        vector<mint> coff = lagrange_interpolation(x, y);
        mint ans = 0, pw = 1;
        REP(i, 6) {
            ans += coff[i] * pw;
            pw *= m;
        }
        cout << ans << endl;
    }

    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

