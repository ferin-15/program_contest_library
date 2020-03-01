// BEGIN CUT
struct BIT {
    int n;
    vector<ll> bit;
    BIT(int sz) { 
        n=1; while(n < sz) n*=2;
        bit.assign(n+1, 0); 
    }
    void update(int i, ll w) {
        for(int x=i+1; x<(int)bit.size(); x += x&-x) bit[x] += w;
    }
    // [0,i]
    ll query(int i) {
        ll ret = 0;
        for(int x=i+1; x>0; x -= x&-x) ret += bit[x];
        return ret;
    }
    // 合計がw以上の最小の位置
    int lower_bound(ll w) {
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
// END CUT