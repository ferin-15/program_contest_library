struct HLDecomposition {
    int n, pos;
    vector<vector<ll> g;
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

    HLDecomposition(){}
    HLDecomposition(int sz):
        n(sz), pos(0), g(n),
        vid(n,-1), head(n), sub(n,1), hvy(n,-1),
        par(n), depth(n), inv(n), type(n), ps(n), pt(n) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void build(vector<ll> rs=vector<ll>(1,0)) {
        int c=0;
        for(int r: rs) {
            dfs1(r);
            dfs2(r, c++);
        }
    }

    // 根rtからdfsして部分木の大きさ、heavy-edgeの判定などをする
    void dfs1(int rt) {
        stack<PII> st;
        par[rt] = -1;
        depth[rt] = 0;
        st.emplace(rt, 0);
        while(st.size()) {
            int v = st.top().first;
            int &i = st.top().second;
            if(i < (int)g[v].size()) {
                int u = g[v][i++];
                if(u == par[v]) continue;
                par[u] = v;
                depth[u] = depth[v]+1;
                st.emplace(u, 0);
            } else {
                st.pop();
                for(int &u: g[v]){
                    if(u == par[v]) swap(u, g[v].back());
                    if(u == par[v]) continue;
                    sub[v] += sub[u];
                    if(sub[u]>sub[g[v].front()]) swap(u, g[v].front());
                }
            }
        }
    }
    // 根r、c番目の木についてchainについての情報をまとめる
    void dfs2(int r, int c) {
        using T = tuple<int, int, int>;
        stack<T> st;
        st.emplace(r,r,0);
        while(!st.empty()) {
            int v,h;
            tie(v,h,ignore)=st.top();
            int &i=get<2>(st.top());
            if(!i) {
                type[v]=c;
                ps[v]=vid[v]=pos++;
                inv[vid[v]]=v;
                head[v]=h;
                hvy[v]=(g[v].empty()?-1:g[v][0]);
                if(hvy[v]==par[v]) hvy[v]=-1;
            }
            if(i<(int)g[v].size()) {
                int u=g[v][i++];
                if(u==par[v]) continue;
                st.emplace(u,(hvy[v]==u?h:u),0);
            } else {
                st.pop();
                pt[v]=pos;
            }
        }
    }
    // 頂点に対する処理 [u,v] 開区間なので注意!!!
    void for_each(int u, int v, const function<void(int,int)>& f) {
        while(1){
            if(vid[u]>vid[v]) swap(u,v);
            // [max(vid[head[v]],vid[u]), vid[v]] の区間についての操作を行う
            f(max(vid[head[v]], vid[u]), vid[v]);
            if(head[u]!=head[v]) v = par[head[v]];
            else break;
        }
    }
    // 辺に対する処理 [u,v] 開区間なので注意!!!
    void for_each_edge(int u, int v, const function<void(int,int)>& f) {
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
    int lca(int u,int v){
        while(1) {
            if(vid[u]>vid[v]) swap(u,v);
            if(head[u]==head[v]) return u;
            v = par[head[v]];
        }
    }
    int distance(int u, int v){
        return depth[u] + depth[v] - 2*depth[lca(u,v)];
    }
};