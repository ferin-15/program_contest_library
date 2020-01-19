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
        for(int x=i+1; x<(int)bit.size(); x += x&-x) bit[x] += w;
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

// https://atcoder.jp/contests/arc033/tasks/arc033_3
namespace arc033c {
    void solve() {
        ll q;
        cin >> q;
        BIT<ll> bit(200010);
        // lower_boundのverify用に+2とか変なことやってる
        while(q--) {
            ll t, x;
            cin >> t >> x;
            if(t == 1) {
                bit.update(x, 2);
            } else {
                ll val = bit.lower_bound(x*2-1);
                cout << val << endl;
                bit.update(val, -2);
            }
        }
    }
}