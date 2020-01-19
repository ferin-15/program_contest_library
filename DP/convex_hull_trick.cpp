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

// https://codeforces.com/contest/311/problem/B
namespace cf185div1B {
    ll d[100010], t[100010], T[100010], dp[105][100010];
    void solve() {
        ll n, m, p;
        cin >> n >> m >> p;
        REP(i, n-1) cin >> d[i+1];
        REP(i, n-1) d[i+1] += d[i];
        REP(i, m) {
            ll a, b;
            cin >> a >> b;
            t[i] = (b-d[a-1]);
        }
        sort(t, t+m);
        T[0] = t[0];
        REP(i, m-1) T[i+1] += T[i] + t[i+1];

        REP(i, m) dp[0][i] = (i+1)*t[i] - T[i];
        FOR(i, 1, p) {
            ConvexHullTrick cht;
            dp[i][0] = t[0] - T[0];
            cht.insert(0, dp[i-1][0] + T[0]);
            FOR(j, 1, m) {
                dp[i][j] = cht.incl_query(t[j]) + t[j]*j - T[j];
                cht.insert(-j, dp[i-1][j] + T[j]);
            }
        }

        cout << dp[p-1][m-1] << endl;
    }
}