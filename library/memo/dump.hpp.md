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


# :warning: memo/dump.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d504a5ea65b088497578bdd812714d51">memo</a>
* <a href="{{ site.github.repository_url }}/blob/master/memo/dump.hpp">View this file on GitHub</a>
    - Last commit date: 2019-12-17 02:13:07+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class S,class T>
ostream &operator <<(ostream& out, const pair<S,T>& a){
    out<<'('<<a.first<<','<<a.second<<')'; return out;
}
template<class T>
ostream &operator <<(ostream& out, const vector<T>& a){
    out << '['; 
    REP(i, a.size()) {
        out << a[i];
        if(i+1!=(ll)a.size()) out << ",";
    }
    out << ']';
    return out;
}
template<class T>
ostream &operator <<(ostream& out, const deque<T>& a){
    out << '['; 
    REP(i, a.size()) {
        out << a[i];
        if(i+1!=(ll)a.size()) out << ",";
    }
    out << ']';
    return out;
}
template<>
ostream &operator<< <vector<ll>>(ostream& out, const vector<vector<ll>>& a){
    out << endl;
    REP(i, a.size()) {
        out << "i=" << i << " " << a[i];
        if(i+1!=(ll)a.size()) out << endl;
    }
    return out;
}
template<>
ostream &operator<< <vector<PII>>(ostream& out, const vector<vector<PII>>& a){
    out << endl;
    REP(i, a.size()) {
        out << "i=" << i << " " << a[i];
        if(i+1!=(ll)a.size()) out << endl;
    }
    return out;
}
template<class T, class S>
ostream &operator <<(ostream& out, const map<T,S>& a){
    out << '{'; 
    for(auto itr=a.begin(); itr!=a.end(); ++itr) {
        out << *itr;
        if(next(itr) != a.end()) out << ",";
    } 
    out << '}'; 
    return out;
}
template<class T>
ostream &operator <<(ostream& out, const set<T>& a){
    out << '{'; 
    for(auto itr=a.begin(); itr!=a.end(); ++itr) {
        out << *itr;
        if(next(itr) != a.end()) out << ",";
    } 
    out << '}'; 
    return out;
}
template<class T>
ostream &operator <<(ostream& out, const multiset<T>& a){
    out << '{'; 
    for(auto itr=a.begin(); itr!=a.end(); ++itr) {
        out << *itr;
        if(next(itr) != a.end()) out << ",";
    } 
    out << '}'; 
    return out;
}
template<class T, class S>
ostream &operator <<(ostream& out, const unordered_map<T,S>& a){
    out << '{'; 
    for(auto itr=a.begin(); itr!=a.end(); ++itr) {
        out << *itr;
        if(next(itr) != a.end()) out << ",";
    } 
    out << '}'; 
    return out;
}
template<class T>
ostream &operator <<(ostream& out, const unordered_set<T>& a){
    out << '{'; 
    for(auto itr=a.begin(); itr!=a.end(); ++itr) {
        out << *itr;
        if(next(itr) != a.end()) out << ",";
    } 
    out << '}'; 
    return out;
}
template<class T>
ostream &operator <<(ostream& out, const queue<T>& a){
    auto b(a);
    out << "[";
    while(b.size()) {
        out << b.front(); b.pop();
        if(b.size()) out << " ";
    }
    out << "]";
    return out;
}
template<class T>
ostream &operator <<(ostream& out, const stack<T>& a){
    auto b(a);
    out << "[";
    while(b.size()) {
        out << b.top(); b.pop();
        if(b.size()) out << " ";
    }
    out << "]";
    return out;
}
template<class T>
ostream &operator <<(ostream& out, const priority_queue<T>& a){
    auto b(a);
    out << "[";
    while(b.size()) {
        out << b.top(); b.pop();
        if(b.size()) out << " ";
    }
    out << "]";
    return out;
}
template<class T>
ostream &operator <<(ostream& out, const priority_queue<T, vector<T>, greater<T>>& a){
    auto b(a);
    out << "[";
    while(b.size()) {
        out << b.top(); b.pop();
        if(b.size()) out << " ";
    }
    out << "]";
    return out;
}

void dump_func() {
    cerr << endl;
}
template <class Head, class... Tail>
void dump_func(Head &&head, Tail &&... tail) {
    cerr << head;
    if (sizeof...(Tail) > 0) {
        cerr << ", ";
    }
    dump_func(std::move(tail)...);
}

