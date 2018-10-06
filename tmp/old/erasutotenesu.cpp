// first 素因数 second 個数
VI fact(ll n){
  vector<PII> p;
  ll m = n;
	for(ll i=2;i<sqrt(n)+1;i++){
    int k = 0;
		while(m%i==0){
			m/=i;
			++k;
		}
    if(k) p.PB(PII(i, k));
	}
  if(m > 1) p.PB(PII(m, 1));
}

//-------------------素数ならtrue----------------------
bool prime[1000000];
memset(prime, true, sizeof(prime));
prime[0] = prime[1] = false;
for (int i = 2; i * i <= 1000000; i++) {
	if (prime[i]) {
		for (int j = 2 * i; j <= 1000000; j += i) {
			prime[j] = false;
		}
	}
}
//-------------------------------------------------------
