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

// O(n*1.466^n) n<=40で16ms
struct maxIndependentSet {
    ll n;
    vector<vector<ll>> g;

    ll dfs(ll v, vector<ll>& used) {
        if(v == n) return 0;
        ll ret = 0;
        if(!used[v]) {
            vector<ll> nv(1, v);
            for(ll i: g[v]) if(!used[i]) nv.push_back(i);
            for(ll i: nv) used[i] = 1;
            chmax(ret, dfs(v+1, used) + 1);
            for(ll i: nv) used[i] = 0;
        }
        ll d = 0;
        for(ll i: g[v]) if(!used[i]) d++;
        if(d > 1 || used[v]) {
            if(!used[v]) {
                used[v] = 1;
                chmax(ret, dfs(v+1, used));
                used[v] = 0;
            } else {
                chmax(ret, dfs(v+1, used));
            }
        }
        return ret;
    }

    maxIndependentSet() {}
    maxIndependentSet(ll n) : n(n), g(n) {}

    void add_edge(ll a, ll b) {
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int get() {
        vector<ll> used(n);
        return dfs(0, used);
    }
};

namespace thanks2017G {
    void solve() {
        ll n, m;
        cin >> n >> m;
        maxIndependentSet graph(n);
        REP(i, m) {
            int a, b;
            cin >> a >> b;
            graph.add_edge(a-1, b-1);
        }
        cout << graph.get() << endl;
    }
}

signed main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    thanks2017G::solve();

    return 0;
}
