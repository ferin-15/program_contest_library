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

struct SCC {
    int V, K;
    vector<vector<int>> G;
    vector<vector<int>> rG;
    vector<int> vs;
    vector<int> used;
    vector<int> cmp;

    void dfs(int v) {
        used[v]=true;
        for(int nx: G[v]) if(!used[nx]) dfs(nx);
        vs.push_back(v);
    }
    void rdfs(int v,int k) {
        used[v]=true; cmp[v]=k;
        for(int nx: rG[v]) if(!used[nx]) rdfs(nx,k);
    }

    SCC() { V=K=-1; }
    SCC(int V_): V(V_), G(V_), rG(V_), used(V_), cmp(V_) {}

    void add_edge(int from,int to) {
        G[from].push_back(to);
        rG[to].push_back(from);
    }
    int scc() {
        used.assign(V,0); vs.clear();
        for(int v=0;v<V;v++) if(!used[v]) dfs(v);
        used.assign(V,0);
        int k=0;
        for(int i=(int)vs.size()-1;i>=0;i--) if(!used[vs[i]]) {
            rdfs(vs[i],k++);
        }
        return K=k;
    }
    // O(ElogE)
    // SCCしたあとのグラフはトポロジカル順になってる
    vector<vector<int>> getDAG() {
        vector<vector<int>> res(K);
        for(int from=0;from<V;from++) {
            for(int to:G[from]) if(cmp[from]!=cmp[to]) {
                res[cmp[from]].push_back(cmp[to]);
            }
        }
        for(int i=0;i<K;i++){
            sort(ALL(res[i]));
            res[i].erase(unique(ALL(res[i])),res[i].end());
        }
        return res;
    }
    // MLがやばいときに途中でいらないのを消す
    void clear() {
        vector<int>().swap(vs);
        vector<int>().swap(used);
        vector<vector<int>>().swap(G);
        vector<vector<int>>().swap(rG);
    }
};

namespace GRL3C {
    void solve() {
        ll n, m;
        cin >> n >> m;
        SCC scc(n);
        REP(i, m) {
            ll u, v;
            cin >> u >> v;
            scc.add_edge(u, v);
        }
        scc.scc();
        ll q;
        cin >> q;
        REP(i, q) {
            ll u, v;
            cin >> u >> v;
            if(scc.cmp[u] == scc.cmp[v]) cout << 1 << endl;
            else cout << 0 << endl;
        }
    }
}

signed main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    GRL3C::solve();

    return 0;
}
