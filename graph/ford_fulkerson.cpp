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