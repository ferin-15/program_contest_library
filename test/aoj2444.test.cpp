#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2444"
#include "../memo/macro.hpp"
#include "../memo/rand.cpp"
#include "../string/rolling_hash.cpp"

signed main(void) {
    ll n, q;
    string s;
    cin >> n >> q >> s;

    rollingHash hash(s);

    ll l = 0, r = 0;
    set<ll> st;
    while(q--) {
        string t;
        cin >> t;
        if(t == "R++") r++;
        else if(t == "R--") r--;
        else if(t == "L++") l++;
        else if(t == "L--") l--;
        st.insert(hash.get(l, r+1));
    }
    cout << st.size() << endl;

    return 0;
}