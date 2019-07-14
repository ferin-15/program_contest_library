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

// 計算量よくわからないけどなんかはやい n<=4e5で200msとか
struct BipartiteMatching {
    vector<int> pre, root;
    vector<vector<int>> to;
    vector<int> p, q;
    int n, m;
    BipartiteMatching(int n, int m) : pre(n,-1),root(n,-1),to(n),p(n,-1),q(m,-1),n(n),m(m){}
    void add(int a, int b) { to[a].push_back(b);}
    int solve() {
        int res = 0;
        bool upd = true;
        while (upd) {
            upd = false;
            queue<int> s;
            for (int i = 0; i < n; ++i) {
                if (!~p[i]) {
                    root[i] = i;
                    s.push(i);
                }
            }
            while (!s.empty()) {
                int v = s.front(); s.pop();
                if (~p[root[v]]) continue;
                for (int i = 0; i < (int)to[v].size(); ++i) {
                    int u = to[v][i];
                    if (!~q[u]) {
                        while (~u) {
                            q[u] = v;
                            swap(p[v],u);
                            v = pre[v];
                        }
                        upd = true;
                        ++res;
                        break;
                    }
                    u = q[u];
                    if (~pre[u]) continue;
                    pre[u] = v; root[u] = root[v];
                    s.push(u);
                }
            }
            if (upd) fill(pre.begin(),pre.end(),-1), fill(root.begin(),root.end(),-1);
        }
        return res;
    }
};

namespace speedrun2K {
    void solve() {
        ll n;
        cin >> n;
        vector<ll> a(n), b(n), vs;
        REP(i, n) {
            cin >> a[i] >> b[i];
            vs.push_back(a[i]);
            vs.push_back(b[i]);
        }
        sort(ALL(vs));
        vs.erase(unique(ALL(vs)), vs.end());
        REP(i, n) {
            a[i] = lower_bound(ALL(vs), a[i]) - vs.begin();
            b[i] = lower_bound(ALL(vs), b[i]) - vs.begin();
        }

        BipartiteMatching match(n, vs.size());
        REP(i, n) {
            match.add(i, a[i]);
            match.add(i, b[i]);
        }
        cout << match.solve() << endl;
    }
}

signed main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    speedrun2K::solve();

    return 0;
}
