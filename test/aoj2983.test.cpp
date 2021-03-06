#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2983"
#include "../memo/macro.hpp"
#include "../math/runtime_modint.cpp"
#include "../math/finite_field_matrix.cpp"
#include "../graph/max_matching.cpp"

signed main(void) {
    MOD = 1000000007;
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> op(n);
    REP(i, m) {
        ll k;
        cin >> k;
        REP(j, k) {
            ll v;
            cin >> v;
            v--;
            op[v].push_back(i);
        }
    }

    vector<bool> used(n);
    ll ans = 0;
    REP(i, n) {
        // 自己ループが存在したらその辺を必ず取る
        // 自己ループに隣接する辺はグラフにいれないようにする
        if(op[i].size() == 1) {
            if(used[op[i][0]]) continue;
            used[op[i][0]] = true;
            ans++;
        }
        // 操作されない頂点は確定で独立集合に入れる
        else if(op[i].size() == 0) {
            ans++;
        }
    }

    vector<PII> edges;
    REP(i, n) {
        if(op[i].size() == 2) {
            if(used[op[i][0]] || used[op[i][1]]) continue;
            edges.push_back({op[i][0], op[i][1]});
        }
    }
    cout << max_matching(m, edges) + ans << endl;

    return 0;
}