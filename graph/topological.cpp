// BEGIN CUT
// ans[i] = (i番目の頂点v, swapできる頂点をまとめたときにvが何番目か)
vector<PII> tsort(vector<vector<ll>> g) {
    const int n = g.size();
    vector<ll> h(n);
    REP(i, n) for(int j: g[i]) h[j]++;

    stack<PII> st;
    REP(i, n) if(h[i] == 0) st.push({i, 0});

    vector<PII> ans;
    while(st.size()) {
        PII p = st.top(); st.pop();
        ans.push_back(p);
        for(auto& j: g[p.first]) {
            h[j]--;
            if(h[j] == 0) st.push({j, p.second+1});
        }
    }

    return ans;
}
// END CUT