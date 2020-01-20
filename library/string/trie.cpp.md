---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: string/trie.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b45cffe084dd3d20d928bee85e7b0f21">string</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/trie.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 04:35:05+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "string/trie.cpp"
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

