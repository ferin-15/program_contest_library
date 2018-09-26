template<typename T, int B = 3>
class persistentArray {
private:
  struct node {
    node *ch[1<<B] = {};
    T val = -1;

    node() {}
    node(const T &v) : val(v) {} 
  };

  node *root = nullptr;

  pair<node*, T*> mutable_get(node* x, int a) {
    x = x ? new node(*x) : new node();
    if(a == 0) return {x, &x->val};
    auto p = mutable_get(x->ch[a&((1<<B)-1)], a >> B);
    x->ch[a&((1<<B)-1)] = p.first;
    return make_pair(x, p.second);
  }
  T immutable_get(int a, node* x) {
    if(a == 0) return x->val;
    return immutable_get(a>>B, x->ch[a & ((1<<B)-1)]);
  }
public:
  persistentArray() {}

  T *mutable_get(const int &k) {
    auto p = mutable_get(root, k);
    root = p.first;
    return p.second;
  }
  T operator[](int k) {
    return immutable_get(k, root);
  }

  node* build(node *x, const T &dat, int a) {
    if(!x) x = new node();
    if(a == 0) {
      x->val = dat;
      return x;
    }
    auto p = build(x->ch[a&((1<<B)-1)], dat, a>>B);
    x->ch[a&((1<<B)-1)] = p;
    return x;
  }
  void build(const V<T> &v) {
    for(int i=0; i<(int)v.size(); ++i) {
      root = build(root, v[i], i);
    }
  }
};