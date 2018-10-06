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

// 2進数っぽく値を管理している、multisetとかXOR絡みの操作ができる
template<typename T = int, int B = 32>
class binaryTrie {
private:
  struct node {
    int cnt;
    T lazy;
    node *ch[2];
    node() : cnt(0), lazy(0), ch{nullptr, nullptr} {}
  };
  void eval(node* t, int depth) {
    if(t->lazy >> depth & 1) swap(t->ch[0], t->ch[1]);
    if(t->ch[0]) t->ch[0]->lazy ^= t->lazy;
    if(t->ch[1]) t->ch[1]->lazy ^= t->lazy;
    t->lazy = 0;
  }
  node* add(node *t, T val, int depth = B-1) {
    if(!t) t = new node;
    t->cnt++;
    if(depth < 0) return t;
    eval(t, depth);
    bool f = (val >> depth) & 1;
    t->ch[f] = add(t->ch[f], val, depth-1);
    return t;
  }
  node* sub(node *t, T val, int depth = B-1) {
    assert(t);  // 存在しないやつは引けない
    t->cnt--;
    if(t->cnt == 0) return nullptr;
    if(depth < 0) return t;
    eval(t, depth);
    bool f = (val >> depth) & 1;
    t->ch[f] = sub(t->ch[f], val, depth-1);
    return t;
  }
  T get_min(node *t, T val, int depth = B-1) {
    assert(t);
    if(depth < 0) return 0;
    eval(t, depth);
    bool f = (val >> depth) & 1; f ^= !t->ch[f];
    return get_min(t->ch[f], val, depth-1) | (f << depth);
  }
  T get(node *t, int k, int depth = B-1) {
    if(depth < 0) return 0;
    eval(t, depth);
    int m = t->ch[0] ? t->ch[0]->cnt : 0;
    if(k < m) return get(t->ch[0], k, depth-1);
    return get(t->ch[1], k-m, depth-1) | (1 << depth);
  }
  int count_lower(node* t, T val, int depth = B-1) {
    if(!t || depth < 0) return 0;
    eval(t, depth);
    bool f = (val >> depth) & 1;
    int tmp = (f && t->ch[0]) ? t->ch[0]->cnt : 0;
    return tmp + count_lower(t->ch[f], val, depth-1);
  }
  node* root;
public:
  binaryTrie() : root(nullptr) {}
  // 要素数、空かどうか
  int size() const { return root ? root->cnt : 0; }
  bool empty() const { return !root; }
  // valを一つ追加する O(B)
  void insert(T val) { root = add(root, val); }
  // valを一つ減らす O(B)
  void erase(T val) { root = sub(root, val); }
  // 全ての要素についてvalとXORを取る
  void xor_all(T val) { if(root) root->lazy ^= val; }
  // valとXORを取ったときのmax O(B)
  T max_element(T val=0) { return get_min(root, ~val); }
  // valとXORを取ったときのmin O(B)
  T min_element(T val=0) { return get_min(root, val); }
  // val以上の最小の要素のid O(B)
  int lower_bound(T val) { return count_lower(root, val); }
  // valより大きい最小の要素のid O(B)
  int upper_bound(T val) { return count_lower(root, val+1); }
  // 0-indexedでk番目の要素の値 O(B)
  T operator[](int k) {
    assert(0 <= k && k < size());
    return get(root, k);
  }
  // valの個数 O(B)
  int count(T val) {
    if(!root) return 0;
    node *t = root;
    for(int i=B-1; i>=0; --i) {
      t = t->ch[val>>i&1];
      if(!t) return 0;
    }
    return t->cnt;
  }
};

signed main(void)
{
  cin.tie(0);
  ios::sync_with_stdio(false);

  int t;
  cin >> t;
  REP(tes, t) {
    int n, k;
    cin >> n >> k;
    VI a(n);
    REP(i, n) cin >> a[i];

    binaryTrie<int, 32> trie;
    int ret = 0;
    REP(i, n) {
      trie.insert(0);
      trie.xor_all(a[i]);
      ret += trie.lower_bound(k);
    }
    cout << ret << endl;
  }

  return 0;
}
