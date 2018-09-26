/**
* @file binary_trie.cpp
* @brief 2進trie
* @detail verify: 未
* @author ferin
*/

// BEGIN CUT
/**
* @brief 2進trie
* @details 
* insertやeraseやbit演算やk-thnumberやlower_bound,upper_boundなどに対応\n
* B=log(max(A)) で 空間O(NB)、時間O(B)
*/
template<typename T = int, int B = 32>
class binaryTrie {
private:
  struct node {
    int cnt;
    T lazy;
    node *ch[2];
    node() : cnt(0), lazy(0), ch{nullptr, nullptr} {}
  };
  /**
  * @brief 遅延評価を行う
  * @param[in] t 今見ている頂点t
  * @param[in] depth 見ている頂点の深さ
  */
  void eval(node* t, int depth) {
    if(t->lazy >> depth & 1) swap(t->ch[0], t->ch[1]);
    if(t->ch[0]) t->ch[0]->lazy ^= t->lazy;
    if(t->ch[1]) t->ch[1]->lazy ^= t->lazy;
    t->lazy = 0;
  }
  /**
  * @brief 値の追加を行う
  * @param[in] t 今見ている頂点t
  * @param[in] val 加える値val
  * @param[in] depth 見ている頂点の深さ
  */
  node* add(node *t, T val, int depth = B-1) {
    if(!t) t = new node;
    t->cnt++;
    if(depth < 0) return t;
    eval(t, depth);
    bool f = (val >> depth) & 1;
    t->ch[f] = add(t->ch[f], val, depth-1);
    return t;
  }
  /**
  * @brief 値の削除を行う
  * @param[in] t 今見ている頂点t
  * @param[in] val 削除する値val
  * @param[in] depth 見ている頂点の深さ
  */
  node* sub(node *t, T val, int depth = B-1) {
    assert(t);
    t->cnt--;
    if(t->cnt == 0) return nullptr;
    if(depth < 0) return t;
    eval(t, depth);
    bool f = (val >> depth) & 1;
    t->ch[f] = sub(t->ch[f], val, depth-1);
    return t;
  }
  /**
  * @brief valとXORを取ったときに最小となる値
  * @param[in] t 今見ている頂点t
  * @param[in] val XORを取る値
  * @param[in] depth 見ている頂点の深さ
  */
  T get_min(node *t, T val, int depth = B-1) {
    assert(t);
    if(depth < 0) return 0;
    eval(t, depth);
    bool f = (val >> depth) & 1; f ^= !t->ch[f];
    return get_min(t->ch[f], val, depth-1) | (f << depth);
  }
  /**
  * @brief k番目の値を求める
  * @param[in] t 今見ている頂点t
  * @param[in] k k番目の値
  * @param[in] depth 見ている頂点の深さ
  */
  T get(node *t, int k, int depth = B-1) {
    if(depth < 0) return 0;
    eval(t, depth);
    int m = t->ch[0] ? t->ch[0]->cnt : 0;
    if(k < m) return get(t->ch[0], k, depth-1);
    return get(t->ch[1], k-m, depth-1) | (1 << depth);
  }
  /**
  * @brief valより大きい最小の要素が何番目の要素か
  * @param[in] t 今見ている頂点t
  * @param[in] val 境界となる値val
  * @param[in] depth 見ている頂点の深さ
  */
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
  /**
  * @brief valを追加する
  * @param[in] val 追加する値
  */
  void insert(T val) { root = add(root, val); }
  /**
  * @brief valを1つ削除する
  * @param[in] val 削除する値
  */
  void erase(T val) { root = sub(root, val); }
  /**
  * @brief 集合内の全ての要素に対してvalとxorを取る
  * @param[in] val XORを取る値
  */
  void xor_all(T val) { if(root) root->lazy ^= val; }
  /**
  * @brief valとXORを取ったときのmax
  * @param[in] val XORを取る値
  */
  T max_element(T val=0) { return get_min(root, ~val); }
  /**
  * @brief valとXORを取ったときのmin
  * @param[in] val XORを取る値
  */
  T min_element(T val=0) { return get_min(root, val); }
  /**
  * @brief val以上の最小の要素が何番目か
  * @param[in] val 指定する境界の値
  */
  int lower_bound(T val) { return count_lower(root, val); }
  /**
  * @brief valより大きい最小の要素が何番目か
  * @param[in] val 指定する境界の値
  */
  int upper_bound(T val) { return count_lower(root, val+1); }
  /**
  * @brief 0-indexでk番目の要素
  * @param[in] k 指定するindex
  */
  T operator[](int k) {
    assert(0 <= k && k < size());
    return get(root, k);
  }
  /**
  * @brief 値valの個数
  * @param[in] val 指定する値val
  */
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
// END CUT