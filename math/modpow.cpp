// BEGIN CUT
ll modpow(ll x, ll y, ll m) {
    ll a = 1, p = x;
    while(y > 0) {
        if(y%2 == 0) {p = (p*p) % m; y /= 2;}
        else {a = (a*p) % m; y--;}
    }
    return a;
}
// END CUT