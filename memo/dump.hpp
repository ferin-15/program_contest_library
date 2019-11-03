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