struct SuffixArray {
  VI SA, rank, tmp;
  string s;
  int n;

  SuffixArray() {}
  SuffixArray(const string& str) { build(str); }

  void build(const string& str) {
    s = str, n = s.size();
    SA.resize(n+1); rank.resize(n+1); tmp.resize(n+1);
    REP(i, n+1) {
      SA[i] = i;
      rank[i] = s[i];
    }
    for(int k=1; k<=n; k*=2) {
      auto comp = [&](int i, int j) -> bool {
        if(rank[i] != rank[j]) return rank[i] < rank[j];
        else {
          int ri = i+k<=n ? rank[i+k] : -1;
          int rj = j+k<=n ? rank[j+k] : -1;
          return ri < rj;
        }
      };
      sort(ALL(SA), comp);

      tmp[SA[0]] = 0;
      FOR(i, 1, n+1) tmp[SA[i]] = tmp[SA[i-1]] + (comp(SA[i-1], SA[i]) ? 1 : 0);
      rank = tmp;
    }
  }

  int operator[](int k) const { return (SA[k]); }
  int size() const { return (SA.size()); }

  void debug() {
    for(int i = 0; i < size(); i++) {
      cout << i << ": " << s.substr(SA[i]) << endl;
    }
  }
};