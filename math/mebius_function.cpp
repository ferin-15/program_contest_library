const ll m = 100000;
vector<ll> min_factor(m+1, -1), mebius(m+1, 1);
min_factor[0] = 0, min_factor[1] = 1;
FOR(i, 2, m+1) {
    if(min_factor[i] != -1) continue;
    mebius[i] = -1;
    min_factor[i] = i;
    for(ll j=i*2; j<=m; j+=i) {
        if(min_factor[j] == -1) min_factor[j] = i;
        if((j/i)%i == 0) mebius[j] = 0;
        else mebius[j] *= -1;
    } 
}