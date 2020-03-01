// BEGIN CUT
template<class T>
struct dinic {
    struct edge{
        int to;
        T cap;
        int rev;
        bool isrev;
    };

    vector<vector<edge>> G;
    vector<int> level, iter;

    void bfs(int s) {
        level.assign(G.size(), -1);
        queue<int> que;
        level[s] = 0;
        que.push(s);
        while(que.size()) {
            int v = que.front(); que.pop();
            for(auto i: G[v]) {
                if(i.cap > 0 && level[i.to] < 0) {
                    level[i.to] = level[v] + 1;
                    que.push(i.to);
                }
            }
        }
    }

    T dfs(int v, const int t, T f) {
        if(v == t) return f;
        for(int &i = iter[v]; i<(ll)G[v].size(); ++i) {
            edge &e = G[v][i];
            if(e.cap > 0 && level[v] < level[e.to]) {
                T d = dfs(e.to, t, min(f, e.cap));
                if(d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    dinic() {}
    dinic(int n) : G(n), level(n), iter(n) {}

    void add_edge(int from, int to, T cap) {
        G[from].push_back({to, cap, (int)G[to].size(), false});
        G[to].push_back({from, 0, (int)G[from].size()-1, true});
    }

    // sからtへ流量fを流す
    T maxflow(int s, int t, T f = 1LL<<30) {
        T flow = 0;
        while(1) {
            bfs(s);
            if(level[t] < 0) return flow;
            iter.assign(G.size(), 0);
            T tmp;
            while((tmp = dfs(s, t, f)) > 0) flow += tmp;
        }
    }

    // sからtへ1流す
    T flow(int s, int t) {
        bfs(s);
        if(level[t] < 0) return 0;
        iter.assign(G.size(), 0);
        return dfs(s, t, 1);
    }
    // 始点，終点tのフローで辺e=(from,to)の容量を1増やしたときの最大流の変化
    // 並列辺はたぶんバグる
    T add(int from, int to, int s, int t) {
        for(auto &e: G[from]) {
            if(e.to == to && !e.isrev) {
                e.cap++;
                break;
            }
        }
        return flow(s, t);
    }
    // 始点s，終点tのフローで辺e=(from,to)の容量を1減らしたときの最大流の変化
    // 並列辺はたぶんバグる
    T sub(int from, int to, int s, int t) {
        for(auto &e: G[from]) {
            if(e.to == to && !e.isrev) {
                T diff = 0;
                // 辺(from,to)で容量いっぱいに流れている
                if(e.cap == 0) {
                    // 残余グラフでfrom→toのパスがない
                    if(flow(from, to) == 0) {
                        flow(t, to);
                        flow(from, s);
                        diff = -1;
                    }
                    G[e.to][e.rev].cap--;
                } else {
                    e.cap--;
                }
                return diff;
            }
        }
        assert(false); // 存在しない辺を減らそうとした
    }

    friend ostream &operator <<(ostream& out, const dinic& a){
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

template<class F>
struct dinic_with_lowerlimit {
    int S, T;
    F sum_lb;
    dinic<F> flow;

    dinic_with_lowerlimit() {}
    dinic_with_lowerlimit(int n) : S(n), T(n+1), sum_lb(0), flow(n+2) {}

    void add_edge(int from, int to, F ub) {
        flow.add_edge(from, to, ub);
    }
    void add_edge(int from, int to, F lb, F ub) {
        flow.add_edge(from, to, ub-lb);
        flow.add_edge(S, to, lb);
        flow.add_edge(from, T, lb);
        sum_lb += lb;
    }

    // sからtへ最小流量を満たすフローが存在しなければ-1
    F maxflow(int s, int t) {
        F a = flow.maxflow(S, T);
        F b = flow.maxflow(s, T);
        F c = flow.maxflow(S, t);
        F d = flow.maxflow(s, t);
        return (a+b==sum_lb && a+c==sum_lb) ? b+d : -1;
    }
};
// END CUT