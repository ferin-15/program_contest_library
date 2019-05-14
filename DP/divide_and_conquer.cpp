vector<vector<int>> dp(k, vector<int>(n)), W(n, vector<int>(n));
// [l,r] [optl,optr]　O(KNlogN)
function<void(int,int,int,int,int)>
func = [&](int i, int l, int r, int optl, int optr) {
    if(l > r) return;
    int mid = (l+r)/2, optm = -1;
    FOR(j, optl, min(mid+1, optr+1)) {
        if(dp[i+1][mid] > dp[i][j] + W[j+1][mid]) {
            dp[i+1][mid] = dp[i][j] + W[j+1][mid];  // [j+1, mid]
            optm = j;
        }
    }
    func(i, l, mid-1, optl, optm);
    func(i, mid+1, r, optm, optr);
};

REP(i, n) REP(j, n) W[i][j] = 0; // !!!
FOR(i, 1, k) REP(j, n) dp[i][j] = INF;
REP(i, n) dp[0][i] = W[0][i]; // !!!

REP(i, k) func(i, 0, n-1, 0, n-1);
cout << dp[k-1][n-1] << endl;
