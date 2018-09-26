// BEGIN CUT
// 直線の傾きに単調性があるときのCHT O(n)
// 最大なら <= になる
class ConvexHullTrick {
public:
  deque<PII> que;
  // ax + b を追加
  void add(int a, int b) {
    PII p(a, b);
    while(que.size() >= 2 && check(que[que.size()-2], que.back(), p)) {
      que.pop_back();
    }
    que.PB(p);
  }
  // 単調性がある xの位置での最小のy
  int incl_query(int x) {
    assert(que.size());
    while(que.size() >= 2 && f(que[0],x) >= f(que[1],x)) {
      que.pop_front();
    }
    return que[0].first * x + que[0].second;
  }
  // 単調性なし
  int query(int x) {
    int lb = -1, ub = que.size()-2;
    while(ub-lb > 1) {
      int mid = (lb+ub)/2;
      if(isright(que[mid], que[mid+1], x)) lb = mid;
      else ub = mid;
    }
    return f(que[ub], x);
  }

  bool isright(const PII &p1, const PII &p2, int x) {
    return (p1.second-p2.second) >= x * (p2.first-p1.first);
  }
  bool check(const PII &a, const PII &b, const PII &c) {
    return (b.first-a.first)*(c.second-b.second)>=(b.second-a.second)*(c.first-b.first);
  }
  int f(const PII &p, int x) {
    return p.first * x + p.second;
  }
};
// END CUT
