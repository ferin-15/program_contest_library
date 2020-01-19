template <typename S>
struct sparseTable {
    using T = typename S::T;
    int n;
    vector<int> log2;
    vector<vector<T>> t;

    sparseTable(int nn) {
        n = nn;
        log2.assign(n+1, 0);
        for(int i=2; i<=n; ++i) log2[i] = log2[i >> 1] + 1;
        t = vector<vector<T>>(log2[n]+1, vector<T>(n));
    }
    void init(vector<T> v) {
        for(int i=0; i<n; ++i) t[0][i] = v[i];
        for(int j=1; j<=log2[n]; ++j) {
            int w = 1LL<<(j-1);
            for (int i = 0; i+(w<<1) <= n; ++i) {
                t[j][i] = S::op(t[j-1][i], t[j-1][i+w]);
            }
        }
    }
    // [l, r]
    T query(int l, int r) {
        int j = log2[r - l];
        return S::op(t[j][l], t[j][r-(1 << j)+1]);
    }
};

// 集合T、結合則・可換・冪等律が成り立つ二項演算op
struct minnimum {
    using T = ll;
    static T op(const T& a, const T& b) { return min(a, b); }
};
struct maximum {
    using T = ll;
    static T op(const T& a, const T& b) { return max(a, b); }
};
struct gcd_op {
    using T = ll;
    static T op(const T& a, const T& b) { return __gcd(a, b); }
};
