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

struct primal_dual {
    struct edge {
        int to;
        ll cap, cost;
        int rev;
        bool isrev;
    };

    int n;
    vector<vector<edge>> g;
    vector<ll> h, dist, prevv, preve;

    primal_dual(int n=300) : n(n), g(n) {}

    void add_edge(int from, int to, ll cap, ll cost) {
        g[from].push_back({to, cap, cost, (int)g[to].size(), true});
        g[to].push_back({from, 0, -cost, (int)g[from].size()-1, false});
    }

    // 与えられるグラフそもそもに負辺がある場合
    // sからtへの流量fの最小費用流
    // 流せないなら-1
    ll min_cost_flow(int s, int t, ll f) {
        ll res = 0;
        priority_queue<PII, vector<PII>, greater<PII>> que;
        h.assign(n, 0);
        preve.assign(n, -1);
        prevv.assign(n, -1);

        while(f > 0) {
            dist.assign(n, LLINF);
            dist[s] = 0;
            que.push({0, s});
            while(que.size()) {
                PII p = que.top(); que.pop();
                int v = p.second;
                if(dist[v] < p.first) continue;
                REP(i, g[v].size()) {
                    edge &e = g[v][i];
                    if(e.cap>0 && dist[e.to]>dist[v]+e.cost+h[v]-h[e.to]) {
                        dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        que.push({dist[e.to], e.to});
                    }
                }
            }
            if(dist[t] == LLINF) return -1;
            REP(v, n) h[v] += dist[v];
            ll d = f;
            for(int v = t; v != s; v = prevv[v]) {
                chmin(d, g[prevv[v]][preve[v]].cap);
            }
            f -= d; res += d * h[t];
            for(int v = t; v != s; v = prevv[v]) {
                edge &e = g[prevv[v]][preve[v]];
                e.cap -= d;
                g[v][e.rev].cap += d;
            }
        }
        return res;
    }
};

namespace GRL6B {
    void solve() {
        ll n, m, f;
        cin >> n >> m >> f;
        primal_dual mcf(n);
        REP(i, m) {
            ll u, v, c, d;
            cin >> u >> v >> c >> d;
            mcf.add_edge(u, v, c, d);
        }
        cout << mcf.min_cost_flow(0, n-1, f) << endl;
    }
}

signed main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    GRL6B::solve();

    return 0;
}
