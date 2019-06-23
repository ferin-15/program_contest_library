struct rollingHash {
    // MOD と 基数
    ll mo[2] = {1000000007, 1000000009};
    ll base[2] = {1009, 1007};
    vector<ll> hash[2], power[2];

    rollingHash() {}
    rollingHash(string s) {
        hash[0].resize(s.size()+1); hash[1].resize(s.size()+1);
        power[0].resize(s.size()+1); power[1].resize(s.size()+1);
        init(s);
    }

    inline ll mul(ll a, ll b, ll md) const {
        return a * b % md;
        // unsigned long long y = a*b;
        // unsigned xh = (unsigned)(y>>32), xl = (unsigned)y, d, m;
        // asm(
        //     "divl %4; \n\t"
        //     : "=a" (d), "=d" (m)
        //     : "d" (xh), "a" (xl), "r" (md)
        // );
        // return a;
    }

    // O(|S|)
    void init(string s) {
        REP(i, 2) {
            power[i][0] = 1;
            FOR(j, 1, s.size()) power[i][j] = mul(power[i][j-1], base[i], mo[i]);
        }
        // 1-indexの累積和
        REP(i, 2) REP(j, s.size()) {
            hash[i][j+1] = (hash[i][j]+mul(power[i][j], s[j]-'a'+1, mo[i]))%mo[i];
        }
    }

    // [l1,r1) と [l2,r2) が一致するか
    bool equal(int l1, int r1, int l2, int r2) {
        REP(i, 2) {
            ll a = (hash[i][r1]-hash[i][l1]+mo[i])%mo[i];
            ll b = (hash[i][r2]-hash[i][l2]+mo[i])%mo[i];
            if(mul(a,power[i][l2-l1],mo[i]) != b) return false;
        }
        return true;
    }
};
