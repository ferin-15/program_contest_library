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

struct FordFulkerson {
    struct edge {
        int to;
        ll cap;
        int rev;
        bool isrev;
    };

    vector<vector<edge>> g;
    vector<int> used;
    int timestamp;

    ll dfs(int idx, const int t, ll flow) {
        if(idx == t) return flow;
        used[idx] = timestamp;
        for(auto &e : g[idx]) {
            if(e.cap > 0 && used[e.to] != timestamp) {
                ll d = dfs(e.to, t, min(flow, e.cap));
                if(d > 0) {
                    e.cap -= d;
                    g[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    FordFulkerson() {}
    FordFulkerson(int n) : timestamp(0), g(n), used(n, -1) {}

    void add_edge(int from, int to, ll cap) {
        g[from].emplace_back((edge){to, cap, (int)g[to].size(), false});
        g[to].emplace_back((edge){from, 0, (int)g[from].size()-1, true});
    }

    ll max_flow(int s, int t) {
        ll flow = 0;
        ++timestamp;
        for(ll f; (f = dfs(s, t, INF)) > 0; timestamp++) {
            flow += f;
        }
        return flow;
    }

    friend ostream &operator <<(ostream& out, const FordFulkerson& a){
        out << "-----" << endl;
        for(int i = 0; i < (int)a.g.size(); i++) {
            for(auto &e : a.g[i]) {
                if(e.isrev) continue;
                auto &rev_e = a.g[e.to][e.rev];
                out << i << "->" << e.to << " (flow: " << rev_e.cap << "/" << e.cap + rev_e.cap << ")" << endl;
            }
        }
        out << "-----" << endl;
        return out;
    }
};