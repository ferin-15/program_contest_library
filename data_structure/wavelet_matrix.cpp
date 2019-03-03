template<int N>
struct FID {
  static const int bucket = 512, block = 16;
  static char popcount[];
  int n;
  array<int, N/bucket+10> large;
  array<unsigned short, N/block+10> small, bs;

  // 初期化 O(2^16 + n)
  FID(){}
  FID(int n, array<bool, N> s) : n(n) {
    if(!popcount[1]) REP(i, 1<<block) popcount[i] = __builtin_popcount(i);

    bs[0] = small[0] = 0;
    large[0] = 0;
    REP(i, n) {
      if(i%block == 0) {
        bs[i/block+1] = 0;
        if(i%bucket == 0) {
          large[i/bucket+1] = large[i/bucket];
          small[i/block+1] = small[i/block] = 0;
        }
        else small[i/block+1] = small[i/block];
      }
      bs[i/block] |= short(s[i])<<(i%block);
      small[i/block+1]  += s[i];
      large[i/bucket+1] += s[i];
    }
    if(n%bucket == 0) small[n/block] = 0;
  }

  // [0,r)のvalの個数 O(1)
  int rank(bool val, int r) {
    if(val) {
      char bitnum = popcount[bs[r/block]&((1<<(r%block))-1)];
      return large[r/bucket] + small[r/block] + bitnum;
    }
    return r-rank(1,r); 
  }
  // [l,r)のvalの個数 O(1)
  int rank(bool val, int l, int r) { return rank(val,r)-rank(val,l); }

  // i個目の値valの位置 O(logn)
  int select(bool val, int i) {
    if(i < 0 || rank(val,n) <= i) return -1;
    i++;
    int lb = 0, ub = n;
    while(ub-lb>1) {
      int mid = (lb+ub)>>1;
      if(rank(val,mid) >= i) ub = mid;
      else lb = mid;
    }
    return ub-1;
  }
  int select(bool val, int i, int l) { return select(val,i+rank(val,l)); }

  // bit列のi番目 O(1)
  bool operator[](int i) { return bs[i/block]>>(i%block)&1; }
};
template<int N> char FID<N>::popcount[1<<FID<N>::block];

template<class T, int N, int LEVEL>
struct wavelet {
  int n;
  array<int, LEVEL> zs;
  array<FID<N>, LEVEL> dat;

  wavelet(int n, array<T, N> seq) : n(n) {
    array<T, N> f, l, r;
    array<bool, N> b;
    copy(seq.begin(), seq.begin()+n, f.begin());
    REP(d, LEVEL) {
      int lh = 0, rh = 0;
      REP(i, n) {
        bool k = f[i]&1<<(LEVEL-d-1);
        if(k) r[rh++] = f[i];
        else l[lh++] = f[i];
        b[i] = k;
      }
      dat[d] = FID<N>(n,b);
      zs[d] = lh;
      swap(l,f);
      copy(r.begin(), r.begin()+rh, f.begin()+lh);
    }
  }

  // i番目の要素をgetする
  T get(int i) {
    T ret = 0;
    REP(d, LEVEL) {
      ret <<= 1;
      bool b = dat[d][i];
      ret |= b;
      i = dat[d].rank(b,i) + b*zs[d]; // (b?zs[d]:0)
    }
    return ret;
  }
  T operator[](int i) { return get(i); }

  // [l,r)にvalが何個あるか O(LEVEL)
  int rank(T val, int l, int r) {
    REP(d, LEVEL) {
      bool b = val&1<<(LEVEL-d-1);
      l = dat[d].rank(b,l) + b*zs[d];
      r = dat[d].rank(b,r) + b*zs[d];
    }
    return r-l;
  }

  // k番目のvalの位置
  int select(T val, int k) {
    array<int, LEVEL> ls, rs;
    int l=0, r=n;
    REP(d, LEVEL) {
      ls[d] = l, rs[d] = r;
      bool b = val&1<<(LEVEL-d-1);
      l = dat[d].rank(b, l) + b*zs[d];
      r = dat[d].rank(b, r) + b*zs[d];
    }
    for(int d=LEVEL-1; d>=0; --d) {
      bool b = val&1<<(LEVEL-d-1);
      k = dat[d].select(b,k,ls[d]);
      if(k >= rs[d] || k < 0) return -1;
    }
    return k;
  }
  // [l,n)でk番目のval
  int select(T val, int k, int l) { return select(val, k+rank(val,0,l)); }

  // [l,r)で小さい(大きい)方からk番目(0-index)の要素を返す
  template<bool ascending=true>
  T kthnumber(int l, int r, int k) {
    if(r-l <= k || k < 0) return -1;
    T ret = 0;
    if(ascending) {
      REP(d, LEVEL) {
        int lc = dat[d].rank(0,l), rc = dat[d].rank(0,r);
        if(rc-lc > k) {
          l = lc;
          r = rc;
        } else {
          k -= rc-lc;
          l = l - lc + zs[d];
          r = r - rc + zs[d];
          ret |= 1ULL<<(LEVEL-d-1);
        }
      }
    } else {
      REP(d, LEVEL) {
        int lc = dat[d].rank(1,l), rc = dat[d].rank(1,r);
        if(rc-lc > k) {
          l = lc+zs[d];
          r = rc+zs[d];
          ret |= 1ULL<<(LEVEL-d-1);
        } else {
          k -= rc-lc;
          l -= lc;
          r -= rc;
        }
      }
    }
    return ret;
  }

  // [l,r)でx未満の要素数
  int rank_lt(int l, int r, T x) {
    int ret = 0;
    REP(d, LEVEL) {
      int lnum = dat[d].rank(1,l), rnum = dat[d].rank(1,r);
      if(x&1<<(LEVEL-d-1)) {
        ret += r-l-(rnum-lnum);
        l = zs[d] + lnum;
        r = zs[d] + rnum;
      } else {
        l -= lnum;
        r -= rnum;
      }
      if(l > r) assert(false);
    }
    return ret;
  }
  // [l,r)中でx以上y未満の要素
  int rangefreq(int l, int r, T x, T y) { 
    return rank_lt(l,r,y) - rank_lt(l,r,x);
  }
};
// ToDo: [l,r)で出現頻度が高い要素
// ToDo: [l,r)で大きい方からk個の和
// ToDo: 動的
// ToDo: verify select

signed main(void)
{
  cin.tie(0);
  ios::sync_with_stdio(false);

  int n, m;
  cin >> n >> m;
  array<int,100010> a;
  REP(i, n) cin >> a[i], a[i] += 1000000000;

  wavelet<int,100010,32> wave(n, a);
  REP(i, m) {
    int l, r, k;
    cin >> l >> r >> k; k--;
    cout << wave.kthnumber(l-1, r, k) - 1000000000 << endl;
  }

  return 0;
}
