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
ostream &operator <<(ostream& out,const pair<S,T>& a){
    out<<'('<<a.first<<','<<a.second<<')'; return out;
}
template<class T>
ostream &operator <<(ostream& out,const vector<T>& a){
    out<<'['; for(T i: a) {out<<i<<',';} out<<']'; return out;
}

int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0}; // DRUL
const int INF = 1<<30;
const ll LLINF = 1LL<<60;
const ll MOD = 1000000007;

// BEGIN
template <typename T>
struct BIT {
    vector<T> bit;
    // 単位元
    const T neutral = 0;
    // 要素数
    int n;
    BIT(int n_ = 1e5) { init(n_); }
    void init(int sz) { 
        n=1; while(n < sz) n*=2;
        bit.assign(n+1, neutral); 
    }
    void update(int i, T w) {
        for(int x=i+1; x<bit.size(); x += x&-x) bit[x] += w;
    }
    // [0,i]
    T query(int i) {
        T ret = neutral;
        for(int x=i+1; x>0; x -= x&-x) ret += bit[x];
        return ret;
    }
    // 合計がw以上の最小の位置
    int lower_bound(T w) {
        int x = 0;
        for(int k=n; k>0; k>>=1) {
            if(x+k <= n && bit[x+k] < w) {
                w -= bit[x+k];
                x += k;
            }
        }
        return x;
    }
};
// END

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=jp
namespace aoj_dsl2b {
    void solve() {
        ll n, q;
        cin >> n >> q;
        BIT<ll> bit(100010);
        while(q--) {
            ll t, x, y;
            cin >> t >> x >> y;
            if(t == 0) {
                bit.update(x, y);
            } else {
                cout << bit.query(y) - bit.query(x-1) << endl;
            }
        }
    }
}

// https://atcoder.jp/contests/arc033/tasks/arc033_3
namespace arc033c {
    void solve() {
        ll q;
        cin >> q;
        BIT<ll> bit(200010);
        // lower_boundのverify用に+2とか変なことやってる
        while(q--) {
            ll t, x;
            cin >> t >> x;
            if(t == 1) {
                bit.update(x, 2);
            } else {
                ll val = bit.lower_bound(x*2-1);
                cout << val << endl;
                bit.update(val, -2);
            }
        }
    }
}

signed main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    // aoj_dsl2b::solve();
    arc033c::solve();

    return 0;
}