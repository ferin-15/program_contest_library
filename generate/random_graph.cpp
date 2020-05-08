vector<pair<int,int>> random_graph(int n, int m, unsigned seed1 = 1, unsigned seed2 = 2) {
    random_set<int> t(seed1), g(seed2);

    vector<pair<int,int>> edges;
    set<pair<int,int>> st;
    for(int i=0; i<n; ++i) g.insert(i);
    t.insert(g.pop_random());
    for(int i=0; i<n-1; ++i) {
        int u = t.random();
        int v = g.pop_random();
        if(u > v) swap(u, v);
        edges.emplace_back(u, v);
        t.insert(v);
    }

    for(int i=0; i<m-(int)edges.size(); ++i) {
        int u, v;
        do {
            u = t.random();
            v = t.random();
            while(u == v) v = t.random();
            if(u > v) swap(u, v);
        } while(st.find({u, v}) != st.end());
        edges.emplace_back(u, v);
        st.insert({u, v});
    }

    return edges;
}