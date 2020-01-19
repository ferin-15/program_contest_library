#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_I"
#include "../data_structure/lazysegtree.cpp"

signed main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    int n, q;
    cin >> n >> q;

    lazysegtree<linear_exp> seg(n);
    seg.build(vector<node>(n, node(0, 0, 0, 1)));
    while(q--) {
        int c, s, t;
        cin >> c >> s >> t;
        if(c == 0) {
            int x;
            cin >> x;
            seg.update(s, t+1, PII(0, x));
        } else {
            cout << seg.query(s, t+1).sum << endl;
        }
    }

    return 0;
}
