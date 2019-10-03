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

struct HLDecomposition {
    int n, pos;
    vector<vector<ll>> g;
    vector<ll> vid,   // HL分解後のグラフでのid
        head,  // 頂点が属するheavy-pathのheadのid
        sub,   // 部分木のサイズ
        hvy,   // heavy-path上での次の頂点のid
        par,   // 親のid
        depth, // 深さ
        inv,   // HL分解前のグラフのid（添え字が分解後のid）
        type,  // 森をHL分解するときの属する木の番号
        ps,    // 行きがけ順
        pt;    // 帰りがけ順

    // 根rtからdfsして部分木の大きさ、heavy-edgeの判定などをする
    void dfs1(ll rt) {
        stack<PII> st;
        par[rt] = -1;
        depth[rt] = 0;
        st.emplace(rt, 0);
        while(st.size()) {
            ll v = st.top().first;
            ll &i = st.top().second;
            if(i < (ll)g[v].size()) {
                ll u = g[v][i++];
                if(u == par[v]) continue;
                par[u] = v;
                depth[u] = depth[v]+1;
                st.emplace(u, 0);
            } else {
                st.pop();
                for(ll &u: g[v]){
                    if(u == par[v]) swap(u, g[v].back());
                    if(u == par[v]) continue;
                    sub[v] += sub[u];
                    if(sub[u]>sub[g[v].front()]) swap(u, g[v].front());
                }
            }
        }
    }
    // 根r、c番目の木についてchainについての情報をまとめる
    void dfs2(ll r, ll c) {
        using T = tuple<ll, ll, ll>;
        stack<T> st;
        st.emplace(r,r,0);
        while(!st.empty()) {
            ll v,h;
            tie(v,h,ignore)=st.top();
            ll &i=get<2>(st.top());
            if(!i) {
                type[v]=c;
                ps[v]=vid[v]=pos++;
                inv[vid[v]]=v;
                head[v]=h;
                hvy[v]=(g[v].empty()?-1:g[v][0]);
                if(hvy[v]==par[v]) hvy[v]=-1;
            }
            if(i<(ll)g[v].size()) {
                ll u=g[v][i++];
                if(u==par[v]) continue;
                st.emplace(u,(hvy[v]==u?h:u),0);
            } else {
                st.pop();
                pt[v]=pos;
            }
        }
    }

    HLDecomposition(){}
    HLDecomposition(ll sz):
        n(sz), pos(0), g(n),
        vid(n,-1), head(n), sub(n,1), hvy(n,-1),
        par(n), depth(n), inv(n), type(n), ps(n), pt(n) {}

    void add_edge(ll u, ll v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void build(vector<ll> rs=vector<ll>(1,0)) {
        ll c=0;
        for(ll r: rs) {
            dfs1(r);
            dfs2(r, c++);
        }
    }

    // 頂点に対する処理 [u,v] 開区間なので注意!!!
    void for_each(ll u, ll v, const function<void(ll,ll)>& f) {
        while(1){
            if(vid[u]>vid[v]) swap(u,v);
            // [max(vid[head[v]],vid[u]), vid[v]] の区間についての操作を行う
            f(max(vid[head[v]], vid[u]), vid[v]);
            if(head[u]!=head[v]) v = par[head[v]];
            else break;
        }
    }
    // 辺に対する処理 [u,v] 開区間なので注意!!!
    void for_each_edge(ll u, ll v, const function<void(ll,ll)>& f) {
        while(1) {
            if(vid[u]>vid[v]) swap(u,v);
            if(head[u]!=head[v]) {
                f(vid[head[v]], vid[v]);
                v = par[head[v]];
            } else {
                if(u!=v) f(vid[u]+1, vid[v]);
                break;
            }
        }
    }
    ll lca(ll u, ll v) {
        while(1) {
            if(vid[u]>vid[v]) swap(u,v);
            if(head[u]==head[v]) return u;
            v = par[head[v]];
        }
    }
    ll distance(ll u, ll v) {
        return depth[u] + depth[v] - 2*depth[lca(u,v)];
    }
};
/*
パスu-vの頂点属性クエリ → hld.for_each(u, v, f)
パスu-vの辺属性クエリ → hld.for_each_edge(u, v, f)
頂点vの部分木に対するクエリ → 区間[hld.vid[u]+1, hld.vid[u] + hld.sub[u]) に操作
*/

namespace abc014D {
    void solve() {
        ll n;
        cin >> n;
        HLDecomposition graph(n);
        vector<vector<ll>> g(n);
        REP(i, n-1) {
            ll a, b;
            cin >> a >> b;
            a--, b--;
            g[a].push_back(b);
            g[b].push_back(a);
            graph.add_edge(a, b);
        }
        graph.build();

        vector<ll> dist(n);
        function<void(ll,ll,ll)> dfs = [&](ll v, ll p, ll d) {
            dist[v] = d;
            for(auto to: g[v]) if(to != p) {
                dfs(to, v, d+1);
            }
        };
        dfs(0, -1, 0);

        ll q;
        cin >> q;
        REP(i, q) {
            ll u, v;
            cin >> u >> v;
            u--, v--;
            ll lca = graph.lca(u, v);
            cout << dist[u] + dist[v] - 2*dist[lca] + 1 << endl;
        }
    }
}