// 二分累乗 O(funcの計算量*logE)
template<typename T>
T binpow(T x, int e, auto func=[](T a, T b){return a*b%MOD;}, T d=1) {
  T ret = d, p = x;
  while(e > 0) {
    if(e%2 == 0) {p = func(p, p); e /= 2;}
    else {ret = func(ret, p); e--;}
  }
  return ret;
};