// rolling-hash
class rollingHash {
public:
  static const int MAX_N = 200010;
  // MOD と 基数
  ll mo[2] = {1000000007, 1000000009};
  ll base[2] = {1009, 1007};
  ll hash[2][MAX_N], power[2][MAX_N];

  rollingHash() {}
  rollingHash(string s) { init(s); }

  // O(|S|)
  void init(string s) {
    REP(i, 2) {
      power[i][0] = 1;
      FOR(j, 1, MAX_N) power[i][j] = power[i][j-1]*base[i]%mo[i];
    }
    REP(i, 2) REP(j, s.size()) {
      hash[i][j+1] = (hash[i][j]+power[i][j]*(s[j]-'a'))%mo[i];
    }
  }

  // [l1, r1) と [l2, r2) が一致するかの判定 (l1 < l2)
  bool equal(int l1, int r1, int l2, int r2) {
    REP(i, 2) {
      ll a = (((hash[i][r1]-hash[i][l1])%mo[i])+mo[i])%mo[i];
      ll b = (((hash[i][r2]-hash[i][l2])%mo[i])+mo[i])%mo[i];
      if(a*power[i][l2-l1]%mo[i] == b) return true;
    }
    return false;
  }
};
