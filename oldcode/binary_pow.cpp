ll binpow(ll x, ll e) {
  ll ret = 1, p = x;
  while(e > 0) {
    if(e&1) {(ret *= p) %= MOD; e--;}
    else {(p *= p) %= MOD; e /= 2;} 
  }
  return ret;
}

// ダブリング O(funcの計算量*log(e))
template<typename T=ll, typename F=function<T(T,T)>>
T binpow(T x, ll e, F func=[](T a, T b){return a*b%MOD;}, T d=1) {
  T ret = d, p = x;
  while(e > 0) {
    if(e&1) {ret = func(ret, p); e--;}
    else {p = func(p, p); e /= 2;} 
  }
  return ret;
};