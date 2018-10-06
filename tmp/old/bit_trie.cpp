#define __USE_MINGW_ANSI_STDIO 0
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define int ll
using VI = vector<int>;
using VVI = vector<VI>;
using PII = pair<int, int>;

#define FOR(i, a, n) for (ll i = (ll)a; i < (ll)n; ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(x) x.begin(), x.end()
#define PB push_back

const ll LLINF = (1LL<<60);
const int INF = (1LL<<30);
const int MOD = 1000000007;

template <typename T> T &chmin(T &a, const T &b) { return a = min(a, b); }
template <typename T> T &chmax(T &a, const T &b) { return a = max(a, b); }
template <typename T> bool IN(T a, T b, T x) { return a<=x&&x<b; }
template<typename T> T ceil(T a, T b) { return a/b + !!(a%b); }
template<class S,class T>
ostream &operator <<(ostream& out,const pair<S,T>& a){
  out<<'('<<a.first<<','<<a.second<<')';
  return out;
}
template<class T>
ostream &operator <<(ostream& out,const vector<T>& a){
  out<<'[';
  REP(i, a.size()) {out<<a[i];if(i!=a.size()-1)out<<',';}
  out<<']';
  return out;
}

int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

// trie
struct trie {
  struct node {
    int d, lch, rch;
    node() {lch=rch=d=-1;}
    node(int d):d(d){lch=rch=-1;}
  };
  vector<node> v;

  trie() { init(); }
  void init() {
    v.clear();
    v.PB(node(0));
  }

  // 01文字列sを追加
  void add(string s) {
    int now = 0;
    REP(i, s.size()) {
      if(s[i] == '0') {
        if(v[now].lch != -1) now = v[now].lch;
        else {
          v[now].lch = v.size();
          v.PB(node(v[now].d+1));
          now = v[now].lch;
        }
      } else {
        if(v[now].rch != -1) now = v[now].rch;
        else {
          v[now].rch = v.size();
          v.PB(node(v[now].d+1));
          now = v[now].rch;
        }
      }
    }
  }

  // 01文字列sとXORを取った結果最も大きい01文字列
  string max(string s) {
    string ans = "";
    int now = 0;
    REP(i, s.size()) {
      if(s[i] == '0') {
        if(v[now].rch != -1) {
          now = v[now].rch;
          ans += '1';
        } else if(v[now].lch != -1) {
          now = v[now].lch;
          ans += '0';
        } else {
          ans += s[i];
        }
      } else {
        if(v[now].lch != -1) {
          now = v[now].lch;
          ans += '1';
        } else if(v[now].rch != -1) {
          now = v[now].rch;
          ans += '0';
        } else {
          ans += s[i];
        }
      }
    }
    return ans;
  }
};
