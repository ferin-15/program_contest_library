// オイラーツアー
ll ptr = 1;
vector<ll> tour(2*n-1), in(n);
function<void(ll,ll)> euler_tour = [&](ll v, ll p) {
    in[v] = ptr-1;
    for(auto to: g[v]) {
        if(to == p) continue;
        tour[ptr++] = to;
        euler_tour(to, v);
    }
    if(p != -1) tour[ptr++] = p;
};
euler_tour(0, -1);
