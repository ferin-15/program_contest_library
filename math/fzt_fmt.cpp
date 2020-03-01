// BEGIN CUT
// a.size() は2べき
// upper: g(S) = \sum_{S \subseteq T} f(T)
// lower: g(S) = \sum_{T \subseteq S} f(T)
template<bool upper>
vector<ll> fzt(vector<ll> a) {
    const int n = log2(a.size());
    REP(i, n) REP(j, 1LL<<n) {
        if(upper && !(j&1LL<<i)) a[j] += a[j|(1LL<<i)];
        else if(!upper && (j&1LL<<i)) a[j] += a[j^(1LL<<i)];
    }
    return a;
}
// a.size() は2べき
// upper: f(S) = \sum_{S \subseteq T} (-1)^(|T\S|) g(T)
// lower: f(S) = \sum_{T \subseteq S} (-1)^(|T\S|) g(T)
template<bool upper>
vector<ll> fmt(vector<ll> a) {
    const int n = log2(a.size());
    REP(i, n) REP(j, 1LL<<n) {
        if(upper && !(j&1LL<<i)) a[j] -= a[j|(1LL<<i)];
        else if(!upper && (j&1LL<<i)) a[j] -= a[j^(1LL<<i)];
    }
    return a;
}

// a.size(),b.size() は2べき
// c_k = \sum_{k = i & j} a_ib_j
vector<ll> convAND(vector<ll> a, vector<ll> b) {
    a = fzt<true>(a);
    b = fzt<true>(b);
    REP(i, a.size()) a[i] *= b[i];
    return fmt<true>(a);
}
// a.size(),b.size() は2べき
// c_k = \sum_{k = i | j} a_ib_j
vector<ll> convOR(vector<ll> a, vector<ll> b) {
    a = fzt<false>(a);
    b = fzt<false>(b);
    REP(i, a.size()) a[i] *= b[i];
    return fmt<false>(a);
}
// END CUT