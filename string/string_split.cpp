// sepで区切る
vector<string> split(const string &str, char sep) {
    vector<string> v;
    auto first = str.begin();
    while( first != str.end() ) {
        auto last = first;
        while( last != str.end() && *last != sep ) ++last;
        v.push_back(std::string(first, last));
        if( last != str.end() ) ++last;
        first = last;
    }
    return v;
}
