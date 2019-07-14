// 文字の種類数をtemplate引数で渡す
template <int types = 26>
struct AhoCorasick {
    struct node {
    int fail;
    vector<int> next;
    vector<int> matched;
    node() : fail(-1), next(types, -1) {}
    };

    vector<node> nodes;
    // 辞書の種類数, trie木の根
    int sz, root;
    // 文字と数字の対応付けをする関数
    using F = function<int(char)>;
    F trans;

    AhoCorasick() {}
    AhoCorasick(vector<string> pattern, F f = [](char c){return c-'a';}) :  sz(pattern.size()), root(0) {
        nodes.resize(1);
        trans = f;
        build(pattern);
    }
    // vectorを結合
    vector<int> unite(const vector<int> &a, const vector<int> &b) {
        vector<int> ret;
        set_union(ALL(a), ALL(b), back_inserter(ret));
        return ret;
    }
    // 文字列集合patternからtrie木っぽいオートマトンを作成
    void build(vector<string> pattern) {
        int now;
        nodes[root].fail = root;
        REP(i, pattern.size()) {
            now = root;
            for(const auto &c: pattern[i]) {
                if(nodes[now].next[trans(c)] == -1) {
                    nodes.push_back(node());
                    nodes[now].next[trans(c)] = nodes.size() - 1;
                }
                now = nodes[now].next[trans(c)];
            }
            nodes[now].matched.push_back(i);
        }

        queue<int> que;
        REP(i, types) {
            if(nodes[root].next[i] == -1) {
                nodes[root].next[i] = root;
            } else {
                nodes[nodes[root].next[i]].fail = root;
                que.push(nodes[root].next[i]);
            }
        }
        while(que.size()) {
            now = que.front(); que.pop();
            REP(i, types) {
                if(nodes[now].next[i] != -1) {
                    int nxt = nodes[now].fail;
                    while(nodes[nxt].next[i] == -1) nxt = nodes[nxt].fail;
                    int nxt_tmp = nodes[now].next[i];
                    nodes[nxt_tmp].fail = nodes[nxt].next[i];
                    nodes[nxt_tmp].matched = unite(nodes[nxt_tmp].matched, nodes[nodes[nxt].next[i]].matched);
                    que.push(nxt_tmp);
                }
            }
        }
    }
    // 一文字ずつ照合していく
    int next(int p, const char c) {
        while(nodes[p].next[trans(c)] == -1) p = nodes[p].fail;
        return nodes[p].next[trans(c)];
    }
    // 文字列s中に辞書と一致する部分列がどれだけあるか
    vector<int> match(const string s) {
        vector<int> res(sz);
        int now = root;
        for(auto c : s) {
            now = next(now, c);
            for(auto i : nodes[now].matched) res[i]++;
        }
        return res;
    }
};
