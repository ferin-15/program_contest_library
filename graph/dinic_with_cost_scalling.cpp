template<class T>
class dinicWithCostScalling {
    struct edge{
        int to;
        T cap;
        int rev;
        bool isrev;
    };

    vector<vector<edge>> G;
    vector<int> level, iter;

    void bfs(int s, const T base) {
        level.assign(G.size(), -1);
        queue<int> que;
        level[s] = 0;
        que.push(s);
        while(que.size()) {
            int v = que.front(); que.pop();
            for(auto i: G[v]) {
                if(i.cap >= base && level[i.to] < 0) {
                    level[i.to] = level[v] + 1;
                    que.push(i.to);
                }
            }
        }
    }
    T dfs(int v, const int t, T f, const T base) {
        if(v == t) return f;
        for(int &i = iter[v]; i<(ll)G[v].size(); ++i) {
            edge &e = G[v][i];
            if(e.cap >= base && level[v] < level[e.to]) {
                T d = dfs(e.to, t, min(f, e.cap), base);
                if(d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

public:
    dinicWithCostScalling() {}
    dinicWithCostScalling(int n) : G(n), level(n), iter(n) {}

    void add_edge(int from, int to, T cap) {
        G[from].push_back({to, cap, (int)G[to].size(), false});
        G[to].push_back({from, 0, (int)G[from].size()-1, true});
    }

    // max_capは辺の最大容量
    T maxflow(int s, int t, T max_cap = 1LL<<30) {
        T flow = 0;
        const int tmp = __builtin_ctzll(max_cap);
        for(T base = 1LL<<tmp; base >= 1;) {
            bfs(s, base);
            if(level[t] < 0) {
                base >>= 1;
                continue;
            }
            iter.assign(G.size(), 0);
            flow += dfs(s, t, 1LL<<60, base);
        }
        return flow;
    }

    friend ostream &operator <<(ostream& out, const dinicWithCostScalling& a){
        out << endl;
        for(int i = 0; i < (int)a.G.size(); i++) {
            for(auto &e : a.G[i]) {
                if(e.isrev) continue;
                auto &rev_e = a.G[e.to][e.rev];
                out << i << "->" << e.to << " (flow: " << rev_e.cap << "/" << e.cap + rev_e.cap << ")" << endl;
            }
        }
        return out;
    }
};