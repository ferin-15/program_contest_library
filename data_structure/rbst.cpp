template<typename T>
struct RBST {
  struct node {
    T val, q;
    node *lch, *rch;
    int sz;
    node() : val(d), q(d), lch(nullptr), rch(nullptr), sz(1) {}
    node(T v) : val(v), q(v), lch(nullptr), rch(nullptr), sz(1) {}
  };

  using F = function<T(T,T)>;
  F f; F g; T d;
  node* root;

  RBST() {}
  RBST(F f_, F g_, T d_) : f(f_), g(g_), d(d_), root(nullptr) {}

  // 乱数生成
  unsigned long long xor128() {
    static unsigned long long rx = 123456789, ry = 362436069, rz = 521288629, rw = 88675123;
    unsigned long long rt = (rx ^ (rx << 11));
    rx = ry;
    ry = rz;
    rz = rw;
    return (rw = (rw ^ (rw >> 19)) ^ (rt ^ (rt >> 8)));
  }

  // szとqを取得するのに使う
  int sz_(node *t) {
    if(t == nullptr) return 0;
    return t->sz;
  }
  T q_(node *t) {
    if(t == nullptr) return d;
    return t->q;
  }
  // node tの値を正しくする
  node* fix(node *t) {
    t->sz = sz_(t->lch) + sz_(t->rch) + 1;
    t->q  = f(t==nullptr?d:t->val, f(q_(t->lch), q_(t->rch)));
    return t;
  }
  // lとrのマージ
  node* merge(node *l, node *r) {
    if(l == nullptr) return r;
    if(r == nullptr) return l;
    int lsz = sz_(l), rsz = sz_(r);
    if(xor128()%(lsz+rsz) < lsz) {
      l->rch = merge(l->rch, r);
      return fix(l);
    } else {
      r->lch = merge(l, r->lch);
      return fix(r);
    }
  }
  // [0, k) [k, n) で分割する
  pair<node*, node*> split(node *t, int k) {
    if(t == nullptr) return pair<node*,node*>(nullptr, nullptr);
    if(k <= sz_(t->lch)) {
      pair<node*, node*> s = split(t->lch, k);
      t->lch = s.second;
      return make_pair(s.first, fix(t));
    } else {
      pair<node*, node*> s = split(t->rch, k-sz_(t->lch)-1);
      t->rch = s.first;
      return make_pair(fix(t), s.second);
    }
  }
  // pos番目に値valのnodeを追加
  node* insert(int pos, T val) { return root = insert(root, pos, val); }
  node* insert(node *t, int pos, T val) {
    pair<node*, node*> s = split(t, pos);
    node *tmp = merge(s.first, new node(val));
    return merge(tmp, s.second);
  }
  // pos番目のnodeを削除
  node* erase(int pos) { return root = sz_(root)==1 ? nullptr : erase(root, pos); }
  node* erase(node* t, int pos) {
    pair<node*, node*> p1 = split(t, pos); // [0,pos)[pos,n)
    pair<node*, node*> p2 = split(p1.second, 1); // [pos,pos+1)[pos+1,n)
    return merge(p1.first, p2.second);
  }
  // pos番目に対する点更新
  void update(int pos, T val) { update(root, pos, val); }
  void update(node *t, int pos, T val) {
    if(pos < sz_(t->lch)) update(t->lch, pos, val);
    else if(pos > sz_(t->lch)) update(t->rch, pos-sz_(t->lch)-1, val);
    else t->val = g(t->val, val);
    fix(t);
  }
  // ToDo: 区間更新 
  // pos番目を取得する点クエリ
  T query(int pos) { return query(root, pos); }
  T query(node *t, int pos) {
    if(pos < sz_(t->lch)) return query(t->lch, pos);
    else if(pos > sz_(t->lch)) return query(t->rch, pos-sz_(t->lch)-1);
    return t->val;
  }
  // [l,r)に対する区間クエリ 
  T query(int l, int r) {
    pair<node*, node*> p1 = split(root, r);     // [0,r)[r,n)
    pair<node*, node*> p2 = split(p1.first, l); // [0,l)[l,r)
    node* mid = p2.second;
    T ret = q_(mid);
    root = merge(merge(p2.first, mid), p1.second);
    return ret;
  }
  // デバッグ用
  void debug() { debug(root); cout << endl; }
  void debug(node* t) {
    if(t == nullptr) return;
    cout << "[";
    debug(t->lch);
    cout << " " << t->val << " ";
    debug(t->rch);
    cout << "]";
  }
  void print_array(int n) {
    REP(i, n) cout << query(i) << " ";
    cout << endl;
  }
};