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

template <int types = 26>
struct Trie {
    struct node {
        ll idx;
        vector<ll> next;
        vector<ll> matched;
        node() : idx(0), next(types, -1) {}
    };

    using F = function<int(char)>;
    vector<node> nodes;
    int sz; // 文字列の種類数
    int root;
    F trans;

    // 初期化
    Trie() {}
    Trie(vector<string> pattern, F f = [](char c){return c-'a';})
    : nodes(1), sz(pattern.size()), root(0), trans(f) {
        build(pattern);
    }
    // 文字列集合patternからtrie木を構築
    void build(vector<string> pattern) {
        int now;
        REP(i, pattern.size()) {
            ll idx = 1;
            now = root;
            for(const auto &c: pattern[i]) {
                if(nodes[now].next[trans(c)] == -1) {
                    nodes.push_back(node());
                    nodes.back().idx = idx;
                    nodes[now].next[trans(c)] = nodes.size() - 1;
                }
                now = nodes[now].next[trans(c)];
                idx++;
            }
            nodes[now].matched.push_back(i);
        }
    }
    // 子が一つの頂点の分を圧縮してパトリシア木をつくる
    void compress(ll v, ll pre, ll pre_c) {
        ll ch_num = 0, to = -1;
        REP(i, types) if(nodes[v].next[i] != -1) {
            to = nodes[v].next[i];
            ch_num++;
        }
        if(ch_num==1 && nodes[v].matched.size()==0 && pre != -1) {
            nodes[pre].next[pre_c] = to;
            compress(to, pre, pre_c);
        } else {
            REP(i, types) if(nodes[v].next[i] != -1) {
                compress(nodes[v].next[i], v, i);
            }
        }
    }
    void compress() { compress(root, -1, -1); }
    vector<ll> num;
    void dfs(ll v) {
        num[v] += nodes[v].matched.size();
        REP(i, types) if(nodes[v].next[i] != -1) {
            dfs(nodes[v].next[i]);
            num[v] += num[nodes[v].next[i]];
        }
    }
    vector<ll> ord;
    vector<string> s;
    ll query(ll tar, ll v) {
        ll ret = nodes[v].matched.size();
        if(ret>0 && nodes[v].matched[0] == tar) return 1;
        ll c = s[tar][nodes[v].idx]-'a';
        REP(i, types) {
            ll to = nodes[v].next[i];
            if(to == -1) continue;
            if(ord[i] < ord[c]) ret += num[to];
            else if(ord[i] == ord[c]) ret += query(tar, to);
        }
        return ret;
    }
};