#define dump(...) cerr << string(#__VA_ARGS__) << ": ", dump_func(__VA_ARGS__); 
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "memo/dump.hpp"
template<class S,class T>
ostream &operator <<(ostream& out, const pair<S,T>& a){
    out<<'('<<a.first<<','<<a.second<<')'; return out;
}
template<class T>
ostream &operator <<(ostream& out, const vector<T>& a){
    out << '['; 
    REP(i, a.size()) {
        out << a[i];
        if(i+1!=(ll)a.size()) out << ",";
    }
    out << ']';
    return out;
}
template<class T>
ostream &operator <<(ostream& out, const deque<T>& a){
    out << '['; 
    REP(i, a.size()) {
        out << a[i];
        if(i+1!=(ll)a.size()) out << ",";
    }
    out << ']';
    return out;
}
template<>
ostream &operator<< <vector<ll>>(ostream& out, const vector<vector<ll>>& a){
    out << endl;
    REP(i, a.size()) {
        out << "i=" << i << " " << a[i];
        if(i+1!=(ll)a.size()) out << endl;
    }
    return out;
}
template<>
ostream &operator<< <vector<PII>>(ostream& out, const vector<vector<PII>>& a){
    out << endl;
    REP(i, a.size()) {
        out << "i=" << i << " " << a[i];
        if(i+1!=(ll)a.size()) out << endl;
    }
    return out;
}
template<class T, class S>
ostream &operator <<(ostream& out, const map<T,S>& a){
    out << '{'; 
    for(auto itr=a.begin(); itr!=a.end(); ++itr) {
        out << *itr;
        if(next(itr) != a.end()) out << ",";
    } 
    out << '}'; 
    return out;
}
template<class T>
ostream &operator <<(ostream& out, const set<T>& a){
    out << '{'; 
    for(auto itr=a.begin(); itr!=a.end(); ++itr) {
        out << *itr;
        if(next(itr) != a.end()) out << ",";
    } 
    out << '}'; 
    return out;
}
template<class T>
ostream &operator <<(ostream& out, const multiset<T>& a){
    out << '{'; 
    for(auto itr=a.begin(); itr!=a.end(); ++itr) {
        out << *itr;
        if(next(itr) != a.end()) out << ",";
    } 
    out << '}'; 
    return out;
}
template<class T, class S>
ostream &operator <<(ostream& out, const unordered_map<T,S>& a){
    out << '{'; 
    for(auto itr=a.begin(); itr!=a.end(); ++itr) {
        out << *itr;
        if(next(itr) != a.end()) out << ",";
    } 
    out << '}'; 
    return out;
}
template<class T>
ostream &operator <<(ostream& out, const unordered_set<T>& a){
    out << '{'; 
    for(auto itr=a.begin(); itr!=a.end(); ++itr) {
        out << *itr;
        if(next(itr) != a.end()) out << ",";
    } 
    out << '}'; 
    return out;
}
template<class T>
ostream &operator <<(ostream& out, const queue<T>& a){
    auto b(a);
    out << "[";
    while(b.size()) {
        out << b.front(); b.pop();
        if(b.size()) out << " ";
    }
    out << "]";
    return out;
}
template<class T>
ostream &operator <<(ostream& out, const stack<T>& a){
    auto b(a);
    out << "[";
    while(b.size()) {
        out << b.top(); b.pop();
        if(b.size()) out << " ";
    }
    out << "]";
    return out;
}
template<class T>
ostream &operator <<(ostream& out, const priority_queue<T>& a){
    auto b(a);
    out << "[";
    while(b.size()) {
        out << b.top(); b.pop();
        if(b.size()) out << " ";
    }
    out << "]";
    return out;
}
template<class T>
ostream &operator <<(ostream& out, const priority_queue<T, vector<T>, greater<T>>& a){
    auto b(a);
    out << "[";
    while(b.size()) {
        out << b.top(); b.pop();
        if(b.size()) out << " ";
    }
    out << "]";
    return out;
}

void dump_func() {
    cerr << endl;
}
template <class Head, class... Tail>
void dump_func(Head &&head, Tail &&... tail) {
    cerr << head;
    if (sizeof...(Tail) > 0) {
        cerr << ", ";
    }
    dump_func(std::move(tail)...);
}

#define dump(...) cerr << string(#__VA_ARGS__) << ": ", dump_func(__VA_ARGS__); 

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

