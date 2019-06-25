#include <bits/stdc++.h>

using namespace std;
using ll = long long;
// #define int ll
using PII = pair<ll, ll>;

#define FOR(i, a, n) for (ll i = (ll)a; i < (ll)n; ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(x) x.begin(), x.end()

template<typename T> T &chmin(T &a, const T &b) { return a = min(a, b); }
template<typename T> T &chmax(T &a, const T &b) { return a = max(a, b); }
template<typename T> bool IN(T a, T b, T x) { return a<=x&&x<b; }
template<typename T> T ceil(T a, T b) { return a/b + !!(a%b); }

template<typename T> vector<T> make_v(size_t a) { return vector<T>(a); }
template<typename T,typename... Ts>
auto make_v(size_t a,Ts... ts) {
    return vector<decltype(make_v<T>(ts...))>(a,make_v<T>(ts...));
}
template<typename T,typename V> typename enable_if<is_class<T>::value==0>::type
fill_v(T &t, const V &v) { t=v; }
template<typename T,typename V> typename enable_if<is_class<T>::value!=0>::type
fill_v(T &t, const V &v ) { for(auto &e:t) fill_v(e,v); }

template<class S,class T>
ostream &operator <<(ostream& out,const pair<S,T>& a) {
    out<<'('<<a.first<<','<<a.second<<')'; return out;
}
template<class T>
ostream &operator <<(ostream& out,const vector<T>& a){
    out<<'[';
    for(const T &i: a) out<<i<<',';
    out<<']';
    return out;
}
template<class T>
ostream &operator <<(ostream& out, const set<T>& a) {
    out<<'{';
    for(const T &i: a) out<<i<<',';
    out<<'}';
    return out;
}
template<class T, class S>
ostream &operator <<(ostream& out, const map<T,S>& a) {
    out<<'{';
    for(auto &i: a) out<<i<<',';
    out<<'}';
    return out;
}

int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0}; // DRUL
const int INF = 1<<30;
const ll LLINF = 1LL<<60;
const ll MOD = 1000000007;

// 最小を求めてるので最大ならinsert(-a,-b), -get(x)
struct ConvexHullTrick {
    deque<PII> que;

    bool isright(const PII &p1, const PII &p2, int x) {
        return (p1.second-p2.second) >= x * (p2.first-p1.first);
    }
    bool check(const PII &a, const PII &b, const PII &c) {
        return (b.first-a.first)*(c.second-b.second)>=(b.second-a.second)*(c.first-b.first);
    }
    ll f(const PII &p, ll x) { return p.first * x + p.second; }

    // ax + b を追加
    void insert(ll a, ll b) {
        PII p(a, b);
        while(que.size() >= 2 && check(que[que.size()-2], que.back(), p)) {
            que.pop_back();
        }
        que.push_back(p);
    }
    // 単調性がある xの位置での最小のy
    ll incl_query(ll x) {
        assert(que.size());
        while(que.size() >= 2 && f(que[0],x) >= f(que[1],x)) {
            que.pop_front();
        }
        return que[0].first * x + que[0].second;
    }
    // 単調性なし
    ll query(ll x) {
        ll lb = -1, ub = (ll)que.size()-1;
        while(ub-lb > 1) {
            ll mid = (lb+ub)/2;
            if(isright(que[mid], que[mid+1], x)) lb = mid;
            else ub = mid;
        }
        return f(que[ub], x);
    }
};

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2580
namespace aoj2580 {
    ll dp[105][10010];
    void solve() {
        ll n, m, d, x;
        cin >> n >> m >> d >> x;
        vector<ll> p(n), a(m), b(m);
        REP(i, n) cin >> p[i];
        REP(i, m) cin >> a[i] >> b[i];

        REP(i, d) REP(j, n) dp[i][j] = LLINF;

        {
            ll num = 0;
            REP(j, m) {
                ll pos;
                if(b[j] >= 0) {
                    pos = a[j]-b[j];
                } else {
                    pos = a[j]+b[j];
                }
                if(pos >= p[0]) num++;
                a[j] += x;
            }
            REP(i, n) dp[0][i] = num * (p[i] - p[0]);
        }

        FOR(i, 1, d) {
            vector<ll> num(n);
            REP(j, m) {
                ll pos;
                if(b[j] >= 0) {
                    pos = a[j]-b[j];
                } else {
                    pos = a[j]+b[j];
                }
                ll tmp = upper_bound(ALL(p), pos) - p.begin() - 1;
                if(tmp >= 0) num[tmp]++;
                a[j] += x;
            }
            for(ll j=n-2; j>=0; --j) num[j] += num[j+1];

            ConvexHullTrick cht;
            REP(j, n) {
                cht.insert(num[j], dp[i-1][j]-num[j]*p[j]);
                dp[i][j] = cht.query(p[j]);
            }
        }

        ll ret = LLINF;
        REP(i, d) chmin(ret, dp[i][n-1]);
        cout << ret << endl;
    }
}

// https://codeforces.com/contest/311/problem/B
namespace cf185div1B {
    ll d[100010], t[100010], T[100010], dp[105][100010];
    void solve() {
        ll n, m, p;
        cin >> n >> m >> p;
        REP(i, n-1) cin >> d[i+1];
        REP(i, n-1) d[i+1] += d[i];
        REP(i, m) {
            ll a, b;
            cin >> a >> b;
            t[i] = (b-d[a-1]);
        }
        sort(t, t+m);
        T[0] = t[0];
        REP(i, m-1) T[i+1] += T[i] + t[i+1];

        REP(i, m) dp[0][i] = (i+1)*t[i] - T[i];
        FOR(i, 1, p) {
            ConvexHullTrick cht;
            dp[i][0] = t[0] - T[0];
            cht.insert(0, dp[i-1][0] + T[0]);
            FOR(j, 1, m) {
                dp[i][j] = cht.incl_query(t[j]) + t[j]*j - T[j];
                cht.insert(-j, dp[i-1][j] + T[j]);
            }
        }

        cout << dp[p-1][m-1] << endl;
    }
}

signed main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    // aoj2580::solve();
    cf185div1B::solve();

    return 0;
}
