// 更新が区間chmin クエリが区間和と区間max

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
// #define int ll
using PII = pair<ll, ll>;

#define FOR(i, a, n) for (ll i = (ll)a; i < (ll)n; ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(x) x.begin(), x.end()

template<typename T> T &chmin(T &a, const T &b) { return a = min(a, b); }
template<typename T> T &chmax(T &a, const T &b) { return a = max(a, b); }
template<typename T> bool IN(T a, T b, T x) { return a<=x&&x<b; }
template<typename T> T ceil(T a, T b) { return a/b + !!(a%b); }

template<typename T> vector<T> make_v(size_t a) { return vector<T>(a); }
template<typename T,typename... Ts>
auto make_v(size_t a,Ts... ts) {
    return vector<decltype(make_v<T>(ts...))>(a,make_v<T>(ts...));
}
template<typename T,typename V> typename enable_if<is_class<T>::value==0>::type
fill_v(T &t, const V &v) { t=v; }
template<typename T,typename V> typename enable_if<is_class<T>::value!=0>::type
fill_v(T &t, const V &v ) { for(auto &e:t) fill_v(e,v); }

template<class S,class T>
ostream &operator <<(ostream& out,const pair<S,T>& a){
    out<<'('<<a.first<<','<<a.second<<')'; return out;
}
template<typename T>
istream& operator >> (istream& is, vector<T>& vec){
    for(T& x: vec) {is >> x;} return is;
}
template<class T>
ostream &operator <<(ostream& out,const vector<T>& a){
    out<<'['; for(T i: a) {out<<i<<',';} out<<']'; return out;
}

int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0}; // DRUL
const int INF = 1<<30;
const ll LLINF = 1LL<<60;
const ll MOD = 1000000007;

template<typename dat_type, typename lazy_type>
struct segtree {
    ll n;
    vector<dat_type> dat;
    dat_type dat_d; 
    vector<lazy_type> lazy;
    lazy_type lazy_d;

    using F = function<dat_type(dat_type,dat_type)>;
    F merge_dat;

    segtree() {}
    segtree(int n_, F md, dat_type dd, ll ld) 
        : dat_d(dd), lazy_d(ld), merge_dat(md) 
    {
        n = 1; while(n < n_) n *= 2;
        dat.assign(n*2-1, dat_d);
        lazy.assign(n*2-1, lazy_d);
    }

    void eval(int k, int l, int r) {
        if(lazy[k] == lazy_d) return;
        // dat[k] に lazy[k] を作用させる
        if(dat[k].max > lazy[k]) {
            dat[k].sum -= (dat[k].max - lazy[k]) * dat[k].cnt;
            dat[k].max = lazy[k];
        }
        if(k*2+1 < n*2-1) {
            // lazy[k] を下に伝播させる
            chmin(lazy[2*k+1], lazy[k]);
            chmin(lazy[2*k+2], lazy[k]);
        }
        lazy[k] = lazy_d;
    }

    void update(int a, int b, ll x, int k, int l, int r) {
        eval(k, l, r);
        // break_condition
        if(b <= l || r <= a || dat[k].max <= x) return;
        // tag_condition
        if(a <= l && r <= b && dat[k].second < x) {
            // lazyへ値を代入
            lazy[k] = x;
            eval(k, l, r);
            return;
        }
        int m = (l+r)>>1;
        update(a, b, x, 2*k+1, l, m);
        update(a, b, x, 2*k+2, m, r);
        dat[k] = merge_dat(dat[2*k+1], dat[2*k+2]);
    }
    void update(int a, int b, ll x) { update(a, b, x, 0, 0, n); }

    dat_type query(int a, int b, int k, int l, int r) {
        eval(k, l, r);
        if(b <= l || r <= a) return dat_d;
        if(a <= l && r <= b) return dat[k];

        int m=(l+r)>>1;
        dat_type vl = query(a, b, 2*k+1, l, m);
        dat_type vr = query(a, b, 2*k+2, m, r);
        return merge_dat(vl, vr);
    }
    dat_type query(int a, int b) { return query(a, b, 0, 0, n); }

    // デバッグ出力
    void debug() {
        cout << "---------------------" << endl;
        int cnt = 0;
        for(int i=1; i<=n; i*=2) {
        REP(j, i) {
            cout << "([" << dat[cnt].sum << "," << dat[cnt].max << "," << dat[cnt].second << "," <<  dat[cnt].cnt << "]," << lazy[cnt] << ") ";
            cnt++;
        }
        cout << endl;
        }
        cout << "---------------------" << endl;
    }
};

signed main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll t;
    cin >> t;

    struct node {
        ll sum, max, second, cnt;
        node(ll v=0) : sum(v), max(v), second(-LLINF), cnt(1) {}
    };
    auto merge_dat = [](node l, node r) {
        node ret;
        ret.sum = l.sum + r.sum;
        ret.max = max(l.max, r.max);
        if(ret.max == l.max && ret.max == r.max) {
            ret.second = max(l.second, r.second);
            ret.cnt = l.cnt + r.cnt;
        } else {
            ret.cnt = l.max > r.max ? l.cnt : r.cnt;
            ret.second = max({min(l.max, r.max), l.second, r.second});
        }
        assert(ret.max != ret.second);
        return ret;
    };

    while(t--) {
        ll n, m;
        cin >> n >> m;

        segtree<node,ll> seg(n, merge_dat, node(), LLINF);
        
        REP(i, n) {
            ll a;
            cin >> a;
            seg.dat[i+seg.n-1] = node(a);
        }
        for(int i=seg.n-2; i>=0; --i) {
            seg.dat[i] = merge_dat(seg.dat[i*2+1], seg.dat[i*2+2]);
        }
        REP(i, m) {
            ll t;
            cin >> t;
            if(t == 0) {
                ll l, r, x; 
                cin >> l >> r >> x;
                seg.update(l, r, x);
            } else if(t == 1) {
                ll l, r;
                cin >> l >> r;
                cout << seg.query(l, r).max << endl;
            } else if(t == 2) {
                ll l, r;
                cin >> l >> r;
                cout << seg.query(l, r).sum << endl;
            }
        }
    }

    return 0;
}
