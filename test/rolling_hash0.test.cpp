#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2444"
#include "../string/rolling_hash.cpp"

signed main(void) {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n, q;
    string s;
    cin >> n >> q >> s;

    const ll mod1 = 1000000007, base1 = 1007;
    const ll mod2 = 1000000009, base2 = 1009;
    rollingHash<mod1, base1> hash1(s);
    rollingHash<mod2, base2> hash2(s);

    ll l = 0, r = 0;
    set<PII> st;
    while(q--) {
        string t;
        cin >> t;
        if(t == "R++") r++;
        else if(t == "R--") r--;
        else if(t == "L++") l++;
        else if(t == "L--") l--;
        st.insert(PII(hash1.get(l, r+1), hash2.get(l, r+1)));
    }
    cout << st.size() << endl;

    return 0;
}