// 文字の種類数をtemplate引数で渡す
template <int types = 26>
struct AhoCorasick {
  // trie木のnode
  struct node {
    node *fail;
    vector<node*> next;
    VI matched;
    node() : fail(nullptr), next(types, nullptr) {}
  };

  // 辞書のサイズ
  int sz;
  // trie木の根
  node *root;
  // vectorを結合
  VI unite(const VI &a, const VI &b) {
    VI ret;
    set_union(ALL(a), ALL(b), back_inserter(ret));
    return ret;
  }
  // 文字と数字の対応付けをする関数
  function<int(char)> trans;
  // 初期化
  AhoCorasick() {}
  AhoCorasick(vector<string> pattern, function<int(char)> f = [](char c){return c-'a';}) {
    trans = f;
    build(pattern);
  }
  // 文字列集合patternからtrie木っぽいオートマトンを作成
  void build(vector<string> pattern) {
    sz = pattern.size(), root = new node;
    node *now;
    root->fail = root;
    REP(i, sz) {
      now = root;
      for(const auto &c: pattern[i]) {
        if(now->next[trans(c)] == nullptr) {
          now->next[trans(c)] = new node;
        }
        now = now->next[trans(c)];
      }
      now->matched.PB(i);
    }

    queue<node*> que;
    REP(i, types) {
      if(root->next[i] == nullptr) {
        root->next[i] = root;
      } else {
        root->next[i]->fail = root;
        que.push(root->next[i]);
      }
    }
    while(que.size()) {
      now = que.front(); que.pop();
      REP(i, types) {
        if(now->next[i] != nullptr) {
          node *nxt = now->fail;
          while(!nxt->next[i]) nxt = nxt->fail;
          now->next[i]->fail = nxt->next[i];
          now->next[i]->matched = unite(now->next[i]->matched, nxt->next[i]->matched);
          que.push(now->next[i]);
        }
      }
    }
  }
  // 一文字ずつ照合していく
  node* next(node* p, const char c) {
    while(p->next[trans(c)] == nullptr) p = p->fail;
    return p->next[trans(c)];
  }
  // 文字列s中に辞書と一致する部分列がどれだけあるか
  VI match(const string s) {
    VI res(sz);
    node *now = root;
    for(auto c : s) {
      now = next(now, c);
      for(auto i : now->matched) res[i]++;
    }
    return res;
  }
};
