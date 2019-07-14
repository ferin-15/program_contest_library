// mの素因数分解をする O(sqrt(m) + loglog(m))
vector<PII> primeFactorization(ll m) {
    vector<PII> ret;
    for(ll i=2; i*i<=m; ++i) {
        ll cnt = 0;
        while(m%i==0) {
            m /= i;
            cnt++;
        }
        if(cnt) ret.emplace_back(i, cnt);
    }
    if(m > 1) ret.emplace_back(1, m);
    return ret;
}