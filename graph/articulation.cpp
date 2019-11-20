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

class articulation {
private:
    void dfs(ll v, ll p, ll &k, vector<ll> &ret) {
        ord[v] = k++;
        low[v] = ord[v];
        ll cnt = 0;
        bool is_articulation = false;
        for(auto to: g[v]) {
            if(ord[to]==-1) {
                dfs(to, v, k, ret);
                chmin(low[v], low[to]);
                ++cnt;
                is_articulation |= p!=-1 && low[to] >= ord[v]; 
            } else if(to != p) {
                chmin(low[v], ord[to]);
            }
        }
        is_articulation |= p==-1 && cnt>1;
        if(is_articulation) ret.push_back(v);
    }
public:
    vector<vector<ll>> g;
    vector<ll> ord, low, cmp;

    articulation() {}
    articulation(ll n) : g(n), ord(n, -1), low(n) {}

    void add_edge(ll u, ll v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<ll> build() {
        ll k = 0;
        vector<ll> ret;
        REP(i, g.size()) if(ord[i]==-1) dfs(i, -1, k, ret);
        return ret;
    }
};

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A&lang=jp
namespace GRL3A {
    void solve() {
        ll n, m;
        cin >> n >> m;
        articulation graph(n);
        REP(i, m) {
            ll a, b;
            cin >> a >> b;
            graph.add_edge(a, b);
        }
        auto ret = graph.build();
        sort(ALL(ret));
        for(auto i: ret) cout << i << endl;
    }
}