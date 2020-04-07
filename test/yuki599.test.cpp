#define PROBLEM "https://yukicoder.me/problems/no/599"
#include "../memo/macro.hpp"
#include "../math/modint.cpp"
#include "../string/z_algorithm.cpp"

int main(void) {
    string s;
    cin >> s;
    const ll n = s.size();

    using mint = modint<1000000007>;
    vector<mint> dp(n/2+1);
    dp[0] = 1;
    FOR(i, 1, n/2+1) {
        auto v = Zalgo(s.substr(i-1));
        FOR(j, i, n/2+1) if(v[n-j-(i-1)] >= j-i+1) dp[j] += dp[i-1];
    }

    mint ret = 0;
    REP(i, n/2+1) ret += dp[i];
    cout << ret << endl;

    return 0;
}