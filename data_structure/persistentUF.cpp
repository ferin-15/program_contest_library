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

template<typename T, int B = 3>
class persistentArray {
private:
    struct node {
        node *ch[1<<B] = {};
        T val = -1;

        node() {}
        node(const T &v) : val(v) {}
    };

    node *root;

    node* build(node *x, const T &dat, int a) {
        if(!x) x = new node();
        if(a == 0) {
            x->val = dat;
            return x;
        }
        auto p = build(x->ch[a&((1<<B)-1)], dat, a>>B);
        x->ch[a&((1<<B)-1)] = p;
        return x;
    }
    pair<node*, T*> mutable_get(node* x, int a) {
        x = x ? new node(*x) : new node();
        if(a == 0) return {x, &x->val};
        auto p = mutable_get(x->ch[a&((1<<B)-1)], a >> B);
        x->ch[a&((1<<B)-1)] = p.first;
        return make_pair(x, p.second);
    }
    T immutable_get(int a, node* x) {
        if(a == 0) return x->val;
        return immutable_get(a>>B, x->ch[a & ((1<<B)-1)]);
    }
public:
    persistentArray() : root(nullptr) {}

    void build(const vector<T> &v) {
        for(int i=0; i<(int)v.size(); ++i) {
            root = build(root, v[i], i);
        }
    }

    T *mutable_get(const int &k) {
        auto p = mutable_get(root, k);
        root = p.first;
        return p.second;
    }
    T operator[](int k) {
        return immutable_get(k, root);
    }
};

struct persistentUnionFind {
    persistentArray<int> data;

    persistentUnionFind() {}
    persistentUnionFind(int sz) { data.build(vector<int>(sz, -1)); }

    int find(int k) {
        int p = data[k];
        return p >= 0 ? find(p) : k;
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y) return;
        auto u = data[x];
        auto v = data[y];
        if(u < v) {
            auto a = data.mutable_get(x); *a += v;
            auto b = data.mutable_get(y); *b = x;
        } else {
            auto a = data.mutable_get(y); *a += u;
            auto b = data.mutable_get(x); *b = y;
        }
    }
    bool same(int x, int y) { return find(x) == find(y); }
    int size(int x) { return -data[find(x)]; }
};

namespace AGC002D {
    void solve() {
        int n, m;
        cin >> n >> m;

        vector<persistentUnionFind> vuf(m+1);
        persistentUnionFind uf(n);

        REP(i, m) {
            int a, b;
            cin >> a >> b;
            a--, b--;
            uf.unite(a, b);
            vuf[i+1] = uf;
        }

        int q;
        cin >> q;
        REP(i, q) {
            int x, y, z;
            cin >> x >> y >> z;
            x--, y--;

            auto check = [&](int mid) {
                if(vuf[mid].same(x, y)) {
                    return vuf[mid].size(x) >= z;
                } else {
                    return vuf[mid].size(x) + vuf[mid].size(y) >= z;
                }
            };

            int lb = 0, ub = m;
            while(ub - lb > 1) {
                int mid = (ub + lb) / 2;
                if(check(mid)) ub = mid;
                else lb = mid;
            }
            cout << ub << endl;
        }
    }
}

signed main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    AGC002D::solve();

    return 0;
}
