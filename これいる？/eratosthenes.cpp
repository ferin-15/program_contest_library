vector<bool> eratosthenes(ll n=1000000) {
	vector<bool> prime(n+1, true);
	prime[0] = prime[1] = false;
	for (int i = 2; i * i <= n; i++) {
		if (prime[i]) {
			for (int j = 2 * i; j <= n; j += i) {
				prime[j] = false;
			}
		}
	}
	return prime;
}
