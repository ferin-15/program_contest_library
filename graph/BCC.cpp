// BEGIN CUT
struct twoEdgeComponents {
    int n;
    vector<vector<int>> g;        // グラフの隣接リスト
    vector<int> cmp;              // 頂点iがどの連結成分に属するか
    vector<vector<int>> each_bcc; // i番目の連結成分の属する頂点
    vector<pair<int,int>> bridge; // i番目の橋
    vector<int> order;
    vector<bool> inS;
    stack<int> roots, S;

    twoEdgeComponents() {}
    twoEdgeComponents(vector<vector<int>> g_) : n(g_.size()), g(g_) {}

    void add_edge(int p, int q) {
        g[p].push_back(q);
        g[q].push_back(p);
    }

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
// END CUT