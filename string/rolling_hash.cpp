// BEGIN CUT
class rollingHash {
private:
    static constexpr ll mod = (1LL<<61) - 1;
    static ll base;
    vector<ll> hash, p;

    ll mul(ll a, ll b) {
        ll au = a>>31, ad = a & ((1LL<<31)-1);
        ll bu = b>>31, bd = b & ((1LL<<31)-1);
        ll mid = ad*bu+au*bd, midu = mid>>30, midd = mid & ((1LL<<30)-1);
        return au*bu*2 + midu + (midd<<31) + ad*bd;
    }
    ll calcmod(ll x) {
        ll ret = (x>>61) + (x & mod);
        if(ret >= mod) ret -= mod;
        return ret;
    }

public:
    rollingHash(const string &s) : hash(s.size()+1), p(s.size()+1, 1) {
        if(base == -1) base = rnd(2, 100000);
        REP(i, s.size()) {
            hash[i+1] = calcmod(mul(hash[i], base)+s[i]);
            p[i+1] = calcmod(mul(p[i], base));
        }
    }
    // [l,r)
    ll get(int l,int r) {
        return calcmod(hash[r] + 3*mod - mul(hash[l], p[r-l]));
    }
    ll concat(ll h1, ll h2, ll h2len) {
        return calcmod(mul(h1, p[h2len]) + h2);
    }
};
ll rollingHash::base = -1;
// END CUT