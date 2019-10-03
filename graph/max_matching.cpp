ll max_matching(ll n, vector<PII> edges) {
    mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<ll> dist(1, MOD-1);

    matrix mat(n, n);
    for(auto e: edges) {
        ll r = dist(mt);
        mat.get(e.first, e.second) = r;
        mat.get(e.second, e.first) = MOD-r;
    }
    return (gauss_jordan(mat)+1)/2;
}