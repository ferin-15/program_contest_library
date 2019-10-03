template <typename T>
struct segtree {
    using F = function<T(T,T)>;
    int n;
    vector<T> dat;
    F f, g;
    T d;

    segtree(int n_, F f_, F g_, T d_) : f(f_), g(g_), d(d_) {
        n = 1;
        while(n < n_) n *= 2;
        dat.assign(n*2, d);
    }
    void build(vector<T> v) {
        REP(i, v.size()) dat[i+n-1] = v[i];
        for(int i=n-2; i>=0; --i) dat[i] = f(dat[i*2+1], dat[i*2+2]);
    }

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
* 点更新区間min d=INF, f=min(a,b), g=b
* 点更新区間max d=-INF, f=max(a,b), g=b
* 点加算区間和  d=0, f=a+b, g+=b
*/
