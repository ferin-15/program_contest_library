vector<pair<int,int>> random_tree(int n, unsigned seed1 = 1, unsigned seed2 = 2) {
    random_set<int> t(seed1), g(seed2);

    vector<pair<int,int>> edges;
    for(int i=0; i<n; ++i) g.insert(i);
    t.insert(g.pop_random());
    for(int i=0; i<n-1; ++i) {
        int u = t.random();
        int v = g.pop_random();
        edges.emplace_back(u, v);
        t.insert(v);
    }

    return 
}