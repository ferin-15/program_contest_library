#define __USE_MINGW_ANSI_STDIO 0
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define int ll
using VI = vector<int>;
using VVI = vector<VI>;
using PII = pair<int, int>;

#define FOR(i, a, n) for (ll i = (ll)a; i < (ll)n; ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(x) x.begin(), x.end()
#define PB push_back

const ll LLINF = (1LL<<60);
const int INF = (1LL<<30);
const int MOD = 1000000007;

template <typename T> T &chmin(T &a, const T &b) { return a = min(a, b); }
template <typename T> T &chmax(T &a, const T &b) { return a = max(a, b); }
template <typename T> bool IN(T a, T b, T x) { return a<=x&&x<b; }
template<typename T> T ceil(T a, T b) { return a/b + !!(a%b); }
template<class S,class T>
ostream &operator <<(ostream& out,const pair<S,T>& a){
  out<<'('<<a.first<<','<<a.second<<')';
  return out;
}
template<class T>
ostream &operator <<(ostream& out,const vector<T>& a){
  out<<'[';
  REP(i, a.size()) {out<<a[i];if(i!=a.size()-1)out<<',';}
  out<<']';
  return out;
}

int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

using ull = unsigned long long;
ull randxor(){
  static ull x=123456789,y=362436069,z=521288629,w=88675123;
  ull t=(x^(x<<11));
  x=y; y=z; z=w;
  return w=(w^(w>>19))^(t^(t>>8));
}

struct node {
  int val;
  node *ch[2];
  double pri;
  int cnt; //部分木のサイズ
  int sum; //部分木の値の和

  node(int v, double p): val(v),pri(p),cnt(1),sum(v) {
    ch[0] = ch[1] = nullptr;
  }
};

int count(node *t) {return t == nullptr ? 0: t->cnt;}
int sum(node *t) {return t == nullptr ? 0: t->sum;}

node *update(node *t) {
  t->cnt = count(t->ch[0]) + count(t->ch[1]) + 1;
  t->sum = sum(t->ch[0]) + sum(t->ch[1]) + t->val;
  return t;
}

// b=0で左回転、b=1で右回転
node *rotate(node *t, int b) {
  node *s = t->ch[1-b];
  t->ch[1-b] = s->ch[b];
  s->ch[b] = t;
  update(t);
  update(s);
  return s;
}

node *insert(node *t, int val, double pri) {
  if(t == nullptr) return new node(val, pri);
  else if(val == t->val) return t;
  else if(val < t->val) {
    t->ch[0] = insert(t->ch[0], val, pri);
    if(t->pri > t->ch[0]->pri) {
      t = rotate(t, 1);
    }
  } else{
    t->ch[1] = insert(t->ch[1], val, pri);
    if(t->pri > t->ch[1]->pri) {
      t = rotate(t, 0);
    }
  }
  return update(t);
}

node *erase(node *t, int x) {
  if (t->val == x) {
    if (t->ch[0] && t->ch[1]) {
      if (t->ch[0]->pri < t->ch[1]->pri) {
        t = rotate(t, 1);
        t->ch[1] = erase(t->ch[1], x);
        return update(t);
      } else {
        t = rotate(t, 0);
        t->ch[0] = erase(t->ch[0], x);
        return update(t);
      }
    } else {
      return t->ch[0] ? t->ch[0] : t->ch[1];
    }
  } else if (x < t->val) {
    t->ch[0] = erase(t->ch[0], x);
  } else {
    t->ch[1] = erase(t->ch[1], x);
  }
  return update(t);
}

int level(node *t, int k) {
  if(k < count(t->ch[0])) return level(t->ch[0], k);
  if(k == count(t->ch[0])) return t->val;
  return level(t->ch[1], k-count(t->ch[0])-1);
}

signed main(void)
{
  int q;
  cin >> q;

  node *root = nullptr;
  REP(i, q) {
    int t, x;
    cin >> t >> x;
    if(t == 1) {
      const int R = 100000;
      double r = randxor() % R / (double)R;
      // cout << r << endl;
      root = insert(root, x, r);
    } else {
      int k = level(root, x-1);
      root = erase(root, k);
      cout << k << endl;
    }
  }

  return 0;
}
