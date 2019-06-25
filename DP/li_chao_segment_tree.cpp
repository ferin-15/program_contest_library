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

// 単調性なしok 動的CHT 各操作O(logN)
template <typename T, const T id = numeric_limits<T>::min()>
class ConvexHullTrick {
private:
    struct line {
        T a, b;
        line(T a_ = 0, T b_ = 0) : a(a_), b(b_) {}
        T get(T x) { return a * x + b; }
    };
    struct node {
        line l;
        node *lch, *rch;
        node(line l_) : l(l_), lch(nullptr), rch(nullptr) {}
    };

    const T minx, maxx;
    node *root = nullptr;

    // [lb, ub]
    node* update(node *p, ll lb, ll ub, line& l) {
        if (!p) return new node(l);
        if (p->l.get(lb) >= l.get(lb) && p->l.get(ub) >= l.get(ub)) return p;
        if (p->l.get(lb) <= l.get(lb) && p->l.get(ub) <= l.get(ub)) {
          p->l = l;
          return p;
        }
        ll mid = (lb + ub) / 2;
        if (p->l.get(mid) < l.get(mid)) swap(p->l, l);
        if (p->l.get(lb) <= l.get(lb)) p->lch = update(p->lch, lb, mid, l);
        else p->rch = update(p->rch, mid + 1, ub, l);
        return p;
    }
    // [lb, ub]
    T query(node *p, ll lb, ll ub, ll t) const {
        if(!p) return id;
        if(ub == lb) return p->l.get(t);
        ll mid = (lb+ub)/2;
        if(t <= mid) return max(p->l.get(t), query(p->lch, lb, mid, t));
        return max(p->l.get(t), query(p->rch, mid + 1, ub, t));
    }
public:
    // getで呼び出しうるxの範囲を指定
    ConvexHullTrick(const T minx_, const T maxx_) : minx(minx_), maxx(maxx_) {}
    // 直線ax+bを追加 最小がほしければ-ax-bを渡してgetの結果に×(-1)する
    void insert(T a, T b) {
        line l(a, b);
        root = update(root, minx, maxx, l);
    }
    // ax+b のうち最大のものを返す
    T get(T x) const { return query(root, minx, maxx, x); }
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

            ConvexHullTrick<ll> cht(0, 1000010);
            REP(j, n) {
                cht.insert(-num[j], -dp[i-1][j]+num[j]*p[j]);
                dp[i][j] = -cht.get(p[j]);
            }
        }

        ll ret = LLINF;
        REP(i, d) chmin(ret, dp[i][n-1]);
        cout << ret << endl;
    }
}

// 定数倍がつらすぎてCHTにlogつけると通らねえ
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
            ConvexHullTrick<ll> cht(-1000000010, 1000000010);
            dp[i][0] = t[0] - T[0];
            cht.insert(0, -dp[i-1][0]-T[0]);
            FOR(j, 1, m) {
                dp[i][j] = -cht.get(t[j]) + t[j]*j - T[j];
                cht.insert(j, -dp[i-1][j]-T[j]);
            }
        }

        cout << dp[p-1][m-1] << endl;
    }
}

signed main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    aoj2580::solve();
    // cf185div1B::solve(); // これ定数倍削減して通すの無理

    return 0;
}
