#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2270
#include "../data_structure/Mo_Tree_Vertex.cpp"

template <typename T>
struct BIT {
    vector<T> bit;
    // 単位元
    const T neutral = 0;
    // 要素数
    int n;
    BIT(int n_ = 1e5) { init(n_); }
    void init(int sz) { 
        n=1; while(n < sz) n*=2;
        bit.assign(n+1, neutral); 
    }
    void update(int i, T w) {
        for(int x=i+1; x<bit.size(); x += x&-x) bit[x] += w;
    }
    // [0,i]
    T query(int i) {
        T ret = neutral;
        for(int x=i+1; x>0; x -= x&-x) ret += bit[x];
        return ret;
    }
    // 合計がw以上の最小の位置
    int lower_bound(T w) {
        int x = 0;
        for(int k=n; k>0; k>>=1) {
            if(x+k <= n && bit[x+k] < w) {
                w -= bit[x+k];
                x += k;
            }
        }
        return x;
    }
};

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n, q;
    cin >> n >> q;
    vector<ll> x(n);
    REP(i, n) cin >> x[i];
    
    vector<ll> vs(x);
    sort(ALL(vs));
    vs.erase(unique(ALL(vs)), vs.end());
    REP(i, n) x[i] = lower_bound(ALL(vs), x[i]) - vs.begin();

    BIT<ll> bit(vs.size());
    auto add = [&](ll idx) { bit.update(x[idx], 1); };
    auto del = [&](ll idx) { bit.update(x[idx], -1); };
    Mo_Tree_Vertex mo(n, add, del);

    REP(i, n-1) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        mo.add_edge(a, b);
    }
    mo.prepare();

    vector<ll> k(q);
    REP(i, q) {
        ll a, b;
        cin >> a >> b >> k[i];
        a--, b--;
        mo.insert(a, b);
    }
    mo.build();

    vector<ll> ans(q);
    REP(i, q) {
        ll idx = mo.process();
        ans[idx] = vs[bit.lower_bound(k[idx])];
    }
    REP(i, q) cout << ans[i] << "\n";
    cout << flush;

    return 0;
}