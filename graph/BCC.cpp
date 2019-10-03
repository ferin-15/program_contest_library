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

struct twoEdgeComponents {
    int n;
    vector<vector<int>> g;        // グラフの隣接リスト
    vector<int> cmp;              // 頂点iがどの連結成分に属するか
    vector<vector<int>> each_bcc; // i番目の連結成分の属する頂点
    vector<pair<int,int>> bridge; // i番目の橋
    vector<int> order;
    vector<bool> inS;
    stack<int> roots, S;

    void dfs(int cur, int prev, int &k) {
        order[cur] = ++k;
        S.push(cur); inS[cur] = true;
        roots.push(cur);

        for(auto to: g[cur]) {
            if(order[to]==0) dfs(to, cur, k);
            else if(to!=prev && inS[to]) {
                while(order[roots.top()] > order[to]) roots.pop();
            }
        }

        if(cur == roots.top()) {
            if(prev!=-1) bridge.push_back({prev, cur});
            vector<int> bcc;
            while(1) {
                int node = S.top(); S.pop(); inS[node] = false;
                bcc.push_back(node);
                if(node==cur) break;
            }
            each_bcc.push_back(bcc);
            roots.pop();
        }
    }

    twoEdgeComponents() {}
    twoEdgeComponents(int n) : n(n), g(n) {}

    void add_edge(int p, int q) {
        g[p].push_back(q);
        g[q].push_back(p);
    }
    // 二重辺連結成分分解を行う
    void bcc() {
        order.assign(n, 0);
        inS.assign(n, false);
        cmp.assign(n, -1);
        int k = 0;
        for(int i=0; i<n; ++i) {
            if(order[i] == 0) {
                dfs(i, -1, k);
            }
        }
        for(int i=0; i<(int)each_bcc.size(); ++i) {
            for(auto j: each_bcc[i]) {
                cmp[j] = i;
            }
        }
    }
    // 分解したあとの木を求める
    vector<vector<int>> getbcc() {
        vector<vector<int>> h(each_bcc.size(), vector<int>());
        for(auto i: bridge) {
            int a = cmp[i.first], b = cmp[i.second];
            h[a].push_back(b);
            h[b].push_back(a);
        }
        return h;
    }
};