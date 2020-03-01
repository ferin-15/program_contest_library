// BEGIN CUT
// 根が1
template<typename Monoid>
struct segtree {
    using T = typename Monoid::T;
    int n;
    vector<T> dat;

    segtree(int n_) {
        n = 1;
        while(n < n_) n <<= 1;
        dat.assign(n*2, Monoid::id());
    }
    void build(vector<T> v) {
        REP(i, v.size()) dat[i+n] = v[i];
        for(int i=n-1; i>0; --i) dat[i] = Monoid::op(dat[i*2], dat[i*2+1]);
    }

    T query(int a, int b) {
        if(a >= b) return Monoid::id();
        T l = Monoid::id(), r = Monoid::id();
        for(a+=n, b+=n; a<b; a>>=1, b>>=1) {
            if(a&1) l = Monoid::op(l, dat[a++]);
            if(b&1) r = Monoid::op(dat[--b], r);
        }
        return Monoid::op(l, r);
    }
    void update(int i, T v) {
        i += n;
        dat[i] = v;
        while(i >>= 1) {
            dat[i] = Monoid::op(dat[i*2], dat[i*2+1]);
        }
    }

    friend ostream &operator <<(ostream& out,const segtree<Monoid>& seg){
        out << "---------------------" << endl;
        int cnt = 1;
        for(int i=1; i<=seg.n; i*=2) {
            REP(j, i) {
                out << seg.dat[cnt] << " ";
                cnt++;
            }
            out << endl;
        }
        out << "---------------------" << endl;
        return out;
    }
};

template<typename Tp>
struct min_monoid {
    using T = Tp;
    static constexpr Tp id() { return INT_MAX; }
    static Tp op(const Tp &a, const Tp &b) { return min(a, b); }
};
template<typename Tp>
struct max_monoid {
    using T = Tp;
    static constexpr Tp id() { return -INF; }
    static Tp op(const Tp &a, const Tp &b) { return max(a, b); }
};
template<typename Tp>
struct sum_monoid {
    using T = Tp;
    static constexpr Tp id() { return 0; }
    static Tp op(const Tp &a, const Tp &b) { return a+b; }
};
// END CUT