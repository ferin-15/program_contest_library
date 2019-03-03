// LIS and LDS
// LISがA、LDSがBとなるような順列を構築しろ
// A + B <= N+1, AB >= N が構築できる必要十分条件
vector<ll> LISLDS(ll N, ll A, ll B) {
  vector<ll> res;
  for (ll i = B-1; i >= 0; --i) res.push_back(i);
  
  if (A == 1) return res;
  
  ll rem = N - B;
  ll p = rem / (A-1);
  ll r = rem % (A-1);
  
  ll b = r;
  ll c = A-1-r;
  
  for (ll i = 0; i < b; ++i) {
    ll size = res.size();
    for (ll j = 0; j < p+1; ++j) {
      res.push_back(size + p - j);
    }
  }
  for (ll i = 0; i < c; ++i) {
    ll size = res.size();
    for (ll j = 0; j < p; ++j) {
      res.push_back(size + p-1 - j);
    }
  }
  
  return res;
}