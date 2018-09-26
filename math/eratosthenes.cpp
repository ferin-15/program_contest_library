//素数ならtrue
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
