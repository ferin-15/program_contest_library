// 前計算O(N) クエリO(1)
mint combi(ll N, ll K) {
    const int maxN=5e5; // !!!
    static mint fact[maxN+1]={},factr[maxN+1]={};
    if (fact[0]==0) {
        fact[0] = factr[0] = 1;
        FOR(i, 1, maxN+1) fact[i] = fact[i-1] * i;
        factr[maxN] = fact[maxN].inv();
        for(ll i=maxN-1; i>=0; --i) factr[i] = factr[i+1] * (i+1);
    }
    if(K<0 || K>N) return 0; // !!!
    return factr[K]*fact[N]*factr[N-K];
}

// 前計算O(Klog(mod)) クエリO(K)
mint combi_bigN(ll N, ll K) {
    const int maxN=5e5; // !!!
    static mint inv[maxN+1] = {};
    if(inv[0]==0) {
        inv[0] = 1;
        FOR(i, 1, maxN+1) inv[i] = mint(i).inv();
    }
    if(K<0 || K>N) return 0; // !!!
    mint ret = 1;
    for(;K>0;N--,K--) ret *= N, ret *= inv[K];
    return ret;
}
