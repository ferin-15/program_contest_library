---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: oldcode/rbst_new.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#bf50ccff88ac9b2562bee63cf804278c">oldcode</a>
* <a href="{{ site.github.repository_url }}/blob/master/oldcode/rbst_new.cpp">View this file on GitHub</a>
    - Last commit date: 2019-10-03 22:20:29+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<typename T,typename E>
struct RBST {
  int xor128() {
    static int x = 123456789;
    static int y = 362436069;
    static int z = 521288629;
    static int w = 88675123; 
    int t;
   
    t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
  }
  using F = function<T(T,T)>;
  using G = function<T(T,E)>;
  using H = function<E(E,E)>;

  F f;
  G g;
  H h;
  T ti;
  E ei;
  
  struct node {
    node *lch,*rch;
    int cnt;
    T val,dat;
    E lazy;
    node() {}
    node(T val, E l) :
      cnt(1), val(val), dat(val), lazy(l) { lch=rch=nullptr; }
  };

  vector<node> pool;
  int ptr;

  RBST(int n, F f, G g, H h, T ti, E ei) :
    f(f), g(g), h(h), ti(ti), ei(ei), pool(n), ptr(0) {}

  // vector v で初期化
  node* build(int l,int r,vector<T> &v) {
    if(l+1 == r) return create(v[l]);
    int m = (l+r)/2;
    return merge(build(l,m,v), build(m,r,v));
  }
  node* build(vector<T> &v) {
    return build(0, v.size(), v);
  }
  // 事前に作っておいたnodeから取ってくる
  inline node* create(){
    return &pool[ptr++];
  }
  inline node* create(T v){
    return &(pool[ptr++] = node(v, ei));
  }
  // cnt,datへのアクセス
  inline int count(const node* a) {
    if(a == nullptr) return 0;
    return a->cnt;
  }
  inline T query(const node *a) {
    if(a == nullptr) return ti;
    return a->dat;
  }
  // node aの値を正しくする
  inline node* update(node* a){
    if(a == nullptr) return a;
    a->cnt = count(a->lch) + count(a->rch) + 1;
    a->dat = f(query(a->lch), f(a->val, query(a->rch)));
    return a;
  }
  // 遅延評価
  node* eval(node* a){
    if(a->lazy != ei){ 
      a->val = g(a->val, a->lazy);
      if(a->lch != nullptr){
        a->lch->lazy = h(a->lch->lazy, a->lazy);
        a->lch->dat = g(a->lch->dat, a->lazy);
      }
      if(a->rch != nullptr){
        a->rch->lazy = h(a->rch->lazy, a->lazy);
        a->rch->dat = g(a->rch->dat, a->lazy);
      }
      a->lazy = ei;
    }
    return update(a);
  }
  // pos番目に挿入
  inline node* insert(node* a, int pos, T v){
    node* b = create(v);
    auto s = split(a,pos);
    return a = merge(merge(s.first,b),s.second);
  }
  // pos番目を削除
  inline node* erase(node* a,int pos){
    auto s = split(a, pos);
    auto t = split(s.second, 1);
    return merge(s.first, t.second);
  }
  // node a, bを併合
  node* merge(node* a,node* b){
    if(a == nullptr) return b;
    if(b == nullptr) return a;
    if(xor128() % (count(a)+count(b)) < count(a)){
      a = eval(a);
      a->rch = merge(a->rch,b);
      return update(a);
    }
    b = eval(b);
    b->lch = merge(a,b->lch);
    return update(b);
  }
  // [0,k)[k,n) で分割
  pair<node*, node*> split(node* a,int k){
    if(a==nullptr) return make_pair(a,a);
    a=eval(a);
    if(k<=count(a->lch)){
      auto s=split(a->lch,k);
      a->lch=s.second;
      return make_pair(s.first,update(a));
    }
    auto s=split(a->rch,k-(count(a->lch)+1));
    a->rch=s.first;
    return make_pair(update(a),s.second);
  } 
  // [l,r)
  inline T query(node *&a, int l, int r){
    auto s=split(a,l);
    auto t=split(s.second,r-l);
    auto u=t.first;
    T res=query(u);
    a=merge(s.first,merge(t.first,t.second));
    return res;
  }
  // [l,r)
  inline void update(node *&a,int l,int r,E v){
    auto s=split(a,l);
    auto t=split(s.second,r-l);
    auto u=t.first;
    u->lazy=h(u->lazy,v);
    a=merge(merge(s.first,eval(u)),t.second);
  }
  // p番目
  inline T get(node *&a,int p){
    auto s=split(a,p);
    auto t=split(s.second,1);
    T res=t.first->val;
    a=merge(s.first,merge(t.first,t.second));
    return res;
  }
  // 木を通りがけ順で出力
  vector<T> dump(node* a){
    vector<T> v(count(a));
    dump(a,v.begin());
    return v;
  }
  void dump(node* a,typename vector<T>::iterator it){
    if(!count(a)) return;
    a=eval(a);
    dump(a->l,it);
    *(it+count(a->l))=a->val;
    dump(a->r,it+count(a->l)+1);
  }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "oldcode/rbst_new.cpp"
template<typename T,typename E>
struct RBST {
  int xor128() {
    static int x = 123456789;
    static int y = 362436069;
    static int z = 521288629;
    static int w = 88675123; 
    int t;
   
    t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
  }
  using F = function<T(T,T)>;
  using G = function<T(T,E)>;
  using H = function<E(E,E)>;

