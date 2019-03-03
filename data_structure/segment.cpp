template <typename T>
struct segtree {
    int n;
    vector<T> dat;
    T d;
    using F = function<T(T,T)>;
    F f, g;

    segtree(int n_, F f_, F g_, T d_) : f(f_), g(g_), d(d_) {
        n = 1;
        while(n < n_) n *= 2;
        dat.assign(n*2, d); 
    }
    // [a, b)
    T query(int a, int b, int k, int l, int r) {
        if(r <= a || b <= l) return d;
        if(a <= l && r <= b) return dat[k];
        return f(query(a, b, 2*k+1, l, (l+r)/2),
                query(a, b, 2*k+2, (l+r)/2, r));
    }
    T query(int a, int b) {return query(a, b, 0, 0, n);}
    void update(int i, T v) {
        i += n-1;
        dat[i] = g(dat[i], v);
            while(i > 0) {
            i = (i-1)/2;
            dat[i] = f(dat[i*2+1], dat[i*2+2]);
        }
    }
    // デバッグ出力
    void debug() {
        cout << "---------------------" << endl;
        int cnt = 0;
        for(int i=1; i<=n; i*=2) {
            REP(j, i) {
                cout << dat[cnt] << " "; 
                cnt++;
            }
            cout << endl;
        }
        cout << "---------------------" << endl;
    }
};
/**
* 点更新区間min d=INF, f=min(a,b), g=b\n
* 点更新区間max d=-INF, f=max(a,b), g=b\n
* 点加算区間和  d=0, f=a+b, g+=b
*/
