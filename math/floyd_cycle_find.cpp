// 初項s0でs_n=next(s_{n-1})となる数列
// s_i = s_{i+period} (i>=start) となるようなstart, periodを探索
// time: O(start+period) space: O(1)
template<class F>
PII floyd_cycle_find(const ll s0, F next) {
    ll t = 0, h = 1, st = s0, sh = next(s0);
    for(; st!=sh; t++, st=next(st), h+=2, sh=next(next(sh)));
    ll start = 0;
    sh = s0; 
    REP(i, h-t) sh = next(sh);
    for(st=s0; st!=sh; ++start, st=next(st), sh=next(sh));
    ll period = 1;
    for(sh=next(st); st!=sh; ++period, sh=next(sh));
    
    return make_pair(start, period);
}

/* 線形合同法などに使われるらしい
const ll s0 = 1611516670;
auto next = [](ll s) { 
    constexpr ll m = 1LL<<40;
    return (s + (s>>20) + 12345) & (m-1); 
};
auto [start, period] = floyd_cycle_find(s0, next); 
*/