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

struct dinic {
    struct edge{
        int to;
        ll cap;
        int rev;
        bool isrev;
    };

    vector<vector<edge>> G;
    vector<int> level, iter;

    void bfs(int s) {
        level.assign(G.size(), -1);
        queue<int> que;
        level[s] = 0;
        que.push(s);
        while(que.size()) {
            int v = que.front(); que.pop();
            for(auto i: G[v]) {
                if(i.cap > 0 && level[i.to] < 0) {
                    level[i.to] = level[v] + 1;
                    que.push(i.to);
                }
            }
        }
    }

    ll dfs(int v, const int t, ll f) {
        if(v == t) return f;
        for(int &i = iter[v]; i<G[v].size(); ++i) {
            edge &e = G[v][i];
            if(e.cap > 0 && level[v] < level[e.to]) {
                ll d = dfs(e.to, t, min(f, e.cap));
                if(d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    dinic() {}
    dinic(int n) : G(n), level(n), iter(n) {}

    void add_edge(int from, int to, ll cap) {
        G[from].push_back({to, cap, (int)G[to].size(), false});
        G[to].push_back({from, 0, (int)G[from].size()-1, true});
    }

    ll max_flow(int s, int t) {
        ll flow = 0;
        while(1) {
            bfs(s);
            if(level[t] < 0) return flow;
            iter.assign(G.size(), 0);
            ll f;
            while((f = dfs(s, t, INF)) > 0) flow += f;
        }
    }

    friend ostream &operator <<(ostream& out, const dinic& a){
        out << "-----" << endl;
        for(int i = 0; i < (int)a.G.size(); i++) {
            for(auto &e : a.G[i]) {
                if(e.isrev) continue;
                auto &rev_e = a.G[e.to][e.rev];
                out << i << "->" << e.to << " (flow: " << rev_e.cap << "/" << e.cap + rev_e.cap << ")" << endl;
            }
        }
        out << "-----" << endl;
        return out;
    }
};