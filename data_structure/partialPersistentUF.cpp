// find:O(logN) unite:O(logN)
struct partialPersistentUF {
    const static int MAX_N = 100010;
    unordered_map<int, int> par[MAX_N];
    int rank[MAX_N];
    int fin[MAX_N];
    int idx;
    partialPersistentUF() { init(); }
    partialPersistentUF(int n) { init(n); }
    void init(int n=MAX_N) {
        idx = 0;
        REP(i, n) par[i][0] = i, rank[i] = 1, fin[i] = 0;
    }
    int find(int x, int t) {
        if(t >= fin[x] && par[x][fin[x]] != x) return find(par[x][fin[x]], t);
        return x;
    }
    void unite(int x, int y) {
        x = find(x, idx);
        y = find(y, idx);
        idx++;
        if(x == y) return;
        if(rank[x] < rank[y]) par[x][idx] = y, fin[x] = idx;
        else {
          par[y][idx] = x, fin[y] = idx;
          if(rank[x] == rank[y]) rank[x]++;
        }
    }
    bool same(int x, int y, int t) { return find(x, t) == find(y, t); }
};
