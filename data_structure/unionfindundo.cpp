// BEGIN CUT
struct UnionFindUndo {
    vector<int> data;
    stack<PII> st;

    UnionFindUndo(int sz) : data(sz, -1) {}

    int find(int k) {
        if(data[k] < 0) return (k);
        return (find(data[k]));
    }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        st.emplace(x, data[x]);
        st.emplace(y, data[y]);
        if(x == y) return;
        if(data[x] > data[y]) swap(x, y);
        data[x] += data[y];
        data[y] = x;
    }
    void undo() {
        data[st.top().first] = st.top().second;
        st.pop();
        data[st.top().first] = st.top().second;
        st.pop();
    }
    bool same(int x, int y) { return find(x) == find(y); }
    int size(int k) { return (-data[find(k)]); }
};
// END CUT