  F f;
  G g;
  H h;
  T ti;
  E ei;
  
  struct node {
    node *lch,*rch;
    int cnt;
    T val,dat;
    E lazy;
    node() {}
    node(T val, E l) :
      cnt(1), val(val), dat(val), lazy(l) { lch=rch=nullptr; }
  };

  vector<node> pool;
  int ptr;

  RBST(int n, F f, G g, H h, T ti, E ei) :
    f(f), g(g), h(h), ti(ti), ei(ei), pool(n), ptr(0) {}

  // vector v で初期化
  node* build(int l,int r,vector<T> &v) {
    if(l+1 == r) return create(v[l]);
    int m = (l+r)/2;
    return merge(build(l,m,v), build(m,r,v));
  }
  node* build(vector<T> &v) {
    return build(0, v.size(), v);
  }
  // 事前に作っておいたnodeから取ってくる
  inline node* create(){
    return &pool[ptr++];
  }
  inline node* create(T v){
    return &(pool[ptr++] = node(v, ei));
  }
  // cnt,datへのアクセス
  inline int count(const node* a) {
    if(a == nullptr) return 0;
    return a->cnt;
  }
  inline T query(const node *a) {
    if(a == nullptr) return ti;
    return a->dat;
  }
  // node aの値を正しくする
  inline node* update(node* a){
    if(a == nullptr) return a;
    a->cnt = count(a->lch) + count(a->rch) + 1;
    a->dat = f(query(a->lch), f(a->val, query(a->rch)));
    return a;
  }
  // 遅延評価
  node* eval(node* a){
    if(a->lazy != ei){ 
      a->val = g(a->val, a->lazy);
      if(a->lch != nullptr){
        a->lch->lazy = h(a->lch->lazy, a->lazy);
        a->lch->dat = g(a->lch->dat, a->lazy);
      }
      if(a->rch != nullptr){
        a->rch->lazy = h(a->rch->lazy, a->lazy);
        a->rch->dat = g(a->rch->dat, a->lazy);
      }
      a->lazy = ei;
    }
    return update(a);
  }
  // pos番目に挿入
  inline node* insert(node* a, int pos, T v){
    node* b = create(v);
    auto s = split(a,pos);
    return a = merge(merge(s.first,b),s.second);
  }
  // pos番目を削除
  inline node* erase(node* a,int pos){
    auto s = split(a, pos);
    auto t = split(s.second, 1);
    return merge(s.first, t.second);
  }
  // node a, bを併合
  node* merge(node* a,node* b){
    if(a == nullptr) return b;
    if(b == nullptr) return a;
    if(xor128() % (count(a)+count(b)) < count(a)){
      a = eval(a);
      a->rch = merge(a->rch,b);
      return update(a);
    }
    b = eval(b);
    b->lch = merge(a,b->lch);
    return update(b);
  }
  // [0,k)[k,n) で分割
  pair<node*, node*> split(node* a,int k){
    if(a==nullptr) return make_pair(a,a);
    a=eval(a);
    if(k<=count(a->lch)){
      auto s=split(a->lch,k);
      a->lch=s.second;
      return make_pair(s.first,update(a));
    }
    auto s=split(a->rch,k-(count(a->lch)+1));
    a->rch=s.first;
    return make_pair(update(a),s.second);
  } 
  // [l,r)
  inline T query(node *&a, int l, int r){
    auto s=split(a,l);
    auto t=split(s.second,r-l);
    auto u=t.first;
    T res=query(u);
    a=merge(s.first,merge(t.first,t.second));
    return res;
  }
  // [l,r)
  inline void update(node *&a,int l,int r,E v){
    auto s=split(a,l);
    auto t=split(s.second,r-l);
    auto u=t.first;
    u->lazy=h(u->lazy,v);
    a=merge(merge(s.first,eval(u)),t.second);
  }
  // p番目
  inline T get(node *&a,int p){
    auto s=split(a,p);
    auto t=split(s.second,1);
    T res=t.first->val;
    a=merge(s.first,merge(t.first,t.second));
    return res;
  }
  // 木を通りがけ順で出力
  vector<T> dump(node* a){
    vector<T> v(count(a));
    dump(a,v.begin());
    return v;
  }
  void dump(node* a,typename vector<T>::iterator it){
    if(!count(a)) return;
    a=eval(a);
    dump(a->l,it);
    *(it+count(a->l))=a->val;
    dump(a->r,it+count(a->l)+1);
  }
};
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

