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


# :warning: string/parse_tree.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b45cffe084dd3d20d928bee85e7b0f21">string</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/parse_tree.cpp">View this file on GitHub</a>
    - Last commit date: 2019-08-31 05:50:04+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// 四則演算と括弧の文字列を構文解析して構文木をつくる
template<class T>
class parser {
private:
    struct node {
        char op;
        ll left, right;
        T val;
        ll id;
        node() {}
        node(char op, ll l, ll r, T v, ll id=-1)
            : op(op), left(l), right(r), val(v), id(id) {}
    };

    string s;
    ll s_pos;
    // 対応する頂点番号を返す
    ll expr() {
        ll ch_l = term();
        while(s_pos < (ll)s.size() && (s[s_pos]=='+' || s[s_pos]=='-')) {
            char op = s[s_pos++];
            ll ch_r = term();
            T val;
            if(op == '+') {
                val = nodes[ch_l].val + nodes[ch_r].val;
            } else if(op == '-') {
                val = nodes[ch_l].val - nodes[ch_r].val;
            }
            nodes.emplace_back(op, ch_l, ch_r, val);
            ch_l = nodes.size()-1;
        }
        return ch_l;
    }
    ll term() {
        ll ch_l = value();
        while(s_pos < (ll)s.size() && (s[s_pos]=='*' || s[s_pos]=='/')) {
            char op = s[s_pos++];
            ll ch_r = value();
            T val;
            if(op == '*') {
                val = nodes[ch_l].val * nodes[ch_r].val;
            } else if(op == '/') {
                val = nodes[ch_l].val / nodes[ch_r].val;
            }
            nodes.emplace_back(op, ch_l, ch_r, val);
            ch_l = nodes.size()-1;
        }
        return ch_l;
    }
    ll value() {
        if(s[s_pos] == '(') {
            s_pos++;
            ll ch_l = expr();
            s_pos++;
            return ch_l;
        } else {
            s_pos++;
            // 大体ここは整数が来そうだけど今回はa[id]
            T val = a[id];
            nodes.emplace_back('a', -1, -1, val, id);
            id++;
            return nodes.size()-1;
        }
    }

public:
    // 今回の問題ではaを使う
    ll id = 0;
    vector<ll> a;

    ll root = 0;
    vector<node> nodes;
    parser(string s) : s(s), s_pos(0) {}
    T build() {
        root = expr();
        return nodes[root].val;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "string/parse_tree.cpp"
// 四則演算と括弧の文字列を構文解析して構文木をつくる
template<class T>
class parser {
private:
    struct node {
        char op;
        ll left, right;
        T val;
        ll id;
        node() {}
        node(char op, ll l, ll r, T v, ll id=-1)
            : op(op), left(l), right(r), val(v), id(id) {}
    };

    string s;
    ll s_pos;
    // 対応する頂点番号を返す
    ll expr() {
        ll ch_l = term();
        while(s_pos < (ll)s.size() && (s[s_pos]=='+' || s[s_pos]=='-')) {
            char op = s[s_pos++];
            ll ch_r = term();
            T val;
            if(op == '+') {
                val = nodes[ch_l].val + nodes[ch_r].val;
            } else if(op == '-') {
                val = nodes[ch_l].val - nodes[ch_r].val;
            }
            nodes.emplace_back(op, ch_l, ch_r, val);
            ch_l = nodes.size()-1;
        }
        return ch_l;
    }
    ll term() {
        ll ch_l = value();
        while(s_pos < (ll)s.size() && (s[s_pos]=='*' || s[s_pos]=='/')) {
            char op = s[s_pos++];
            ll ch_r = value();
            T val;
            if(op == '*') {
                val = nodes[ch_l].val * nodes[ch_r].val;
            } else if(op == '/') {
                val = nodes[ch_l].val / nodes[ch_r].val;
            }
            nodes.emplace_back(op, ch_l, ch_r, val);
            ch_l = nodes.size()-1;
        }
        return ch_l;
    }
    ll value() {
        if(s[s_pos] == '(') {
            s_pos++;
            ll ch_l = expr();
            s_pos++;
            return ch_l;
        } else {
            s_pos++;
            // 大体ここは整数が来そうだけど今回はa[id]
            T val = a[id];
            nodes.emplace_back('a', -1, -1, val, id);
            id++;
            return nodes.size()-1;
        }
    }

public:
    // 今回の問題ではaを使う
    ll id = 0;
    vector<ll> a;

    ll root = 0;
    vector<node> nodes;
    parser(string s) : s(s), s_pos(0) {}
    T build() {
        root = expr();
        return nodes[root].val;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

