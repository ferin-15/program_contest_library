struct dice {
    mt19937 mt;
    dice() : mt(chrono::steady_clock::now().time_since_epoch().count()) {}
    ll operator()(ll x) { return this->operator()(0, x - 1); }
    ll operator()(ll x, ll y) {
        uniform_int_distribution<ll> dist(x, y);
        return dist(mt);
    }
} rnd;
