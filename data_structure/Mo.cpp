// insertしてbuildしたあとprocessでクエリを進めていく
struct Mo {
  vector<int> left, right, order;
  vector<bool> used;
  int width;
  int nl, nr, ptr;
  using F = function<void(int)>;
  F add, del;

  inline void distribute(int idx) {
    used[idx].flip();
    if(used[idx]) add(idx);
    else del(idx);
  }

  Mo(int n, F a, F d) : width((int)sqrt(n)), nl(0), nr(0), ptr(0), used(n), add(a), del(d) {}

  // [l, r)
  void insert(int l, int r) {
    left.push_back(l);
    right.push_back(r);
  }
  void build() {
    order.resize(left.size());
    iota(ALL(order), 0);
    sort(ALL(order), [&](int a, int b) {
      if(left[a] / width != left[b] / width) return left[a] < left[b];
      return right[a] < right[b];
    });
  }
  // クエリを1つ進め、クエリのidを返す 
  int process() {
    if(ptr == order.size()) return -1;
    const auto id = order[ptr];
    while(nl > left[id]) distribute(--nl);
    while(nr < right[id]) distribute(nr++);
    while(nl < left[id]) distribute(nl++);
    while(nr > right[id]) distribute(--nr);
    return order[ptr++];
  }
};