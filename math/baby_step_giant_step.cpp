// BEGIN CUT
// x^k = y (mod m) となるkを求める O(sqrt(m))
ll baby_step_giant_step(ll x, ll y, ll m) {
    // Baby-step
    // mp[x^i] = i
    unordered_map<ll,ll> mp;
    mp[1] = 0;
    ll z = 1;
    const ll m_sqrt = sqrt(m)+1;
    REP(i, m_sqrt) {
        (z *= x) %= m;
        mp[z] = i+1;
    }
    if(mp.find(y) != mp.end()) return mp[y];

    // Giant-step 
    ll r = modpow(z, m-2, m);   // x^(-m_sqrt)
    FOR(i, 1, m_sqrt+1) {
        (y *= r) %= m;
        if(mp.find(y) != mp.end()) return mp[y] + i*m_sqrt;
    }

    return -1;
}
// END CUT