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

// i番目の高さがh[i]のヒストグラム中で最大の長方形の面積
ll largest_rectangle_histogram(vector<ll> h) {
    const ll n = h.size();

    // iを固定して高さがh[i]となる長方形を考えるとl,rは一意に定まる
    // l[i], r[i] をstackを使って求める

    // l[i] = (j<=iかつh[j-1]<h[i]となる最大のj)
    vector<ll> l(n);
    stack<ll> st1;
    REP(i, n) {
        while(st1.size() && h[st1.top()] >= h[i]) st1.pop();
        l[i] = st1.empty() ? 0 : (st1.top()+1);
        st1.push(i);
    }
    // r[i] = (j>iかつh[j]<h[i]となる最小のj)
    vector<ll> r(n);
    stack<ll> st2;
    for(ll i=n-1; i>=0; --i) {
        while(st2.size() && h[st2.top()] >= h[i]) st2.pop();
        r[i] = st2.empty() ? n : st2.top();
        st2.push(i);
    }
    ll ret = 0;
    REP(i, n) ret = max(ret, h[i]*(r[i]-l[i]));
    return ret;
}

// c[i][j] = 0 のマスだけを使って構成できる最大の長方形の面積を返す
ll largeest_rectangle(vector<vector<ll>> c) {
    const int h = c.size(), w = c[0].size();
    vector<vector<ll>> con(h, vector<ll>(w));

    REP(i, w) {
        int cnt = 1;
        REP(j, h) {
            if(!c[j][i]) {
                con[j][i] = cnt;
                cnt++;
            } else {
                con[j][i] = 0;
                cnt = 1;
            }
        }
    }

    ll ret = 0;
    REP(i, h) chmax(ret, largest_rectangle_histogram(con[i]));
    return ret;
}

namespace DPL3C {
    void solve() {
        ll n;
        cin >> n;
        vector<ll> h(n);
        REP(i, n) cin >> h[i];

        cout << largest_rectangle_histogram(h) << endl;
    }
}

namespace DPL3B {
    void solve() {
        ll h, w;
        cin >> h >> w;
        vector<vector<ll>> c(h, vector<ll>(w));
        REP(i, h) REP(j, w) cin >> c[i][j];

        cout << largeest_rectangle(c) << endl;
    }
}

signed main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    // DPL3C::solve();
    DPL3B::solve();

    return 0;
}
