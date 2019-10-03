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

// find:O(logN) unite:O(logN)
struct partialPersistentUF {
    const static int MAX_N = 100010;
    unordered_map<int, int> par[MAX_N];
    int rank[MAX_N];
    int fin[MAX_N];
    int idx;
    partialPersistentUF() { init(); }
    partialPersistentUF(int n) { init(n); }
    void init(int n=MAX_N) {
        idx = 0;
        REP(i, n) par[i][0] = i, rank[i] = 1, fin[i] = 0;
    }
    // t(1-indexed)回目までのuniteでのxの親
    int find(int x, int t) {
        if(t >= fin[x] && par[x][fin[x]] != x) return find(par[x][fin[x]], t);
        return x;
    }
    void unite(int x, int y) {
        x = find(x, idx);
        y = find(y, idx);
        idx++;
        if(x == y) return;
        if(rank[x] < rank[y]) par[x][idx] = y, fin[x] = idx;
        else {
          par[y][idx] = x, fin[y] = idx;
          if(rank[x] == rank[y]) rank[x]++;
        }
    }
    bool same(int x, int y, int t) { return find(x, t) == find(y, t); }
};

namespace codethanks2017H {
    partialPersistentUF uf;
    void solve() {
        int n, m;
        cin >> n >> m;
        REP(i, m) {
            int a, b;
            cin >> a >> b;
            a--, b--;
            uf.unite(a, b);
        }

        int q;
        cin >> q;
        REP(i, q) {
            int x, y;
            cin >> x >> y;
            x--, y--;
            if(uf.find(x, m) != uf.find(y, m)) {
                cout << -1 << endl;
                continue;
            }
            int lb = -1, ub = m;
            while(ub-lb > 1) {
                int mid = (ub+lb)/2;
                if(uf.find(x, mid) == uf.find(y, mid)) ub = mid;
                else lb = mid;
            }
            cout << ub << endl;
        }
    }
}