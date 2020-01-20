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


# :warning: DP/divide_and_conquer.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e2fca8135c2fadca093abd79a6b1c0d2">DP</a>
* <a href="{{ site.github.repository_url }}/blob/master/DP/divide_and_conquer.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 04:35:05+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// O(hwlogw)
// dp[i][j] = min_{0<=k<j} (dp[i-1][k]+f(k,j))
template<typename T, typename Compare = less<T>>
vector<vector<T>> divide_and_conquer(ll h, ll w, const function<T(ll,ll)> &f, const Compare &comp = Compare()) {
    const T inf = numeric_limits<T>::max() / 10;
    vector<vector<T>> dp(h, vector<T>(w, inf));
    function<void(ll,ll,ll,ll,ll)>
    dfs = [&](ll i, ll l, ll r, ll optl, ll optr) {
        if(l > r) return;
        ll mid = (l+r)/2, optm = -1;
        FOR(j, optl, min(mid, optr)+1) {
            T cost = dp[i][j] + f(j+1, mid);
            if(comp(cost, dp[i+1][mid])) {
                dp[i+1][mid] = cost;
                optm = j;
            }
        }
        dfs(i, l, mid-1, optl, optm);
        dfs(i, mid+1, r, optm, optr);
    };
    REP(i, w) dp[0][i] = f(0, i);
    FOR(i, 1, h) REP(j, w) dp[i][j] = inf;
    REP(i, h-1) dfs(i, 0, w-1, 0, w-1);
    return dp;
}

namespace cf190div1E {
    int u[4010][4010], W[4010][4010];
    void solve() {
        int n, k;
        scanf("%d %d ", &n, &k);
        REP(i, n) {
            REP(j, n) {
                u[i][j] = getchar() - '0';
                getchar();
            }
        }

        FOR(w, 1, n+1) {
            for(int l=0, r=l+w; r<n; ++l, ++r) {
                W[l][r] = u[l][r];
                if(w >= 2) W[l][r] += W[l+1][r] + W[l][r-1] - W[l+1][r-1];
            }
        }
        auto f = [&](ll i, ll j) { return W[i][j]; };

        auto dp = divide_and_conquer<ll>(k, n, f);
        cout << dp[k-1][n-1] << endl;
    }
}

namespace cf438F {
    void solve() {
        cin.tie(0);
        ios::sync_with_stdio(false);

        ll N, K;
        cin >> N >> K;
        vector<ll> A(N);
        REP(i, N) {
            cin >> A[i];
            --A[i];
        }

        ll L = 0, R = 0, sum = 0;
        vector<ll> appear(100010);
        appear[A[0]]++;
        auto add = [&](ll idx) { sum += appear[A[idx]]++; };
        auto del = [&](ll idx) { sum -= --appear[A[idx]]; };
        function<ll(ll,ll)> f = [&](ll l, ll r) {
            while(L > l) add(--L);
            while(L < l) del(L++);
            while(R < r) add(++R);
            while(R > r) del(R--);
            return sum;
        };
        auto dp = divide_and_conquer(K, N, f);
        cout << dp[K-1][N-1] << endl;
    }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "DP/divide_and_conquer.cpp"
// O(hwlogw)
// dp[i][j] = min_{0<=k<j} (dp[i-1][k]+f(k,j))
template<typename T, typename Compare = less<T>>
vector<vector<T>> divide_and_conquer(ll h, ll w, const function<T(ll,ll)> &f, const Compare &comp = Compare()) {
    const T inf = numeric_limits<T>::max() / 10;
    vector<vector<T>> dp(h, vector<T>(w, inf));
    function<void(ll,ll,ll,ll,ll)>
    dfs = [&](ll i, ll l, ll r, ll optl, ll optr) {
        if(l > r) return;
        ll mid = (l+r)/2, optm = -1;
        FOR(j, optl, min(mid, optr)+1) {
            T cost = dp[i][j] + f(j+1, mid);
            if(comp(cost, dp[i+1][mid])) {
                dp[i+1][mid] = cost;
                optm = j;
            }
        }
        dfs(i, l, mid-1, optl, optm);
        dfs(i, mid+1, r, optm, optr);
    };
    REP(i, w) dp[0][i] = f(0, i);
    FOR(i, 1, h) REP(j, w) dp[i][j] = inf;
    REP(i, h-1) dfs(i, 0, w-1, 0, w-1);
    return dp;
}

namespace cf190div1E {
    int u[4010][4010], W[4010][4010];
    void solve() {
        int n, k;
        scanf("%d %d ", &n, &k);
        REP(i, n) {
            REP(j, n) {
                u[i][j] = getchar() - '0';
                getchar();
            }
        }

        FOR(w, 1, n+1) {
            for(int l=0, r=l+w; r<n; ++l, ++r) {
                W[l][r] = u[l][r];
                if(w >= 2) W[l][r] += W[l+1][r] + W[l][r-1] - W[l+1][r-1];
            }
        }
        auto f = [&](ll i, ll j) { return W[i][j]; };

        auto dp = divide_and_conquer<ll>(k, n, f);
        cout << dp[k-1][n-1] << endl;
    }
}

namespace cf438F {
    void solve() {
        cin.tie(0);
        ios::sync_with_stdio(false);

        ll N, K;
        cin >> N >> K;
        vector<ll> A(N);
        REP(i, N) {
            cin >> A[i];
            --A[i];
        }

        ll L = 0, R = 0, sum = 0;
        vector<ll> appear(100010);
        appear[A[0]]++;
        auto add = [&](ll idx) { sum += appear[A[idx]]++; };
        auto del = [&](ll idx) { sum -= --appear[A[idx]]; };
        function<ll(ll,ll)> f = [&](ll l, ll r) {
            while(L > l) add(--L);
            while(L < l) del(L++);
            while(R < r) add(++R);
            while(R > r) del(R--);
            return sum;
        };
        auto dp = divide_and_conquer(K, N, f);
        cout << dp[K-1][N-1] << endl;
    }
}
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

