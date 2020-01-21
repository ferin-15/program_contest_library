// O(n*1.466^n) n<=40で16ms
class maxIndependentSet {
public:
    int n;
    vector<int> deg, used, dead, ans;
    vector<vector<int>> g;

private:
    int ret, cnt, alive;
    void dfs() {
        if(cnt+alive <= ret) return;

        int v = -1;
        REP(i, n) if(!used[i] && !dead[i]) {
            if(deg[i] <= 1) { v = i; break; }
            if(v<0 || deg[v]<deg[i]) v=i;
        }
        if(v<0) return;

        if(deg[v] != 1) {
            dead[v] = 1;
            alive--;
            for(auto i: g[v]) deg[i]--;
            dfs();
            dead[v] = 0;
            alive++;
            for(auto i: g[v]) deg[i]++;
        }
        {
            used[v] = 1;
            alive--;
            for(auto i: g[v]) {
                if(dead[i] == 0) alive -= !used[i];
                dead[i]++;
            }
            cnt++;
            if(ret < cnt) ans = used, ret = cnt;
            dfs();
            used[v] = 0;
            alive++;
            for(auto i: g[v]) {
                dead[i]--;
                if(dead[i] == 0) alive += !used[i];
            }
            cnt--;
        }
    }

public:
    maxIndependentSet() {}
    maxIndependentSet(ll n) : n(n), deg(n), used(n), dead(n), ans(n), g(n) {}

    void add_edge(ll a, ll b) {
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<ll> get() {
        REP(i, n) deg[i] = g[i].size();
        ret = cnt = 0, alive = n;
        dfs();
        vector<ll> ans_set;
        REP(i, n) if(ans[i]) ans_set.push_back(i);
        return ans_set;
    }
};

namespace thanks2017G {
    void solve() {
        ll n, m;
        cin >> n >> m;
        maxIndependentSet graph(n);
        REP(i, m) {
            int a, b;
            cin >> a >> b;
            graph.add_edge(a-1, b-1);
        }
        cout << graph.get().size() << endl;
    }
}