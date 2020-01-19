// 最小を求めてるので最大ならinsert(-a,-b), -get(x)
struct ConvexHullTrick {
    deque<PII> que;

    bool isright(const PII &p1, const PII &p2, int x) {
        return (p1.second-p2.second) >= x * (p2.first-p1.first);
    }
    bool check(const PII &a, const PII &b, const PII &c) {
        return (b.first-a.first)*(c.second-b.second)>=(b.second-a.second)*(c.first-b.first);
    }
    ll f(const PII &p, ll x) { return p.first * x + p.second; }

    // ax + b を追加
    void insert(ll a, ll b) {
        PII p(a, b);
        while(que.size() >= 2 && check(que[que.size()-2], que.back(), p)) {
            que.pop_back();
        }
        que.push_back(p);
    }
    // 単調性がある xの位置での最小のy
    ll incl_query(ll x) {
        assert(que.size());
        while(que.size() >= 2 && f(que[0],x) >= f(que[1],x)) {
            que.pop_front();
        }
        return que[0].first * x + que[0].second;
    }
    // 単調性なし
    ll query(ll x) {
        ll lb = -1, ub = (ll)que.size()-1;
        while(ub-lb > 1) {
            ll mid = (lb+ub)/2;
            if(isright(que[mid], que[mid+1], x)) lb = mid;
            else ub = mid;
        }
        return f(que[ub], x);
    }
};