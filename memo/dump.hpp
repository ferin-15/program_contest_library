template<class S,class T>
ostream &operator <<(ostream& out, const pair<S,T>& a){
    out<<'('<<a.first<<','<<a.second<<')'; return out;
}
template<class T>
ostream &operator <<(ostream& out, const vector<T>& a){
    if(a.size() >= 1000) {
        out << "many elements";
        return out;
    }
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
    if(a.size() >= 1000) {
        out << "many elements";
        return out;
    }
    out << '['; 
    REP(i, a.size()) {
        out << a[i];
        if(i+1!=(ll)a.size()) out << ",";
    }
    out << ']';
    return out;
}
template<>
ostream &operator<< <string>(ostream& out, const vector<string>& a){
    if(a.size() >= 1000) {
        out << "many elements";
        return out;
    }
    out << endl;
    REP(i, a.size()) {
        out << "i=" << i << " " << a[i];
        if(i+1!=(ll)a.size()) out << endl;
    }
    return out;
}
template<>
ostream &operator<< <vector<int>>(ostream& out, const vector<vector<int>>& a){
    if(a.size() >= 1000) {
        out << "many elements";
        return out;
    }
    out << endl;
    REP(i, a.size()) {
        out << "i=" << i << " " << a[i];
        if(i+1!=(ll)a.size()) out << endl;
    }
    return out;
}
template<>
ostream &operator<< <vector<ll>>(ostream& out, const vector<vector<ll>>& a){
    if(a.size() >= 1000) {
        out << "many elements";
        return out;
    }
    out << endl;
    REP(i, a.size()) {
        out << "i=" << i << " " << a[i];
        if(i+1!=(ll)a.size()) out << endl;
    }
    return out;
}
template<>
ostream &operator<< <vector<PII>>(ostream& out, const vector<vector<PII>>& a){
    if(a.size() >= 1000) {
        out << "many elements";
        return out;
    }
    out << endl;
    REP(i, a.size()) {
        out << "i=" << i << " " << a[i];
        if(i+1!=(ll)a.size()) out << endl;
    }
    return out;
}
template<class T, class S>
ostream &operator <<(ostream& out, const map<T,S>& a){
    if(a.size() >= 1000) {
        out << "many elements";
        return out;
    }
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
    if(a.size() >= 1000) {
        out << "many elements";
        return out;
    }
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
    if(a.size() >= 1000) {
        out << "many elements";
        return out;
    }
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
    if(a.size() >= 1000) {
        out << "many elements";
        return out;
    }
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
    if(a.size() >= 1000) {
        out << "many elements";
        return out;
    }
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
    if(a.size() >= 1000) {
        out << "many elements";
        return out;
    }
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
    if(a.size() >= 1000) {
        out << "many elements";
        return out;
    }
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
    if(a.size() >= 1000) {
        out << "many elements";
        return out;
    }
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
    if(a.size() >= 1000) {
        out << "many elements";
        return out;
    }
    auto b(a);
    out << "[";
    while(b.size()) {
        out << b.top(); b.pop();
        if(b.size()) out << " ";
    }
    out << "]";
    return out;
}

ll debug_dump_cnt = 0;
void dump_func() {
    debug_dump_cnt++;
    cerr << "\n";
}
template <class Head, class... Tail>
void dump_func(Head &&head, Tail &&... tail) {
    if(debug_dump_cnt > 1000) {
        if(debug_dump_cnt == 1001) cerr << "many dump\n";
        return;
    } 
    cerr << head;
    if (sizeof...(Tail) > 0) {
        cerr << ", ";
    }
    dump_func(std::move(tail)...);
}

#define dump(...) cerr << string(#__VA_ARGS__) << ": ", dump_func(__VA_ARGS__); 