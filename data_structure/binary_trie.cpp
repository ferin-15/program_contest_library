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
ostream &operator <<(ostream& out,const pair<S,T>& a){
    out<<'('<<a.first<<','<<a.second<<')'; return out;
}
template<class T>
ostream &operator <<(ostream& out,const vector<T>& a){
    out<<'['; for(T i: a) {out<<i<<',';} out<<']'; return out;
}

int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0}; // DRUL
const int INF = 1<<30;
const ll LLINF = 1LL<<60;
const ll MOD = 1000000007;

template<typename T = int, int B = 32>
class binaryTrie {
private:
    struct node {
        int cnt;
        T lazy;
        node *ch[2];
        node() : cnt(0), lazy(0), ch{nullptr, nullptr} {}
    };
    node* root;
    void eval(node* t, int depth) {
        if(t->lazy >> depth & 1) swap(t->ch[0], t->ch[1]);
        if(t->ch[0]) t->ch[0]->lazy ^= t->lazy;
        if(t->ch[1]) t->ch[1]->lazy ^= t->lazy;
        t->lazy = 0;
    }
    node* add(node *t, T val, int depth = B-1) {
        if(!t) t = new node;
        t->cnt++;
        if(depth < 0) return t;
        eval(t, depth);
        bool f = (val >> depth) & 1;
        t->ch[f] = add(t->ch[f], val, depth-1);
        return t;
    }
    node* sub(node *t, T val, int depth = B-1) {
        assert(t);
        t->cnt--;
        if(t->cnt == 0) return nullptr;
        if(depth < 0) return t;
        eval(t, depth);
        bool f = (val >> depth) & 1;
        t->ch[f] = sub(t->ch[f], val, depth-1);
        return t;
    }
    T get_min(node *t, T val, int depth = B-1) {
        assert(t);
        if(depth < 0) return 0;
        eval(t, depth);
        bool f = (val >> depth) & 1; f ^= !t->ch[f];
        return get_min(t->ch[f], val, depth-1) | (f << depth);
    }
    T get(node *t, int k, int depth = B-1) {
        if(depth < 0) return 0;
        eval(t, depth);
        int m = t->ch[0] ? t->ch[0]->cnt : 0;
        if(k < m) return get(t->ch[0], k, depth-1);
        return get(t->ch[1], k-m, depth-1) | (1 << depth);
    }
    int count_lower(node* t, T val, int depth = B-1) {
        if(!t || depth < 0) return 0;
        eval(t, depth);
        bool f = (val >> depth) & 1;
        int tmp = (f && t->ch[0]) ? t->ch[0]->cnt : 0;
        return tmp + count_lower(t->ch[f], val, depth-1);
    }
public:
    binaryTrie() : root(nullptr) {}
    int size() const { return root ? root->cnt : 0; }
    bool empty() const { return !root; }
    void insert(T val) { root = add(root, val); }
    void erase(T val) { root = sub(root, val); }
    void xor_all(T val) { if(root) root->lazy ^= val; }
    // valとXORを取ったときのmax/min
    T max_element(T val=0) { return get_min(root, ~val); }
    T min_element(T val=0) { return get_min(root, val); }
    int lower_bound(T val) { return count_lower(root, val); }
    int upper_bound(T val) { return count_lower(root, val+1); }
    T operator[](int k) {
        assert(0 <= k && k < size());
        return get(root, k);
    }
    // valの個数
    int count(T val) {
        if(!root) return 0;
        node *t = root;
        for(int i=B-1; i>=0; --i) {
            eval(t, i);
            t = t->ch[val>>i&1];
            if(!t) return 0;
        }
        return t->cnt;
    }
};

// https://codeforces.com/contest/947/problem/C
namespace cf947c {
    void solve() {
        int n;
        cin >> n;
        vector<int> a(n), p(n);
        REP(i, n) cin >> a[i];
        REP(i, n) cin >> p[i];

        binaryTrie<int, 32> trie;
        REP(i, n) trie.insert(p[i]);

        REP(i, n) {
            int ret = trie.min_element(a[i]);
            cout << (ret^a[i]) << " ";
            trie.erase(ret);
        }
        cout << endl;
    }
}

// https://www.spoj.com/problems/SUBXOR/
namespace spoj_subxor {
    void solve() {
        ll t;
        cin >> t;
        REP(tes, t) {
            ll n, k;
            cin >> n >> k;
            vector<ll> a(n);
            REP(i, n) cin >> a[i];

            binaryTrie<ll, 32> trie;
            ll ret = 0;
            REP(i, n) {
                trie.insert(0);
                trie.xor_all(a[i]);
                ret += trie.lower_bound(k);
            }
            cout << ret << endl;
        }
    }
}

// https://atcoder.jp/contests/arc033/tasks/arc033_3
namespace arc033c {
    void solve() {
        ll q;
        cin >> q;
        binaryTrie<ll, 32> trie;
        REP(i, q) {
            ll t, x;
            cin >> t >> x;
            if(t == 1) {
                trie.insert(x);
            } else {
                cout << trie[x-1] << endl;
                trie.erase(trie[x-1]);
            }
        }
    }
}