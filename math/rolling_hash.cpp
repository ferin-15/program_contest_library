struct rollingHash {
    // MOD と 基数
    ll base[2] = {1009, 1007};
    using P = pair<modint<1000000007>, modint<1000000009>>;
    vector<P> hash, power;

    rollingHash() {}
    rollingHash(string s) : hash(s.size()), power(s.size()) {
        init(s);
    }

    // O(|S|)
    void init(string s) {
        power[i].first = power[i].second = 1;
        FOR(i, 1, s.size()) {
            power[i].first = power[i-1].first * base[0];
            power[i].second = power[i-1].second * base[1];
        }

        hash[0].first = hash[0].second = s[i]-'a';
        FOR(i, 1, s.size()) {
            hash[i].first = hash[i-1].first+power[i].first*(s[i]-'a');
            hash[i].second = hash[i-1].second+power[i].second*(s[i]-'a');
        }
    }

    // [l1, r1) と [l2, r2) が一致するかの判定 (l1 < l2)
    bool equal(int l1, int r1, int l2, int r2) {
        REP(i, 2) {
            ll a = (((hash[i][r1]-hash[i][l1])%mo[i])+mo[i])%mo[i];
            ll b = (((hash[i][r2]-hash[i][l2])%mo[i])+mo[i])%mo[i];
            if(a*power[i][l2-l1]%mo[i] == b) return true;
        }
        return false;
    }
};
