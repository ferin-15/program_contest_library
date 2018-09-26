using C = complex<double>;

void dft(vector<C> &f, bool inv = false)
{
  const int n = f.size();
  const double PI = (inv ? -1 : 1) * acos(-1);
  for(int i=0, j=1; j+1<n; j++) {
    for(int k = n>>1; k>(i^=k); k>>=1);
    if(i>j) swap(f[i], f[j]);
  }

  C pow_zeta, zeta, a, b;
  for(int i=1; i<n; i<<=1) {
    zeta = polar(1.0, PI/i);
    for(int j=0; j<n; j+=i<<1) {
      pow_zeta = 1.0;
      for(int k=0; k<i; k++) {
        a = f[j+k],
        b = C(f[j+k+i].real()*pow_zeta.real()-f[j+k+i].imag()*pow_zeta.imag(),
              f[j+k+i].real()*pow_zeta.imag()+f[j+k+i].imag()*pow_zeta.real());
        f[j+k] = a+b, f[j+k+i] = a-b;
        pow_zeta *= zeta;
      }
    }
  }
  if(inv) {
    double temp = 1.0/n;
    REP(i, n) f[i] *= temp;
  }
}

// xとyの畳み込みを返す
VI multiply(VI x, VI y) {
  int n = 1;
  while(n < x.size()+y.size()-1) n <<= 1;
  vector<C> f(n), g(n);
  REP(i, x.size()) f[i] = x[i];
  REP(i, y.size()) g[i] = y[i];
  dft(f); dft(g);
  REP(i, n) f[i] *= g[i];
  dft(f, true);
  VI ret(x.size()+y.size()-1);
  REP(i, x.size()+y.size()-1) ret[i] = f[i].real() + 0.5;
  return ret;
}
