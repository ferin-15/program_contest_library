// BEGIN CUT
template<class T, class S, class F>
struct SWAG {
    // using F = function<S(S,T)>;
    F f; S id;
    stack<T> lt, rt;
    stack<S> ls, rs;
    SWAG(F f, S d) : f(f), id(d) {
        ls.push(id);
        rs.push(id);
    }
    void push_back(T x) { 
        rt.push(x);
        rs.push(f(rs.top(), x));
    }
    void pop_front() {
        if(lt.empty()) {
            while(rt.size()) {
                T x = rt.top(); rt.pop(); rs.pop();
                lt.push(x);
                ls.push(f(ls.top(), x));
            }
        }
        lt.pop();
        ls.pop();
    }
    template<class Q>
    void fold(Q q) { q(ls.top(), rs.top()); }
};
// END CUT