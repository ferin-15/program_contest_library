template<class T, class F>
struct slidingWindowAggregation {
    // using F = function<T(T,T)>;
    F f; T d;
    stack<pair<T,T>> st1, st2;
    slidingWindowAggregation(F f, T d) : f(f), d(d) {}
    // f({x_1, x_2, …, x_n}) を求める
    T fold_all() { 
        if(st1.size() && st2.size()) return f(st1.top().second, st2.top().second); 
        if(st2.size()) return st2.top().second;
        if(st1.size()) return st1.top().second;
        return d;
    }
    // 末尾にx追加
    void push(T x) { 
        const T rui = st2.size() ? f(st2.top().second, x) : x;
        st2.push({x, rui}); 
    }
    // 先頭削除
    void pop() {
        if(st1.empty()) {
            T rui = d;
            while(st2.size()) {
                T t; tie(t, ignore) = st2.top(); st2.pop();
                rui = f(rui, t);
                st1.push({t, rui});
            }
        }
        st1.pop();
    }
};