// BEGIN CUT
VI tsort(VVI g) {
  const int n = g.size();
  VI h(n, 0);
  REP(i, n) for(int j: g[i]) h[j]++;

  stack<int> st;
  REP(i, n) if(h[i] == 0) st.push(i);

  VI ans;
  while(st.size()) {
    int i = st.top(); st.pop();
    ans.push_back(i);
    for(auto& j: g[i]) {
      h[j]--;
      if(h[j] == 0) st.push(j);
    }
  }

  return ans;
}
// END CUT
