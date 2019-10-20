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

template<class T>
struct dinic {
    struct edge{
        int to;
        T cap;
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

    T dfs(int v, const int t, T f) {
        if(v == t) return f;
        for(int &i = iter[v]; i<(ll)G[v].size(); ++i) {
            edge &e = G[v][i];
            if(e.cap > 0 && level[v] < level[e.to]) {
                T d = dfs(e.to, t, min(f, e.cap));
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

    void add_edge(int from, int to, T cap) {
        G[from].push_back({to, cap, (int)G[to].size(), false});
        G[to].push_back({from, 0, (int)G[from].size()-1, true});
    }

    // sからtへ流量fを流す
    T maxflow(int s, int t, T f = 1LL<<30) {
        T flow = 0;
        while(1) {
            bfs(s);
            if(level[t] < 0) return flow;
            iter.assign(G.size(), 0);
            T tmp;
            while((tmp = dfs(s, t, f)) > 0) flow += tmp;
        }
    }

    // sからtへ1流す
    T flow(int s, int t) {
        bfs(s);
        if(level[t] < 0) return 0;
        iter.assign(G.size(), 0);
        return dfs(s, t, 1);
    }
    // 始点，終点tのフローで辺e=(from,to)の容量を1増やしたときの最大流の変化
    // 並列辺はたぶんバグる
    T add(int from, int to, int s, int t) {
        for(auto &e: G[from]) {
            if(e.to == to && !e.isrev) {
                e.cap++;
                break;
            }
        }
        return flow(s, t);
    }
    // 始点s，終点tのフローで辺e=(from,to)の容量を1減らしたときの最大流の変化
    // 並列辺はたぶんバグる
    T sub(int from, int to, int s, int t) {
        for(auto &e: G[from]) {
            if(e.to == to && !e.isrev) {
                T diff = 0;
                // 辺(from,to)で容量いっぱいに流れている
                if(e.cap == 0) {
                    // 残余グラフでfrom→toのパスがない
                    if(flow(from, to) == 0) {
                        flow(t, to);
                        flow(from, s);
                        diff = -1;
                    }
                    G[e.to][e.rev].cap--;
                } else {
                    e.cap--;
                }
                return diff;
            }
        }
        assert(false); // 存在しない辺を減らそうとした
    }

    friend ostream &operator <<(ostream& out, const dinic& a){
        out << endl;
        for(int i = 0; i < (int)a.G.size(); i++) {
            for(auto &e : a.G[i]) {
                if(e.isrev) continue;
                auto &rev_e = a.G[e.to][e.rev];
                out << i << "->" << e.to << " (flow: " << rev_e.cap << "/" << e.cap + rev_e.cap << ")" << endl;
            }
        }
        return out;
    }
};