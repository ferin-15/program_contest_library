// BEGIN CUT
template<ll MOD, ll B>
struct rollingHash{
    vector<ll> hash,p;
    rollingHash(){}
    rollingHash(const string &s){
        const int n=s.size();
        hash.assign(n+1,0); p.assign(n+1,1);
        for(int i=0;i<n;i++){
            hash[i+1]=(hash[i]*B+s[i])%MOD;
            p[i+1]=p[i]*B%MOD;
        }
    }
    // [l,r)
    ll get(int l,int r){
        ll res=hash[r]+MOD-hash[l]*p[r-l]%MOD;
        return res>=MOD?res-MOD:res;
    }
};
// END CUT