#include <bits/stdc++.h>

using namespace std;
using ll = long long;
// #define int ll
using PII = pair<ll, ll>;

#define FOR(i, a, n) for (ll i = (ll)a; i < (ll)n; ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(x) x.begin(), x.end()

template<typename T> T &chmin(T &a, const T &b) { return a = min(a, b); }
template<typename T> T &chmax(T &a, const T &b) { return a = max(a, b); }
template<typename T> bool IN(T a, T b, T x) { return a<=x&&x<b; }
template<typename T> T ceil(T a, T b) { return a/b + !!(a%b); }

template<typename T> vector<T> make_v(size_t a) { return vector<T>(a); }
template<typename T,typename... Ts>
auto make_v(size_t a,Ts... ts) {
    return vector<decltype(make_v<T>(ts...))>(a,make_v<T>(ts...));
}
template<typename T,typename V> typename enable_if<is_class<T>::value==0>::type
fill_v(T &t, const V &v) { t=v; }
template<typename T,typename V> typename enable_if<is_class<T>::value!=0>::type
fill_v(T &t, const V &v ) { for(auto &e:t) fill_v(e,v); }

template<class S,class T>
ostream &operator <<(ostream& out,const pair<S,T>& a) {
    out<<'('<<a.first<<','<<a.second<<')'; return out;
}
template<class T>
ostream &operator <<(ostream& out,const vector<T>& a){
    out<<'[';
    for(const T &i: a) out<<i<<',';
    out<<']';
    return out;
}
template<class T>
ostream &operator <<(ostream& out, const set<T>& a) {
    out<<'{';
    for(const T &i: a) out<<i<<',';
    out<<'}';
    return out;
}
template<class T, class S>
ostream &operator <<(ostream& out, const map<T,S>& a) {
    out<<'{';
    for(auto &i: a) out<<i<<',';
    out<<'}';
    return out;
}

int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0}; // DRUL
const int INF = 1<<30;
const ll LLINF = 1LL<<60;
const ll MOD = 1000000007;

template<class T, int primitive_root>
struct NTT {
    void ntt(vector<T>& a, int sign) {
        const int n = a.size();
        assert((n^(n&-n)) == 0);
        T g = 3; //g is primitive root of mod
        const ll mod = T::mod();
		T h = g.pow((mod-1)/n); // h^n = 1
		if(sign == -1) h = h.inv(); //h = h^-1 % mod
		//bit reverse
		int i = 0;
		for (int j = 1; j < n - 1; ++j) {
			for (int k = n >> 1; k >(i ^= k); k >>= 1);
			if (j < i) swap(a[i], a[j]);
		}
		for (int m = 1; m < n; m *= 2) {
			const int m2 = 2 * m;
			const T base = h.pow(n/m2);
			T w = 1;
            for(int x=0; x<m; ++x) {
				for (int s = x; s < n; s += m2) {
					T u = a[s];
					T d = a[s + m] * w;
					a[s] = u + d;
					a[s + m] = u - d;
				}
				w *= base;
			}
		}
    }
    void ntt(vector<T>& input) { ntt(input, 1); }
    void inv_ntt(vector<T>& input) {
        ntt(input, -1);
        const T n_inv = T((int)input.size()).inv();
        for(auto &x: input) x *= n_inv;
    }
    vector<T> convolution(const vector<T>& a, const vector<T>& b) {
        int sz = 1;
        while(sz < (int)a.size() + (int)b.size()) sz *= 2;
        vector<T> a2(a), b2(b);
        a2.resize(sz); b2.resize(sz);
        ntt(a2); ntt(b2);
        for(int i=0; i<sz; ++i) a2[i] *= b2[i];
        inv_ntt(a2);
        return a2;
    }
};

template<class T>
vector<T> any_mod_convolution(vector<T> a, vector<T> b) {
    const ll m1 = 167772161, m2 = 469762049, m3 = 1224736769;
    NTT<modint<m1>,3> ntt1;
    NTT<modint<m2>,3> ntt2;
    NTT<modint<m3>,3> ntt3;
    vector<modint<m1>> a1(a.size()), b1(b.size());
    vector<modint<m2>> a2(a.size()), b2(b.size());
    vector<modint<m3>> a3(a.size()), b3(b.size());
    for(int i=0; i<(int)a.size(); ++i) a1[i] = a[i].x, b1[i] = b[i].x;
    for(int i=0; i<(int)a.size(); ++i) a2[i] = a[i].x, b2[i] = b[i].x;
    for(int i=0; i<(int)a.size(); ++i) a3[i] = a[i].x, b3[i] = b[i].x;
    auto x = ntt1.convolution(a1, b1);
    auto y = ntt2.convolution(a2, b2);
    auto z = ntt3.convolution(a3, b3);
    const ll m1_inv_m2 = 104391568;
    const ll m12_inv_m3 = 721017874;
    const ll m12_mod = m1 * m2 % T::mod();
    vector<T> ret(x.size());
    for(int i=0; i<(int)x.size(); ++i) {
        ll v1 = (y[i].x-x[i].x) * m1_inv_m2 % m2;
        if(v1<0) v1 += m2;
        ll v2 = (z[i].x-(x[i].x+m1*v1)%m3) * m12_inv_m3 % m3;
        if(v2<0) v2 += m3;
        ret[i] = x[i].x + m1*v1 + m12_mod*v2;
    }
    return ret;
}