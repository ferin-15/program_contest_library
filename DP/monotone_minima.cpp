/**
* @file monotone_minima.cpp
* @brief monotone minima
* @detail verify: https://beta.atcoder.jp/contests/colopl2018-final-open/tasks/colopl2018_final_c
* @author ferin
*/

// BEGIN CUT
const int MAX_N = 200010;
int minima[MAX_N]; // minima[i] = argmin_j f(i, j)
int a[MAX_N];

int f(int i, int j) { return a[j] + (j-i)*(j-i); }
// 開区間なのでmonotoneMinima(0, n-1, 0, n-1) と呼び出す
void monotoneMinima(int ib, int ie, int jb, int je) {
  if(ib > ie) return;
  if(ib == ie) {
    int jm = jb;
    int fm = f(ib, jm), fj;
    for(int j=jb+1; j<=je; ++j) {
      if(fm > (fj = f(ib, j))) {
        fm = fj;
        jm = j;
      }
    }
    minima[ib] = jm;
    return;
  }
  int im = (ib+ie)/2;
  monotoneMinima(im, im, jb, je);
  monotoneMinima(ib, im-1, jb, minima[im]);
  monotoneMinima(im+1, ie, minima[im], je);
}
// END CUT
