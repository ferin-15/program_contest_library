struct SCC {
    int V, K;
    vector<vector<int>> G;
    vector<vector<int>> rG;
    vector<int> vs;
    vector<int> used;  
    vector<int> cmp;
    SCC() { V=K=-1; }
    SCC(int V_): V(V_), G(V_), rG(V_), used(V_), cmp(V_) {}
    void add_edge(int from,int to) {
        G[from].push_back(to);
        rG[to].push_back(from);
    }
    void dfs(int v) {
        used[v]=true;
        for(int nx: G[v]) if(!used[nx]) dfs(nx);
        vs.push_back(v);
    }
    void rdfs(int v,int k) {
        used[v]=true; cmp[v]=k;
        for(int nx: rG[v]) if(!used[nx]) rdfs(nx,k);
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
    // いらないやつをちゃんと確認
    void clear() {
        vector<int>().swap(vs);
        vector<int>().swap(used);
        vector<vector<int>>().swap(G);
        vector<vector<int>>().swap(rG);
    }
};