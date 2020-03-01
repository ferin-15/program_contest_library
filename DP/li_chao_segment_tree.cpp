// BEGIN CUT
// 単調性なしok 動的CHT 各操作O(logN)
template <typename T, const T id = numeric_limits<T>::min()>
class ConvexHullTrick {
private:
    struct line {
        T a, b;
        line(T a_ = 0, T b_ = 0) : a(a_), b(b_) {}
        // ll でも overflow するのに注意
        T get(T x) { return a * x + b; }
    };
    struct node {
        line l;
        node *lch, *rch;
        node(line l_) : l(l_), lch(nullptr), rch(nullptr) {}
    };

    const T minx, maxx;
    node *root = nullptr;

    // [lb, ub]
    node* update(node *p, ll lb, ll ub, line& l) {
        if (!p) return new node(l);
        if (p->l.get(lb) >= l.get(lb) && p->l.get(ub) >= l.get(ub)) return p;
        if (p->l.get(lb) <= l.get(lb) && p->l.get(ub) <= l.get(ub)) {
          p->l = l;
          return p;
        }
        ll mid = (lb + ub) / 2;
        if (p->l.get(mid) < l.get(mid)) swap(p->l, l);
        if (p->l.get(lb) <= l.get(lb)) p->lch = update(p->lch, lb, mid, l);
        else p->rch = update(p->rch, mid + 1, ub, l);
        return p;
    }
    // [lb, ub]
    T query(node *p, ll lb, ll ub, ll t) const {
        if(!p) return id;
        if(ub == lb) return p->l.get(t);
        ll mid = (lb+ub)/2;
        if(t <= mid) return max(p->l.get(t), query(p->lch, lb, mid, t));
        return max(p->l.get(t), query(p->rch, mid + 1, ub, t));
    }
public:
    // getで呼び出しうるxの範囲を指定
    ConvexHullTrick(const T minx_, const T maxx_) : minx(minx_), maxx(maxx_) {}
    // 直線ax+bを追加 最小がほしければ-ax-bを渡してgetの結果に×(-1)する
    void insert(T a, T b) {
        line l(a, b);
        root = update(root, minx, maxx, l);
    }
    // ax+b のうち最大のものを返す
    T get(T x) const { return query(root, minx, maxx, x); }
};
// END CUT