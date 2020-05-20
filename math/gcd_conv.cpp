// BEGIN CUT
// g(x) = \sum_{yはxの倍数} f(y)
template<class T>
void fzt_div_upper(vector<T> &a) {
    const ll n = a.size();
    FOR(i, 1, n) {
        for(ll j=2*i; j<n; j+=i) {
            a[i] += a[j];
        }
    }
}
// f(y) = \sum_{yはxの倍数} g(x)
template<class T>
void fmt_div_upper(vector<T> &a) {
    const ll n = a.size();
    for(ll i=n-1; i>=1; --i) {
        for(ll j=2*i; j<n; j+=i) {
            a[i] -= a[j];
        }
    }
}
// c(z) = \sum_{gcd(x,y)=z} a(x)a(y)
template<class T>
void conv_gcd(vector<T> &a) {
    fzt_div_upper(a);
    REP(i, a.size()) a[i] *= a[i];
    fmt_div_upper(a);
}
// END CUT