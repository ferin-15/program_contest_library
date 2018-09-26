区間更新区間max
  auto f = [](int l, int r){return min(l, r);};
  auto g = [](int l, int r){return r==INT_MAX?l:r;};
  auto h = [](int l, int r){return r==INT_MAX?l:r;};
  segtree<int,int> seg(n, f, g, h, INT_MAX, INT_MAX);
区間加算区間和
auto f = [](int l, int r){return l+r;};
auto g = [](int l, int r){return l+r;};
auto h = [](int l, int r){return l+r;};
auto p = [](int l, int r){return l*r;};
segtree<int,int> seg(n, f, g, h, 0, 0, p);
区間加算区間最小
auto f = [](int l, int r){return min(l,r);};
auto g = [](int l, int r){return l+r;};
auto h = [](int l, int r){return l+r;};
segtree<int,int> seg(n, f, g, h, 0, 0);
区間更新区間和
auto f = [](int a, int b){return a+b;};
auto g = [](int a, int b){return b==0?a:b;};
auto h = [](int a, int b){return b==0?a:b;};
auto p = [](int a, int b){return a*b;};
segtree<int,int> seg(n, f, g, h, 0, 0, p);
区間xor区間和
segtree<int, int> seg(n,
  [](int a, int b){return a+b;},
  [](int a, int b){return b>=1?b-a:a;},
  [](int a, int b){return a^b;},
  0, 0,
  [](int a, int b){return a*b;});
区間加算,更新　区間和
（クエリタイプ、値）
作用素をペアにするとできる
