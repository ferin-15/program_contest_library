template<class T>
class random_set {
    struct Xor128 {
        unsigned x, y, z, w;
        Xor128(unsigned _w) { x = 123456789; y = 362436069; z = 521288629; w = _w; }
        unsigned nextUInt() {
            unsigned t = (x ^ (x << 11));
            x = y; y = z; z = w;
            return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
        }
    } rnd;
    unordered_set<T> st;
    vector<T> v;
public:
    random_set(unsigned seed = 88675123) : rnd(seed) {}
    auto begin() { return st.begin(); }
    auto end() { return st.end(); }
    bool empty() { return st.empty(); }
    size_t size() { return st.size(); }
    auto insert(T key) {
        auto ret = st.insert(key);
        if(ret.second == true) v.push_back(key);
        return ret;
    }
    T random() {
        unsigned idx = rnd.nextUInt() % size();
        return v[idx];
    }
    T pop_random() {
        unsigned idx = rnd.nextUInt() % size();
        T key = v[idx];
        swap(v[idx], v.back());
        st.erase(key);
        v.pop_back();
        return key;
    }
};